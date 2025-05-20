#include "GaussianSplattingEditorLibrary.h"
#include "ObjectTools.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "TextureResource.h"
#include "Misc/Paths.h"
#include "StaticMeshAttributes.h"
#include "MaterialDomain.h"
#include "StaticMeshCompiler.h"
#include "Materials/MaterialInstanceConstant.h"
#include "NiagaraDataInterfaceArrayFloat.h"
#include "NiagaraSystemFactoryNew.h"
#include "NiagaraEditorModule.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "GaussianSplattingPointCloudDataInterface.h"
#include "NiagaraDataInterfaceCurve.h"
#include "Interfaces/IPluginManager.h"
#include "Commandlets/Commandlet.h"
#include "DynamicResolutionState.h"
#include "HAL/ThreadManager.h"
#include "EngineModule.h"
#include "AssetCompilingManager.h"
#include "NiagaraActor.h"
#include "NiagaraComponent.h"
#include "FileHelpers.h"
#include "Engine/StaticMeshActor.h"
#include "JsonObjectConverter.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include <string>
#include <cmath>

constexpr float ColourCoef = 0.28209479177387814;

UGaussianSplattingPointCloud* UGaussianSplattingEditorLibrary::LoadSplatPly(FString FileName, UObject* Outer, FName AssetName /*= NAME_None*/)
{
	const auto& Points = UGaussianSplattingPointCloud::LoadPointsFromFile(FileName);
	if (Points.IsEmpty())
		return nullptr;
	UGaussianSplattingPointCloud* PointCloud = NewObject<UGaussianSplattingPointCloud>(Outer, AssetName);
	PointCloud->SetPoints(Points);
	return PointCloud;
}

UStaticMesh* UGaussianSplattingEditorLibrary::CreateStaticMeshFromPointCloud(UGaussianSplattingPointCloud* PointCloud, UObject* Outer, FName AssetName /*= NAME_None*/)
{
	if (PointCloud == nullptr) {
		return nullptr;
	}
	UStaticMesh* StaticMesh = NewObject<UStaticMesh>(Outer, AssetName);

	{
		FStaticMeshSourceModel& NewSourceModel = StaticMesh->AddSourceModel();
		FMeshDescription& NewMeshDescription = *StaticMesh->CreateMeshDescription(0);
		FStaticMeshAttributes AttributeGetter = FStaticMeshAttributes(NewMeshDescription);
		AttributeGetter.Register();
		NewSourceModel.BuildSettings.bUseMikkTSpace = false;
		NewSourceModel.BuildSettings.bRecomputeNormals = false;
		NewSourceModel.BuildSettings.bRecomputeTangents = false;
		NewSourceModel.BuildSettings.bComputeWeightedNormals = false;
		NewSourceModel.BuildSettings.bUseFullPrecisionUVs = true;
		NewSourceModel.BuildSettings.bRemoveDegenerates = false;
		NewSourceModel.BuildSettings.bUseBackwardsCompatibleF16TruncUVs = true;
		NewSourceModel.BuildSettings.bGenerateLightmapUVs = false;

		TPolygonGroupAttributesRef<FName> PolygonGroupNames = AttributeGetter.GetPolygonGroupMaterialSlotNames();
		TVertexAttributesRef<FVector3f> VertexPositions = AttributeGetter.GetVertexPositions();
		TVertexInstanceAttributesRef<FVector3f> Normals = AttributeGetter.GetVertexInstanceNormals();
		TVertexInstanceAttributesRef<FVector3f> Tangents = AttributeGetter.GetVertexInstanceTangents();
		TVertexInstanceAttributesRef<float> BinormalSigns = AttributeGetter.GetVertexInstanceBinormalSigns();
		TVertexInstanceAttributesRef<FVector4f> Colors = AttributeGetter.GetVertexInstanceColors();
		TVertexInstanceAttributesRef<FVector2f> UVs = AttributeGetter.GetVertexInstanceUVs();

		auto Points = PointCloud->GetPoints();
		int PointCount = Points.Num();

		int TextureDimension = FMath::RoundUpToPowerOfTwo(FMath::Sqrt((double)PointCount));
		FVector2f InvTextureDimension(1.0f / (TextureDimension + 0.5f), 1.0f / TextureDimension);
		TArray<FFloat16> ColorData;
		TArray<FFloat16> ScaleData;
		TArray<FFloat16> QuatData;

		ColorData.Reserve(PointCount * 4);
		ScaleData.Reserve(PointCount * 4);
		QuatData.Reserve(PointCount * 4);

		int32 VertexCount = PointCount * 4;
		int32 VertexInstanceCount = PointCount * 6;
		int32 PolygonCount = 0;

		NewMeshDescription.ReserveNewVertices(VertexCount);
		NewMeshDescription.ReserveNewVertexInstances(VertexInstanceCount);
		NewMeshDescription.ReserveNewPolygons(PolygonCount);
		NewMeshDescription.ReserveNewEdges(PolygonCount * 2);
		UVs.SetNumChannels(1);
		Colors.SetNumChannels(1);

		FPolygonGroupID PolygonGroup0 = NewMeshDescription.CreatePolygonGroup();

		int VaildIndex = 0;

		for (int i = 0; i < PointCount; i++) {
			const FGaussianSplattingPoint& Point = Points[i];

			const FVertexID VertexID0 = NewMeshDescription.CreateVertex();
			const FVertexID VertexID1 = NewMeshDescription.CreateVertex();
			const FVertexID VertexID2 = NewMeshDescription.CreateVertex();
			const FVertexID VertexID3 = NewMeshDescription.CreateVertex();

			float SizeFeature = 4 * FMath::Max(Point.Scale.Length(), 0.00001f) * 0.001f;

			VertexPositions[VertexID0] = Point.Position + SizeFeature * FVector3f(-1.f, 0.0f, -1.f);
			VertexPositions[VertexID1] = Point.Position + SizeFeature * FVector3f(1.f, 0.0f, -1.f);
			VertexPositions[VertexID2] = Point.Position + SizeFeature * FVector3f(1.f, 0.0f, 1.f);
			VertexPositions[VertexID3] = Point.Position + SizeFeature * FVector3f(-1.f, 0.0f, 1.f);

			const FVertexInstanceID VertexInstanceID0 = NewMeshDescription.CreateVertexInstance(VertexID0);
			const FVertexInstanceID VertexInstanceID1 = NewMeshDescription.CreateVertexInstance(VertexID1);
			const FVertexInstanceID VertexInstanceID2 = NewMeshDescription.CreateVertexInstance(VertexID2);

			const FVertexInstanceID VertexInstanceID3 = NewMeshDescription.CreateVertexInstance(VertexID0);
			const FVertexInstanceID VertexInstanceID4 = NewMeshDescription.CreateVertexInstance(VertexID2);
			const FVertexInstanceID VertexInstanceID5 = NewMeshDescription.CreateVertexInstance(VertexID3);

			UVs[VertexInstanceID0] = FVector2f(0.0f, 0.0f);
			UVs[VertexInstanceID1] = FVector2f(1.0f, 0.0f);
			UVs[VertexInstanceID2] = FVector2f(1.0f, 1.0f);

			UVs[VertexInstanceID3] = FVector2f(0.0f, 0.0f);
			UVs[VertexInstanceID4] = FVector2f(1.0f, 1.0f);
			UVs[VertexInstanceID5] = FVector2f(0.0f, 1.0f);

			UVs.Set(VertexInstanceID0, 0, FVector2f(0.0f, 0.0f));
			UVs.Set(VertexInstanceID1, 0, FVector2f(1.0f, 0.0f));
			UVs.Set(VertexInstanceID2, 0, FVector2f(1.0f, 1.0f));
			UVs.Set(VertexInstanceID3, 0, FVector2f(0.0f, 0.0f));
			UVs.Set(VertexInstanceID4, 0, FVector2f(1.0f, 1.0f));
			UVs.Set(VertexInstanceID5, 0, FVector2f(0.0f, 1.0f));

			FVector2f Coord = FVector2f(VaildIndex % TextureDimension, VaildIndex / TextureDimension);
			VaildIndex++;

			FVector2f SampleUV = (Coord + 0.5) * InvTextureDimension;
			FLinearColor VertexColor = SRGBToLinear(FVector4f(SampleUV.X, 0, 0, SampleUV.Y));

			Colors[VertexInstanceID0] = VertexColor;
			Colors[VertexInstanceID1] = VertexColor;
			Colors[VertexInstanceID2] = VertexColor;
			Colors[VertexInstanceID3] = VertexColor;
			Colors[VertexInstanceID4] = VertexColor;
			Colors[VertexInstanceID5] = VertexColor;

			ScaleData.Append({
				Point.Scale.X,
				Point.Scale.Y,
				Point.Scale.Z,
				SizeFeature
			});


			ColorData.Append({
				Point.Color.R,
				Point.Color.G,
				Point.Color.B,
				Point.Color.A
				});

			QuatData.Append({
				Point.Quat.X,
				Point.Quat.Y,
				Point.Quat.Z,
				Point.Quat.W,
				});

			NewMeshDescription.CreateTriangle(PolygonGroup0, {
				VertexInstanceID0,
				VertexInstanceID1,
				VertexInstanceID2,
				});

			NewMeshDescription.CreateTriangle(PolygonGroup0, {
				VertexInstanceID3,
				VertexInstanceID4,
				VertexInstanceID5,
			});
		}

		PolygonGroupNames[PolygonGroup0] = "LOD0_Section0";
		UMaterialInterface* ParentMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.Material'/GaussianSplattingForUnrealEngine/Materials/M_GaussianSplatting.M_GaussianSplatting'"));
		UMaterialInstanceConstant* NewMaterial = NewObject<UMaterialInstanceConstant>(StaticMesh);
		NewMaterial->SetParentEditorOnly(ParentMaterial);

		NewMaterial->SetTextureParameterValueEditorOnly(FMaterialParameterInfo("ScaleTexture"), CreateFloat16TextureFromData(
			StaticMesh,
			TEXT("ScaleTexture"),
			TextureDimension,
			TextureDimension,
			ScaleData));

		NewMaterial->SetTextureParameterValueEditorOnly(FMaterialParameterInfo("QuadTexture"), CreateFloat16TextureFromData(
			StaticMesh,
			TEXT("QuadTexture"),
			TextureDimension,
			TextureDimension,
			QuatData));

		NewMaterial->SetTextureParameterValueEditorOnly(FMaterialParameterInfo("ColorTexture"), CreateFloat16TextureFromData(
			StaticMesh,
			TEXT("ColorTexture"),
			TextureDimension,
			TextureDimension,
			ColorData));

		NewMaterial->PreEditChange(nullptr);
		NewMaterial->PostEditChange();
		StaticMesh->GetStaticMaterials().Add(FStaticMaterial(NewMaterial));
		NewSourceModel.ScreenSize = 1;
		StaticMesh->CommitMeshDescription(0);
	}

	StaticMesh->ImportVersion = EImportStaticMeshVersion::LastVersion;
	StaticMesh->Build();
	StaticMesh->PostEditChange();
	StaticMesh->MarkPackageDirty();
	StaticMesh->WaitForPendingInitOrStreaming(true, true);
	FStaticMeshCompilingManager::Get().FinishAllCompilation();
	return StaticMesh;
}

UNiagaraSystem* UGaussianSplattingEditorLibrary::CreateNiagaraSystemFromPointCloud(UGaussianSplattingPointCloud* PointCloud, UObject* Outer, FName AssetName /*= NAME_None*/, UNiagaraSystem* Template /*= nullptr*/)
{
	if (PointCloud == nullptr) {
		return nullptr;
	}

	if (Template == nullptr) {
		Template = LoadObject<UNiagaraSystem>(nullptr, TEXT("/GaussianSplattingForUnrealEngine/Niagara/NS_GaussianSplattingPointCloud.NS_GaussianSplattingPointCloud"));;
	}

	UNiagaraSystem* NewSystem = Cast<UNiagaraSystem>(StaticDuplicateObject(Template, Outer, AssetName));
	NewSystem->TemplateAssetDescription = FText();
	NewSystem->Category = FText();

	FNiagaraUserRedirectionParameterStore& ParameterStore = NewSystem->GetExposedParameters();
	UNiagaraDataInterfaceGaussianSplattingPointCloud* GaussianSplattingPointsDI = Cast<UNiagaraDataInterfaceGaussianSplattingPointCloud>(ParameterStore.GetDataInterface(FNiagaraVariable(FNiagaraTypeDefinition(UNiagaraDataInterfaceGaussianSplattingPointCloud::StaticClass()), "User.PointCloud")));
	GaussianSplattingPointsDI->SetPointCloud(PointCloud);

	UNiagaraDataInterfaceCurve* GaussianSplattingFeatureCruveDI = Cast<UNiagaraDataInterfaceCurve>(ParameterStore.GetDataInterface(FNiagaraVariable(FNiagaraTypeDefinition(UNiagaraDataInterfaceCurve::StaticClass()), "User.FeatureCurve")));
	GaussianSplattingFeatureCruveDI->Curve = PointCloud->CalcFeatureCurve();

	NewSystem->bFixedBounds = true;
	if (!PointCloud->GetPoints().IsEmpty()) {
		NewSystem->SetFixedBounds(PointCloud->CalcBounds());
	}
	UNiagaraSystemFactoryNew::InitializeSystem(NewSystem, true);
	NewSystem->RequestCompile(false);
	NewSystem->EnsureFullyLoaded();
	NewSystem->PostEditChange();
	NewSystem->MarkPackageDirty();
	return NewSystem;
}

void UGaussianSplattingEditorLibrary::SetupPointCloudToNiagaraComponent(UGaussianSplattingPointCloud* PointCloud, UNiagaraComponent* NiagaraComponent, UNiagaraSystem* NiagaraSystem /*= nullptr*/)
{
	if (NiagaraSystem == nullptr) {
		NiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, TEXT("/GaussianSplattingForUnrealEngine/Niagara/NS_GaussianSplattingPointCloud.NS_GaussianSplattingPointCloud"));
	}
	NiagaraComponent->SetAsset(NiagaraSystem);

	NiagaraComponent->SetSystemFixedBounds(PointCloud->CalcBounds());

	if (UNiagaraDataInterfaceGaussianSplattingPointCloud* ArrayDI = UNiagaraFunctionLibrary::GetDataInterface<UNiagaraDataInterfaceGaussianSplattingPointCloud>(NiagaraComponent, "PointCloud")) {
		ArrayDI->SetPointCloud(PointCloud);
		UNiagaraDataInterfaceGaussianSplattingPointCloud* VariantDI = CastChecked<UNiagaraDataInterfaceGaussianSplattingPointCloud>(DuplicateObject(ArrayDI, NiagaraComponent));
		VariantDI->SetPointCloud(PointCloud);
		NiagaraComponent->SetParameterOverride(FNiagaraVariableBase(FNiagaraTypeDefinition(UNiagaraDataInterfaceGaussianSplattingPointCloud::StaticClass()), "PointCloud"), FNiagaraVariant(VariantDI));
	}
	if (UNiagaraDataInterfaceCurve* ArrayDI = UNiagaraFunctionLibrary::GetDataInterface<UNiagaraDataInterfaceCurve>(NiagaraComponent, "FeatureCurve")) {
		ArrayDI->Curve = PointCloud->CalcFeatureCurve();
		ArrayDI->UpdateLUT();
		UNiagaraDataInterfaceCurve* VariantDI = CastChecked<UNiagaraDataInterfaceCurve>(DuplicateObject(ArrayDI, NiagaraComponent));
		VariantDI->Curve = ArrayDI->Curve;
		NiagaraComponent->SetParameterOverride(FNiagaraVariableBase(FNiagaraTypeDefinition(UNiagaraDataInterfaceCurve::StaticClass()), "FeatureCurve"), FNiagaraVariant(VariantDI));
	}
	if (NiagaraComponent->IsActive()) {
		NiagaraComponent->ReinitializeSystem();
	}
}

UTexture2D* UGaussianSplattingEditorLibrary::CreateFloat16TextureFromData(UObject* Outer, FString Name, uint32 Width, uint32 Height, TArray<FFloat16> Data)
{
	UTexture2D* NewTexture = NewObject<UTexture2D>(Outer, *Name);
	if (!NewTexture->GetPlatformData()) {
		NewTexture->SetPlatformData(new FTexturePlatformData());
	}

	auto PlatformData = NewTexture->GetPlatformData();
	PlatformData->SizeX = Width;
	PlatformData->SizeY = Height;
	PlatformData->SetNumSlices(1);
	PlatformData->PixelFormat = PF_FloatRGBA;
	NewTexture->Filter = TextureFilter::TF_Nearest;
	NewTexture->LODGroup = TextureGroup::TEXTUREGROUP_16BitData;
	NewTexture->CompressionSettings = TC_HDR;
	NewTexture->SRGB = false;
	NewTexture->NeverStream = true;

	int BlockBytes = GPixelFormats[PF_FloatRGBA].BlockBytes;
	int TotalBytes = Width * Height * BlockBytes;
	PlatformData->Mips.Add(new FTexture2DMipMap());
	auto Mip = PlatformData->Mips.Last();
	Mip.SizeX = Width;
	Mip.SizeY = Height;
	Mip.BulkData.Lock(LOCK_READ_WRITE);
	uint8* TextureData = Mip.BulkData.Realloc(TotalBytes);
	FMemory::Memcpy(TextureData, Data.GetData(), Data.Num() * sizeof(FFloat16));
	Mip.BulkData.Unlock();

	NewTexture->Source.Init(Width, Height, 1, 1, TSF_RGBA16F, TextureData);
	NewTexture->UpdateResource();
	NewTexture->MarkPackageDirty();

	return NewTexture;
}

void UGaussianSplattingEditorLibrary::FakeEngineTick(UWorld* InWorld, float InDelta /*= 0.03f*/, int InCount /*= 1*/)
{
	for (int i = 0; i < InCount; i++) {
		//InWorld->FlushLevelStreaming();
		if (IsRunningCommandlet()) {
			GEngine->EmitDynamicResolutionEvent(EDynamicResolutionStateEvent::EndFrame);
			CommandletHelpers::TickEngine(InWorld);
			GEngine->EmitDynamicResolutionEvent(EDynamicResolutionStateEvent::EndFrame);
		}
		else if (FSlateApplication::IsInitialized()) {
			FApp::SetDeltaTime(InDelta);
			bool bIsTicking = FSlateApplication::Get().IsTicking();
			GEngine->EmitDynamicResolutionEvent(EDynamicResolutionStateEvent::EndFrame);
			GEngine->Tick(FApp::GetDeltaTime(), false);
			FSlateApplication::Get().PumpMessages();
			FSlateApplication::Get().Tick();
			GFrameCounter++;

			if (!bIsTicking && GIsRHIInitialized) {
				if (FSceneInterface* Scene = InWorld->Scene) {
					ENQUEUE_RENDER_COMMAND(BeginFrame)([](FRHICommandListImmediate& RHICmdList) {
						GFrameNumberRenderThread++;
						GFrameCounterRenderThread++;
						FCoreDelegates::OnBeginFrameRT.Broadcast();
						});

					ENQUEUE_RENDER_COMMAND(EndFrame)([](FRHICommandListImmediate& RHICmdList) {
						FCoreDelegates::OnEndFrameRT.Broadcast();
						RHICmdList.EndFrame();
						});
					FlushRenderingCommands();
				}
				ENQUEUE_RENDER_COMMAND(VirtualTextureScalability_Release)([](FRHICommandList& RHICmdList) {
					GetRendererModule().ReleaseVirtualTexturePendingResources();
					});
			}

			FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread);

			FSlateApplication::Get().GetRenderer()->Sync();

			FThreadManager::Get().Tick();

			FTSTicker::GetCoreTicker().Tick(FApp::GetDeltaTime());

			GEngine->TickDeferredCommands();

			GEngine->EmitDynamicResolutionEvent(EDynamicResolutionStateEvent::EndFrame);

			FAssetCompilingManager::Get().FinishAllCompilation();
		}
	}
}

FLinearColor UGaussianSplattingEditorLibrary::SRGBToLinear(const FLinearColor& Color)
{
	auto SRGBToLinearFloat = [](const float Color) -> float
		{
			return (Color <= 0.04045f) ? Color / 12.92f : FMath::Pow((Color + 0.055f) / 1.055f, 2.4f);
		};

	return FLinearColor(
		SRGBToLinearFloat(Color.R)
		, SRGBToLinearFloat(Color.G)
		, SRGBToLinearFloat(Color.B)
		, Color.A
	);
}

FLinearColor UGaussianSplattingEditorLibrary::LinearToSRGB(const FLinearColor& Color)
{
	auto LinearToSRGBFloat = [](const float Color) -> float {
		return (Color <= 0.0031308f) ? Color * 12.92f : 1.055f * FMath::Pow(Color, 1.0f / 2.4f) - 0.055f;
		};

	return FLinearColor(
		LinearToSRGBFloat(Color.R)
		, LinearToSRGBFloat(Color.G)
		, LinearToSRGBFloat(Color.B)
		, Color.A
	);
}

FVector2D UGaussianSplattingEditorLibrary::GetTangledUV(int FrameXY, int Index)
{
	int Top = 0, Bottom = FrameXY - 1, Left = 0, Right = FrameXY - 1;
	int MaxFrame = FrameXY - 1;
	int CurrentIndex = 0;

	while (Top <= Bottom && Left <= Right) {
		for (int J = Left; J <= Right; ++J) {
			if (CurrentIndex == Index) {
				return FVector2D(Top, J) / MaxFrame;
			}
			CurrentIndex++;
		}
		Top++;

		for (int I = Top; I <= Bottom; ++I) {
			if (CurrentIndex == Index) {
				return FVector2D(I, Right) / MaxFrame;
			}
			CurrentIndex++;
		}
		Right--;

		if (Top <= Bottom) {
			for (int J = Right; J >= Left; --J) {
				if (CurrentIndex == Index) {
					return FVector2D(Bottom, J) / MaxFrame;
				}
				CurrentIndex++;
			}
			Bottom--;
		}

		if (Left <= Right) {
			for (int I = Bottom; I >= Top; --I) {
				if (CurrentIndex == Index) {
					return FVector2D(I, Left) / MaxFrame;
				}
				CurrentIndex++;
			}
			Left++;
		}
	}
	ensure(false);
	return FVector2D::ZeroVector;
}

FVector UGaussianSplattingEditorLibrary::UVtoPyramid(FVector2D UV)
{
	FVector Position = FVector(
		0.0f + (UV.X - UV.Y),
		-1.0f + (UV.X + UV.Y),
		0.0f
	);

	FVector2D Absolute = FVector2D(Position).GetAbs();
	Position.Z = 1.0f - Absolute.X - Absolute.Y;
	return Position;
}

FVector UGaussianSplattingEditorLibrary::UVtoOctahedron(FVector2D uv)
{
	FVector Position = FVector(2.0f * (uv - 0.5f), 0);

	FVector2D Absolute = FVector2D(Position).GetAbs();
	Position.Z = 1.0f - Absolute.X - Absolute.Y;

	// "Tuck in" the corners by reflecting the xy position along the line y = 1 - x
	// (in quadrant 1), and its mirrored image in the other quadrants.
	if (Position.Z < 0) {
		FVector2D Temp = FVector2D(Position).GetSignVector() * FVector2D(1.0f - Absolute.X, 1.0f - Absolute.Y);
		Position.X = Temp.X;
		Position.Y = Temp.Y;
	}

	return Position;
}

void SearchPlyFileRecursive(FString InRootDir, TArray<TPair<FString, FGaussianSplattingPointCloudMetaInfo>>& OutPlyInfoList)
{
	FString FolderName = FPaths::GetPathLeaf(InRootDir);
	if (FolderName.StartsWith("iteration_", ESearchCase::CaseSensitive)) {
		FString PlyPath = FString::Printf(TEXT("%s/point_cloud.ply"), *InRootDir);
		FString ClippedPlyPath = FString::Printf(TEXT("%s/point_cloud_clipped.ply"), *InRootDir);
		FString PlyInfoPath = FString::Printf(TEXT("%s/point_cloud_meta.json"), *InRootDir);
		if (FPaths::FileExists(PlyInfoPath)) {
			TSharedPtr<FJsonObject> PlyJsonInfo;
			FString JsonString;
			if (FFileHelper::LoadFileToString(JsonString, *PlyInfoPath)) {
				TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
				if (FJsonSerializer::Deserialize(JsonReader, PlyJsonInfo) && PlyJsonInfo.IsValid()) {
					FGaussianSplattingPointCloudMetaInfo MetaInfo;
					FJsonObjectConverter::JsonObjectToUStruct<FGaussianSplattingPointCloudMetaInfo>(PlyJsonInfo.ToSharedRef(), &MetaInfo);
					if (FPaths::FileExists(ClippedPlyPath)) {
						OutPlyInfoList.Add({ ClippedPlyPath, MetaInfo });
					}
					else if (FPaths::FileExists(PlyPath)) {
						OutPlyInfoList.Add({ PlyPath, MetaInfo });
					}
				}
			}
		}
		return;
	}
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.DirectoryExists(*InRootDir)) {
		IFileManager::Get().IterateDirectory(*InRootDir, [&OutPlyInfoList](const TCHAR* Filename, bool bIsDirectory) {
			if (bIsDirectory) {
				SearchPlyFileRecursive(Filename, OutPlyInfoList);
			}
			return true;
			});
	}
}

FString GetDatasetNameName(const FString& FolderPath)
{
	FString DatasetName;
	TArray<FString> PathParts;
	FolderPath.Replace(TEXT("\\"), TEXT("/")).ParseIntoArray(PathParts, TEXT("/"), true);
	if (PathParts.Num() >= 5) {
		DatasetName = PathParts[PathParts.Num() - 4];
		if (DatasetName.StartsWith("Cluster")) {
			DatasetName = PathParts[PathParts.Num() - 5];
		}
	}
	return DatasetName;
}

void UGaussianSplattingEditorLibrary::ImportPointClouds(UWorld* World, FString SearchDir, FString SaveContentDir, UNiagaraSystem* TemplateSystem /*= nullptr*/, bool bUseStandaloneNiagraSystem /*= false */)
{
	TArray<TPair<FString, FGaussianSplattingPointCloudMetaInfo>> PlyInfoList;
	SearchPlyFileRecursive(SearchDir, PlyInfoList);

	TArray<TPair<UGaussianSplattingPointCloud*, FVector>> PointClouds;

	for (auto PlyInfo : PlyInfoList) {
		FString FolderPart, FileNamePart, ExtensionPart;
		FPaths::Split(PlyInfo.Key, FolderPart, FileNamePart, ExtensionPart);
		FString DatasetName = GetDatasetNameName(FolderPart);

		UPackage* NewPackage = CreatePackage(*(SaveContentDir / DatasetName));

		UGaussianSplattingPointCloud* PointCloud = UGaussianSplattingEditorLibrary::LoadSplatPly(PlyInfo.Key, NewPackage, *DatasetName);
		PointCloud->SetFlags(RF_Public | RF_Standalone);
		PointCloud->MarkPackageDirty();

		FAssetRegistryModule::AssetCreated(PointCloud);
		FPackagePath PackagePath = FPackagePath::FromPackageNameChecked(NewPackage->GetName());
		FString PackageLocalPath = PackagePath.GetLocalFullPath();
		UPackage::SavePackage(NewPackage, PointCloud, RF_Public | RF_Standalone, *PackageLocalPath, GError, nullptr, false, true, SAVE_NoError);

		PointClouds.Add({ PointCloud, PlyInfo.Value.Location });
	}

	for (auto PointCloudPair : PointClouds) {
		ANiagaraActor* NiagaraActor = World->SpawnActor<ANiagaraActor>(PointCloudPair.Value, FRotator());
		UNiagaraComponent* NiagaraComponent = NiagaraActor->GetNiagaraComponent();
		UNiagaraSystem* Niagara = nullptr;
		if (bUseStandaloneNiagraSystem) {
			Niagara = UGaussianSplattingEditorLibrary::CreateNiagaraSystemFromPointCloud(PointCloudPair.Key, NiagaraActor->GetPackage(), NAME_None, TemplateSystem);
		}
		else {
			SetupPointCloudToNiagaraComponent(PointCloudPair.Key, NiagaraComponent, TemplateSystem);
		}
		if (Niagara) {
			Niagara->ClearFlags(RF_Public | RF_Standalone);
			NiagaraComponent->SetAsset(Niagara);
			NiagaraActor->Modify();
			NiagaraActor->MarkPackageDirty();
		}
		NiagaraActor->SetActorLabel(PointCloudPair.Key->GetName());
		bool bPromptUserToSave = false;
		bool bSaveMapPackages = true;
		bool bSaveContentPackages = true;
		bool bFastSave = true;
		FEditorFileUtils::SaveDirtyPackages(bPromptUserToSave, bSaveMapPackages, bSaveContentPackages, bFastSave);
	}
}

void UGaussianSplattingEditorLibrary::RepartitionPointClouds(UWorld* World, FString PartitionBaseName /*= "Cell"*/, int32 CellSize /*= 51200*/, UNiagaraSystem* TemplateSystem /*= nullptr*/, bool bUseStandaloneNiagraSystem /*= false */)
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(World, ANiagaraActor::StaticClass(), Actors);
	TMap<UNiagaraComponent*, UGaussianSplattingPointCloud*> OldClouds;
	FString SaveContentDir;
	for (auto Actor : Actors) {
		UNiagaraComponent* NiagaraComponent = Actor->GetComponentByClass<UNiagaraComponent>();
		if (UNiagaraDataInterfaceGaussianSplattingPointCloud* PointCloudDI = UNiagaraFunctionLibrary::GetDataInterface<UNiagaraDataInterfaceGaussianSplattingPointCloud>(NiagaraComponent, "PointCloud")) {
			UGaussianSplattingPointCloud* PointCloud = PointCloudDI->GetPointCloud();
			OldClouds.Add(NiagaraComponent, PointCloud);
			if (SaveContentDir.IsEmpty()) {
				SaveContentDir = FPaths::GetPath(PointCloud->GetPackage()->GetPathName());
			}
		}
	}
	FBox2D TotalBound;
	for (auto CloudPair : OldClouds) {
		FVector BoxExtent = CloudPair.Value->CalcBounds().GetExtent();
		FVector Location = CloudPair.Key->GetComponentLocation();
		TotalBound += FBox2D(
			FVector2D(Location.X - BoxExtent.X, Location.Y - BoxExtent.Y),
			FVector2D(Location.X + BoxExtent.X, Location.Y + BoxExtent.Y)
		);
	}
	TMap<FIntPoint, TArray<TPair<UGaussianSplattingPointCloud*, FVector>>> Partition;
	for (auto CloudPair : OldClouds) {
		FVector BoxExtent = CloudPair.Value->CalcBounds().GetExtent();
		FVector Location = CloudPair.Key->GetComponentLocation();
		FBox2D Bound = FBox2D(
			FVector2D(Location.X - BoxExtent.X, Location.Y - BoxExtent.Y),
			FVector2D(Location.X + BoxExtent.X, Location.Y + BoxExtent.Y)
		);

		if (Bound.GetArea() > 0) {
			FVector2D MinSide = (Bound.Min - TotalBound.Min) / CellSize;
			FVector2D MaxSide = (Bound.Max - TotalBound.Min) / CellSize;
			for (int i = std::floor(MinSide.X); i <= std::ceil(MaxSide.X); i++) {
				for (int j = std::floor(MinSide.Y); j <= std::ceil(MaxSide.Y); j++) {
					Partition.FindOrAdd({ i,j }).Add({ CloudPair.Value, Location });
				}
			}
		}
	}
	TMap<UGaussianSplattingPointCloud*, FVector> RepartitionPointClouds;
	for (const auto& Cell : Partition) {
		FVector CellLocation = FVector(TotalBound.Min.X + Cell.Key.X * CellSize + CellSize / 2.0f, TotalBound.Min.Y + Cell.Key.Y * CellSize + CellSize / 2.0f, 0.0f);
		FBox2D CellBound = FBox2D(
			FVector2D(TotalBound.Min.X + Cell.Key.X * CellSize, TotalBound.Min.Y + Cell.Key.Y * CellSize),
			FVector2D(TotalBound.Min.X + Cell.Key.X * CellSize + CellSize, TotalBound.Min.Y + Cell.Key.Y * CellSize + CellSize)
		);
		TArray<FGaussianSplattingPoint> SourceWorldPoints;
		for (auto Source : Cell.Value) {
			TArray<FGaussianSplattingPoint> LocalPoints = Source.Key->GetPoints();
			for (auto& Point : LocalPoints) {
				Point.Position = FVector3f(Source.Value) + Point.Position;
			}
			SourceWorldPoints.Append(LocalPoints);
		}
		TArray<FGaussianSplattingPoint> CellPoints;
		for (auto Point : SourceWorldPoints) {
			if (CellBound.IsInside(FVector2D(Point.Position.X, Point.Position.Y))) {
				Point.Position = Point.Position - FVector3f(CellLocation);
				CellPoints.Add(Point);
			}
		}
		if (!CellPoints.IsEmpty()) {
			FString CellName = FString::Printf(TEXT("%s_%d_%d"), *PartitionBaseName, Cell.Key.X, Cell.Key.Y);
			UGaussianSplattingPointCloud* PointCloud = nullptr;
			UPackage* Package = nullptr;
			PointCloud = LoadObject<UGaussianSplattingPointCloud>(nullptr, *(SaveContentDir / CellName + "." + CellName));
			if (PointCloud) {
				Package = PointCloud->GetPackage();
			}
			else {
				Package = CreatePackage(*(SaveContentDir / CellName));
				PointCloud = NewObject<UGaussianSplattingPointCloud>(Package, *CellName);
			}
			PointCloud->SetPoints(CellPoints);
			PointCloud->SetFlags(RF_Public | RF_Standalone);
			PointCloud->MarkPackageDirty();
			FAssetRegistryModule::AssetCreated(PointCloud);
			FPackagePath PackagePath = FPackagePath::FromPackageNameChecked(Package->GetName());
			FString PackageLocalPath = PackagePath.GetLocalFullPath();
			UPackage::SavePackage(Package, PointCloud, RF_Public | RF_Standalone, *PackageLocalPath, GError, nullptr, false, true, SAVE_NoError);
			RepartitionPointClouds.Add(PointCloud, CellLocation);
		}
	}
	for (auto OldCloudPair : OldClouds) {
		World->DestroyActor(OldCloudPair.Key->GetOwner());
		if (!RepartitionPointClouds.Contains(OldCloudPair.Value)) {
			ObjectTools::ForceDeleteObjects({ OldCloudPair.Value }, false);
		}
	}
	for (auto PointCloudPair : RepartitionPointClouds) {
		ANiagaraActor* NiagaraActor = World->SpawnActor<ANiagaraActor>(PointCloudPair.Value, FRotator());
		UNiagaraComponent* NiagaraComponent = NiagaraActor->GetNiagaraComponent();
		UNiagaraSystem* Niagara = nullptr;
		if (bUseStandaloneNiagraSystem) {
			Niagara = UGaussianSplattingEditorLibrary::CreateNiagaraSystemFromPointCloud(PointCloudPair.Key, NiagaraActor->GetPackage(), NAME_None, TemplateSystem);
		}
		else {
			SetupPointCloudToNiagaraComponent(PointCloudPair.Key, NiagaraComponent, TemplateSystem);
		}
		if (Niagara) {
			Niagara->ClearFlags(RF_Public | RF_Standalone);
			NiagaraComponent->SetAsset(Niagara);
			NiagaraActor->Modify();
			NiagaraActor->MarkPackageDirty();
		}
		NiagaraActor->SetActorLabel(PointCloudPair.Key->GetName());
		bool bPromptUserToSave = false;
		bool bSaveMapPackages = true;
		bool bSaveContentPackages = true;
		bool bFastSave = true;
		FEditorFileUtils::SaveDirtyPackages(bPromptUserToSave, bSaveMapPackages, bSaveContentPackages, bFastSave);
	}
}

