#include "GaussianSplattingHLODBuilder.h"
#include "Serialization/ArchiveCrc32.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Kismet/GameplayStatics.h"
#include "GaussianSplattingStep.h"
#include "Interfaces/IPluginManager.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GaussianSplattingEditorSettings.h"
#include "NiagaraComponent.h"
#include "AssetCompilingManager.h"
#include "ShaderCompiler.h"
#include "Dom/JsonObject.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkyLightComponent.h"
#include "LandscapeComponent.h"
#include "GaussianSplattingEditorLibrary.h"
#include "JsonObjectConverter.h"

UGaussianSplattingHLODBuilderSettings::UGaussianSplattingHLODBuilderSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (!HasAnyFlags(RF_ClassDefaultObject)) {
		CaptureSettings = CreateDefaultSubobject<UGaussianSplattingStep_Capture>("Capture");
		SparseReconstructionSettings = CreateDefaultSubobject<UGaussianSplattingStep_SparseReconstruction>("SparseReconstruction");
		GaussianSplattingEditorSettings = CreateDefaultSubobject<UGaussianSplattingStep_GaussianSplatting>("GaussianSplatting");
	}
}

uint32 UGaussianSplattingHLODBuilderSettings::GetCRC() const
{
	FArchiveCrc32 Ar;
	FString HLODBaseKey = "1EC5FBC75A71412EB296F1E7E8411257";
	Ar << HLODBaseKey;
	TArray<uint8> Buffer;
	FMemoryWriter SettingsAr(Buffer, true);
	CaptureSettings->SerializeScriptProperties(SettingsAr);
	SparseReconstructionSettings->SerializeScriptProperties(SettingsAr);
	GaussianSplattingEditorSettings->SerializeScriptProperties(SettingsAr);
	Ar << Buffer;
	uint32 Hash = Ar.GetCrc();
	return Hash;
}

UGaussianSplattingHLODBuilder::UGaussianSplattingHLODBuilder(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

TSubclassOf<UHLODBuilderSettings> UGaussianSplattingHLODBuilder::GetSettingsClass() const
{
	return UGaussianSplattingHLODBuilderSettings::StaticClass();
}

TArray<UActorComponent*> UGaussianSplattingHLODBuilder::Build(const FHLODBuildContext& InHLODBuildContext, const TArray<UActorComponent*>& InSourceComponents) const
{
	const FString PluginDir = IPluginManager::Get().FindPlugin(TEXT("GaussianSplattingForUnrealEngine"))->GetBaseDir();
	const UGaussianSplattingHLODBuilderSettings* Settings = Cast<UGaussianSplattingHLODBuilderSettings>(HLODBuilderSettings);

	const int32 GarbageCollectionFrequency = 10;
	static int32 Counter = 0;
	InHLODBuildContext.World->FlushLevelStreaming(EFlushLevelStreamingType::Visibility);

	if (InHLODBuildContext.AssetsBaseName.Contains(TEXT("_DL"))) {
		return {};
	}

	if (FApp::CanEverRender()){
		FAssetCompilingManager::Get().FinishAllCompilation();
		FAssetCompilingManager::Get().ProcessAsyncTasks();
		UTexture::ForceUpdateTextureStreaming();
		IStreamingManager::Get().StreamAllResources();
		if (GShaderCompilingManager && GShaderCompilingManager->GetNumRemainingJobs() > 0){
			GShaderCompilingManager->FinishAllCompilation();
		}
	}

	if (!GarbageCollectionFrequency || Counter++ % GarbageCollectionFrequency == 0){
		UE_LOG(LogGaussianSplatting, Warning, TEXT("Pre CollectGarbage"));
		GEngine->ForceGarbageCollection();
		UE_LOG(LogGaussianSplatting, Warning, TEXT("Post CollectGarbage"));
	}

	static bool bNeedRecaptureSky = true;
	if (bNeedRecaptureSky) {
		ASkyLight* SkyLight = Cast<ASkyLight>(UGameplayStatics::GetActorOfClass(InHLODBuildContext.World, ASkyLight::StaticClass()));
		USkyLightComponent* SkyLightComp = SkyLight->GetLightComponent();
		SkyLightComp->MarkRenderStateDirty();
		SkyLightComp->RecaptureSky();
		bNeedRecaptureSky = false;
	}

	TObjectPtr<UGaussianSplattingStep_Capture> CaptureStep = Settings->CaptureSettings;
	TObjectPtr<UGaussianSplattingStep_SparseReconstruction> SparseReconstructionStep = Settings->SparseReconstructionSettings;
	TObjectPtr<UGaussianSplattingStep_GaussianSplatting> GaussianSplattingStep = Settings->GaussianSplattingEditorSettings;
	CaptureStep->SetWorld(InHLODBuildContext.World);
	SparseReconstructionStep->SetWorld(InHLODBuildContext.World);
	GaussianSplattingStep->SetWorld(InHLODBuildContext.World);

	const FString WorkDir = GetDefault<UGaussianSplattingEditorSettings>()->GetWorkDir(InHLODBuildContext.World->GetName() / InHLODBuildContext.AssetsBaseName);
	FString PlyPath = FString::Printf(TEXT("%s/output/point_cloud/iteration_%d/point_cloud.ply"), *WorkDir, GaussianSplattingStep->Iterations);
	bool bUseCache = FParse::Param(FCommandLine::Get(), TEXT("UseCache"));
	
	CaptureStep->Activate();
	CaptureStep->SetWorkDir(WorkDir);
	SparseReconstructionStep->SetWorkDir(WorkDir);
	GaussianSplattingStep->SetWorkDir(WorkDir);

	CaptureStep->SourceMode = EGaussianSplattingSourceMode::Select;
	CaptureStep->SetSelectionByComponents(InSourceComponents);

	if (!(FPaths::FileExists(PlyPath) && bUseCache)) {
		CaptureStep->Capture();
		SparseReconstructionStep->ReconstructionSparse(false);
		GaussianSplattingStep->Train(false);
	}
	else {
		UE_LOG(LogGaussianSplatting, Warning, TEXT("Use Cache Ply : %s"), *PlyPath);
	}

	TSet<FString> SourceAssets;
	for (auto SourceComponent : InSourceComponents) {
		if (UStaticMeshComponent* StaticMeshComp = Cast<UStaticMeshComponent>(SourceComponent)) {
			if (UStaticMesh* StaticMesh = StaticMeshComp->GetStaticMesh()) {
				SourceAssets.Add(StaticMesh->GetName());
			}
		}
		else if(ULandscapeComponent* LandscapeComp = Cast<ULandscapeComponent>(SourceComponent)) {
			SourceAssets.Add(LandscapeComp->GetOwner()->GetActorLabel());
		}
		else {
			SourceAssets.Add(SourceComponent->GetName());
		}
	}
	FBoxSphereBounds Bounds = CaptureStep->CurrentBounds;
	FString InfoPath = FString::Printf(TEXT("%s/output/point_cloud/iteration_%d/point_cloud_meta.json"), *WorkDir, GaussianSplattingStep->Iterations);
	TSharedRef<FJsonObject> WriteJsonObject = MakeShared<FJsonObject>();

	FGaussianSplattingPointCloudMetaInfo MetaInfo;
	MetaInfo.Location = Bounds.Origin;
	MetaInfo.BoxExtent = Bounds.BoxExtent;
	MetaInfo.SourceAssets = SourceAssets;
	FJsonObjectConverter::UStructToJsonObject(FGaussianSplattingPointCloudMetaInfo::StaticStruct(), &MetaInfo, WriteJsonObject, 0, 0);

	FString JsonString;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
	if (FJsonSerializer::Serialize(WriteJsonObject, JsonWriter) && JsonWriter->Close()) {
		FFileHelper::SaveStringToFile(JsonString, *InfoPath);
	}
	if (GaussianSplattingStep->bClippingByMask) {
		PlyPath = GaussianSplattingStep->Clip(PlyPath);
	}
	UGaussianSplattingPointCloud* PointCloud = UGaussianSplattingEditorLibrary::LoadSplatPly(PlyPath, InHLODBuildContext.AssetsOuter, *InHLODBuildContext.AssetsBaseName);
	if (PointCloud != nullptr) {
		UNiagaraSystem* NiagaraSystem = UGaussianSplattingEditorLibrary::CreateNiagaraSystemFromPointCloud(PointCloud, InHLODBuildContext.AssetsOuter, *(InHLODBuildContext.AssetsBaseName + "_Niagara"));
		if (NiagaraSystem) {
			NiagaraSystem->ClearFlags(RF_Public | RF_Standalone);
			UNiagaraComponent* NiagaraComponent = NewObject<UNiagaraComponent>(InHLODBuildContext.AssetsOuter);
			NiagaraComponent->SetWorldLocation(CaptureStep->CurrentBounds.Origin);
			NiagaraComponent->SetAsset(NiagaraSystem);
			return { NiagaraComponent };
		}
	}
	return {};
}