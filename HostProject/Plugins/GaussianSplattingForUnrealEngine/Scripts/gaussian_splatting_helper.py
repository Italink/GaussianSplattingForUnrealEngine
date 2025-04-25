#-*- coding: utf-8 -*-

from ast import arg
import subprocess
import os
import sys
import argparse
import shutil

def printImmediately(*args, **kwargs):
    print(*args, **kwargs, flush = True)

class GaussianSplattingHelper:
    def __init__(self):
        parser = argparse.ArgumentParser(description='Gaussian Splatting Helper')
        parser.add_argument("workDir", help= "work directory");
        parser.add_argument('-s', '--sparse', action='store_true', help='execute sparse reconstruction')
        parser.add_argument('-v', '--view', action='store_true', help='execute colmap view')
        parser.add_argument('-d', '--edit', action='store_true', help='execute colmap edit')
        parser.add_argument('-c', '--colmap', help='')
        parser.add_argument('-g', '--gaussian', help='')
        parser.add_argument('-e', '--extractor', help='')
        parser.add_argument('-mat', '--matcher', help='')
        parser.add_argument('-map', '--mapper', help='')
        parser.add_argument('-a', '--aligner', help='')
        parser.add_argument('-t', '--train', help='')
        parser.add_argument('--clip', action='store_true', help='execute clip ')
        parser.add_argument('--clip_threshold',type=float, help='', default = 0.8)
        parser.add_argument('--mask_dilation',type=int, help='', default = 100)
        parser.add_argument('--ply', help='')
        
        self.args = parser.parse_args()
        self.scriptDir = os.path.dirname(os.path.abspath(__file__))
        os.chdir(self.args.workDir)
        if self.args.sparse:
            self.executeSparseReconstruction()
        if self.args.view:
            self.executeColmapView()
        if self.args.edit:
            self.executeColmapEdit()
        if self.args.gaussian and len(self.args.gaussian) > 0:
            self.executeGaussianSplatting()
        if self.args.clip:
            self.executeGaussianSplattingClip()

    def runCommand(self, command, env_ext = {}):
        env = os.environ.copy();
        env.update(env_ext)
        printImmediately("python run command: ", command)
        process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, stdin=subprocess.DEVNULL, cwd=self.args.workDir , env=env, shell=True, universal_newlines=True)
        while True:
            output = process.stdout.readline()
            if output == '' and process.poll() is not None:
                break
            if output:
                printImmediately(output.strip())
                sys.stdout.flush()
        if process.returncode!= 0:
            printImmediately(f"Command '{command}' failed with return code {process.returncode}", file=sys.stderr)

    def executeSparseReconstruction(self):
        if os.path.exists("./sparse"):
            shutil.rmtree("./sparse")
        os.makedirs("./images", exist_ok=True)
        os.makedirs("./sparse/0", exist_ok=True)
        if os.path.exists("./database.db"):
            os.remove("./database.db")
        command = f"{self.args.colmap} feature_extractor --database_path ./database.db --image_path ./images --ImageReader.camera_model SIMPLE_PINHOLE"
        if os.path.exists("./masks") :
            command += " --ImageReader.mask_path ./masks "
        if self.args.extractor:
            command += str(self.args.extractor);
        self.runCommand(command)
        command = f"{self.args.colmap} exhaustive_matcher --database_path ./database.db "
        if self.args.matcher:
            command += str(self.args.matcher);
        self.runCommand(command)

        # self.runCommand(f"{self.args.colmap} point_triangulator --database_path database.db --image_path images --input_path ./text --output_path ./pointtriangulator --Mapper.fix_existing_images 1 --Mapper.ba_refine_focal_length 0")
        
        command = f"{self.args.colmap} mapper --database_path ./database.db --image_path ./images --output_path ./sparse  --Mapper.fix_existing_images 1 "
        if self.args.mapper:
            command += str(self.args.mapper);
        self.runCommand(command)
        
        command = f"{self.args.colmap} model_aligner --input_path ./sparse/0 --output_path ./sparse/0 --ref_images_path ./cameras.txt --ref_is_gps 0 --alignment_type custom --alignment_max_error 3 "
        if self.args.aligner:
            command += str(self.args.aligner);
        self.runCommand(command)
       
    def executeColmapView(self):
        colmap_executable_path = self.args.colmap
        colmap_directory = os.path.dirname(os.path.dirname(colmap_executable_path))
        plugins_path = os.path.join(colmap_directory, "plugins")
        env = {
            "QT_PLUGIN_PATH" :plugins_path
        }
        command = f"{self.args.colmap} gui --database_path ./database.db --image_path ./images --import_path ./sparse/0"
        self.runCommand(command, env)

    def executeColmapEdit(self):
        colmap_executable_path = self.args.colmap
        colmap_directory = os.path.dirname(os.path.dirname(colmap_executable_path))
        plugins_path = os.path.join(colmap_directory, "plugins")
        env = {
            "QT_PLUGIN_PATH" :plugins_path
        }
        command = f"{self.args.colmap} gui --database_path ./database.db --image_path ./images "
        if os.path.exists("./masks") :
            command += " --ImageReader.mask_path ./masks "
        self.runCommand(command, env)

    def executeGaussianSplatting(self):
        command = "conda activate gaussian_splatting"
        if os.path.exists("./depths"):
            command += f"&& python {self.scriptDir}/make_depth_scale.py --base_dir . --depths_dir ./depths && python {self.args.gaussian}/train.py -s . -m ./output --depths ./depths "
        else:
            command += f"&& python {self.args.gaussian}/train.py -s . -m ./output "
        if self.args.train:
            command += str(self.args.train);
        self.runCommand(command)

if __name__ == "__main__":
    GaussianSplattingHelper = GaussianSplattingHelper()
