import numpy as np
import argparse
import cv2
import math
from plyfile import PlyData, PlyElement
from read_write_model import *
from PIL import Image
from scipy.ndimage import binary_dilation
import matplotlib.pyplot as plt

# from vispy import app, scene
# from vispy.scene import visuals

C0 = 0.28209479177387814

def SH2RGB(sh):
    return sh * C0 + 0.5

def getWorld2View(R, t):
    Rt = np.zeros((4, 4))
    Rt[:3, :3] = R
    Rt[:3, 3] = t 
    Rt[3, 3] = 1.0
    return np.float32(Rt)

def getProjectionMatrix(znear, zfar, fovX, fovY):
    tanHalfFovY = math.tan((fovY / 2))
    tanHalfFovX = math.tan((fovX / 2))

    top = tanHalfFovY * znear
    bottom = -top
    right = tanHalfFovX * znear
    left = -right

    P = np.zeros((4, 4))

    z_sign = 1.0

    P[0, 0] = 2.0 * znear / (right - left)
    P[1, 1] = 2.0 * znear / (top - bottom)
    P[0, 2] = (right + left) / (right - left)
    P[1, 2] = (top + bottom) / (top - bottom)
    P[3, 2] = z_sign
    P[2, 2] = z_sign * zfar / (zfar - znear)
    P[2, 3] = -(zfar * znear) / (zfar - znear)
    return P

def focal2fov(focal, pixels):
    return 

def clip_test(pts, image_meta, camera_intrinsics, discarded_indices, mask_image, debug_view):
    pts_homogeneous = np.hstack((pts, np.ones((pts.shape[0], 1))))
    # 计算旋转矩阵
    R = qvec2rotmat(image_meta.qvec)
    # 平移向量
    t = image_meta.tvec
    # 世界坐标系到相机坐标系的变换矩阵
    ViewMat = getWorld2View(R, t)
    # 获取相机内参
    f, cx, cy = camera_intrinsics.params

    image_width = 2 * cx
    image_height = 2 * cy

    # 计算水平和垂直视场角
    fovX = 2 * math.atan(image_width / (2 * f))
    fovY = 2 * math.atan(image_height / (2 * f))
    # 计算投影矩阵
    ProjectionMatrix = getProjectionMatrix(0.01, 10000, fovX, fovY)

    # 将点云从世界坐标系转换到相机坐标系
    camera_points_homogeneous = np.dot(pts_homogeneous, ViewMat.T)
    # 将相机坐标系下的点投影到裁剪空间
    clip_points_homogeneous = np.dot(camera_points_homogeneous, ProjectionMatrix.T)

    # 透视除法
    clip_points = clip_points_homogeneous[:, :3] / clip_points_homogeneous[:, 3, np.newaxis]

    # 提取裁剪空间的深度信息
    clip_depths = clip_points[:, 2]

    # 转换到图像空间
    image_points = np.zeros((clip_points.shape[0], 2))
    image_points[:, 0] = (clip_points[:, 0] + 1) * cx
    image_points[:, 1] = (clip_points[:, 1] + 1) * cy

    original_image_name = image_meta.name

    file_name, file_ext = os.path.splitext(original_image_name)
    image_width = int(camera_intrinsics.width)
    image_height = int(camera_intrinsics.height)

    indices = np.arange(len(image_points))
    x, y = image_points[:, 0].astype(int), image_points[:, 1].astype(int)

    valid_indices = (x >= 0) & (x < image_width) & (y >= 0) & (y < image_height) & (clip_depths >= 0) & (clip_depths <= 1)
    valid_x = x[valid_indices]
    valid_y = y[valid_indices]
    valid_indices_subset = indices[valid_indices]

    in_black_mask = mask_image[valid_y, valid_x] == 0
    black_mask_indices = valid_indices_subset[in_black_mask]

    # 统计 black_mask_indices 中每个索引的计数
    unique_black_mask_indices, black_counts = np.unique(black_mask_indices, return_counts=True)
    # 统计 valid_indices_subset 中每个索引的计数
    unique_valid_indices, valid_counts = np.unique(valid_indices_subset, return_counts=True)

    # 初始化或更新 discarded_indices
    all_indices = np.unique(np.concatenate([unique_black_mask_indices, unique_valid_indices]))
    for idx in all_indices:
        black_count = black_counts[unique_black_mask_indices == idx][0] if idx in unique_black_mask_indices else 0
        valid_count = valid_counts[unique_valid_indices == idx][0] if idx in unique_valid_indices else 0

        if idx not in discarded_indices:
            discarded_indices[idx] = [black_count, valid_count, 0]
        else:
            discarded_indices[idx][0] += black_count
            discarded_indices[idx][1] += valid_count
            discarded_indices[idx][2] = discarded_indices[idx][0] / discarded_indices[idx][1]

def clip(base_dir, ply_path, out_ply_path, mask_dir, mask_use_count = 10, mask_dilation = 5, mask_clip_threshold = 0.8, size_clip_threshold = 0.95, distance_of_observation = 25600, min_screen_size_of_observation = 0.01, debug_view = False):
    cameras, images, points3d = read_model(os.path.join(base_dir, "sparse", "0"), ext=f".bin")
    plydata = PlyData.read(ply_path)
    vertices = plydata['vertex']
    pts = np.vstack([vertices['x'], vertices['y'], vertices['z']]).T
    # shs = np.vstack([vertices['f_dc_0'], vertices['f_dc_1'], vertices['f_dc_2']]).T 
    # colors = SH2RGB(shs)
    scales = np.vstack([np.exp(vertices['scale_0']), np.exp(vertices['scale_1']), np.exp(vertices['scale_2'])]).T
    sizes = np.linalg.norm(scales, axis=1) * 2 
    sizes_ue = sizes * 100
    pts_count = len(pts)

    fov = 90.0
    half_fov_rad = fov * math.pi / 360.0
    screen_multiple = 1920.0 / 1080.0 / math.tan(half_fov_rad)
    min_object_size = min_screen_size_of_observation * distance_of_observation / screen_multiple

    size_percentile = np.percentile(sizes_ue, size_clip_threshold * 100)
    indices_below_threshold = np.where(sizes_ue < 5 * size_percentile)[0]
    clip_count_by_size_percentile = pts_count - len(indices_below_threshold)

    indices_above_min = np.where(sizes_ue > min_object_size)[0]
    observable_indices = np.intersect1d(indices_above_min, indices_below_threshold)
    clip_count_by_observate = pts_count - len(observable_indices) - clip_count_by_size_percentile

    property_names = [prop.name for prop in vertices.properties]
    filtered_properties = {}
    for prop_name in property_names:
        prop_data = vertices[prop_name]
        filtered_properties[prop_name] = prop_data[observable_indices]
        
    new_vertex_data = np.empty(len(filtered_properties[property_names[0]]), dtype=vertices.data.dtype)
    for prop_name in property_names:
        new_vertex_data[prop_name] = filtered_properties[prop_name]
    vertices = PlyElement.describe(new_vertex_data, 'vertex')
    pts = np.vstack([vertices['x'], vertices['y'], vertices['z']]).T

    discarded_indices = {}
    all_indices = np.arange(len(vertices))
    step = max(1, len(images) / mask_use_count)
    image_keys = list(images.keys())
    for i in range(0, len(images), int(step)):
        if i < len(image_keys):
            image_meta = images[image_keys[i]]
            camera_intrinsics = cameras[image_meta.camera_id]
            original_image_name = image_meta.name
            file_name, file_ext = os.path.splitext(original_image_name)
            mask_file_path = os.path.join(mask_dir, file_name + ".png")
            if not os.path.exists(mask_file_path):
                return None
            mask_image = Image.open(mask_file_path)
            mask_image = np.array(mask_image.convert("L"))
            structuring_element = np.ones((2 * mask_dilation + 1, 2 * mask_dilation + 1))
            dilated_mask = binary_dilation(mask_image, structure=structuring_element)
            dilated_mask = (dilated_mask * 255).astype(np.uint8) 
            clip_test(pts, image_meta, camera_intrinsics, discarded_indices, dilated_mask, debug_view)

    valid_indices = [idx for idx in all_indices if idx not in discarded_indices or discarded_indices[idx][2] <  1 - mask_clip_threshold]
    valid_indices = np.array(valid_indices)
    clip_count_by_mask = len(all_indices) - len(valid_indices)

    print(f"clip begin              : {pts_count}")
    print(f"clip by size percentile : {clip_count_by_size_percentile} \t[{size_clip_threshold}] ")
    print(f"clip by size observate  : {clip_count_by_observate} \t[{distance_of_observation}:{min_screen_size_of_observation}] ")
    print(f"clip by size masks      : {clip_count_by_mask} \t[{mask_clip_threshold}] ")
    print(f"clip end                : {len(valid_indices)} ", flush = True)
    
    if len(valid_indices) == 0 :
        return
    property_names = [prop.name for prop in vertices.properties]
    filtered_properties = {}
    for prop_name in property_names:
        prop_data = vertices[prop_name]
        filtered_properties[prop_name] = prop_data[valid_indices]
        
    new_vertex_data = np.empty(len(filtered_properties[property_names[0]]), dtype=vertices.data.dtype)
    for prop_name in property_names:
        new_vertex_data[prop_name] = filtered_properties[prop_name]
    vertices = PlyElement.describe(new_vertex_data, 'vertex')

    output_dir = os.path.dirname(out_ply_path)
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    new_plydata = PlyData([vertices] + [el for el in plydata.elements if el.name != 'vertex'])
    new_plydata.write(out_ply_path)

def hlod_clip_workflow():
    search_dir = r"D:\ProjectTitan\Plugins\GaussianSplattingForUnrealEngine_Private\Work\TitanMain\CitySample_HLOD0_3DGS"

    found_files = []

    for root, dirs, files in os.walk(search_dir):
        for file in files:
            if file == "point_cloud.ply":
                file_path = os.path.join(root, file)
                found_files.append(file_path)

    files_count = len(found_files)
    for i in range(0, files_count, 1):
        ply_path = found_files[i]
        file_name, file_ext = os.path.splitext(ply_path)
        output_ply_path = file_name + '_clipped' + file_ext
        base_dir = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(ply_path))))
        mask_dir = os.path.join(base_dir, "masks")
        mask_dilation = 5
        mask_use_count = 10 
        mask_clip_threshold = 0.9
        size_clip_threshold = 0.98
        distance_of_observation =  25600
        min_screen_size_of_observation = 0.005
        print(f"-------[{i}/{files_count}]{ply_path}", flush = True)
        clip(base_dir, ply_path, output_ply_path, mask_dir, mask_use_count, mask_dilation, mask_clip_threshold, size_clip_threshold, distance_of_observation, min_screen_size_of_observation, False)
        print(f"", flush = True)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--base_dir', default="F:/UnrealProjects/CitySample2/Plugins/GaussianSplattingForUnrealEngine_Private/WorkHome/Cache/Big_City_LVL/CitySample_HLOD0_3DGS/Big_City_LVL_MainGrid_L0_X-9_Y-9/Cluster0")
    parser.add_argument('--ply_path', default="F:/UnrealProjects/CitySample2/Plugins/GaussianSplattingForUnrealEngine_Private/WorkHome/Cache/Big_City_LVL/CitySample_HLOD0_3DGS/Big_City_LVL_MainGrid_L0_X-9_Y-9/Cluster0/output/point_cloud/iteration_7000/point_cloud.ply")
    parser.add_argument('--output_ply_path', default="F:/UnrealProjects/CitySample2/Plugins/GaussianSplattingForUnrealEngine_Private/WorkHome/Cache/Big_City_LVL/CitySample_HLOD0_3DGS/Big_City_LVL_MainGrid_L0_X-9_Y-9/Cluster0/output/point_cloud/iteration_7000/point_cloud_clipped.ply")
    parser.add_argument('--mask_dir', default="F:/UnrealProjects/CitySample2/Plugins/GaussianSplattingForUnrealEngine_Private/WorkHome/Cache/Big_City_LVL/CitySample_HLOD0_3DGS/Big_City_LVL_MainGrid_L0_X-9_Y-9/Cluster0/masks")
    parser.add_argument('--mask_use_count', default=5)
    parser.add_argument('--mask_dilation', default=5)
    parser.add_argument('--mask_clip_threshold', default=0.9)
    parser.add_argument('--size_clip_threshold', default=0.98)
    parser.add_argument('--distance_of_observation', default=25600)
    parser.add_argument('--min_screen_size_of_observation', default=0.005)
    args = parser.parse_args()
    # clip(args.base_dir, args.ply_path, args.output_ply_path, args.mask_dir, args.mask_use_count, args.mask_dilation, args.mask_clip_threshold, args.size_clip_threshold, args.distance_of_observation, args.min_screen_size_of_observation, True)
    hlod_clip_workflow()



                



