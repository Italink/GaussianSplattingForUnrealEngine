#include "GaussianSplattingPointCloudAssetFactory.h"
#include "Misc/Paths.h"
#include "NiagaraSystemFactoryNew.h"
#include "GaussianSplattingEditorLibrary.h"
#include "IContentBrowserSingleton.h"
#include "ContentBrowserModule.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Framework/Notifications/NotificationManager.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "GaussianSplattingPointCloudEditor.h"
#include "NiagaraActor.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GaussianSplattingPointCloudActor.h"

#define LOCTEXT_NAMESPACE "GaussianSplatting"

UGaussianSplattingPointCloudAssetFactory::UGaussianSplattingPointCloudAssetFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Formats.Add(FString(TEXT("ply;")) + NSLOCTEXT("GaussianSplattingPointCloud", "FormatGaussianSplattingPLY", ".ply File").ToString());
	SupportedClass = UGaussianSplattingPointCloud::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
	ImportPriority = 1;
}

UObject* UGaussianSplattingPointCloudAssetFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	FString FileNamePart, FolderPart, ExtensionPart;
	FPaths::Split(Filename, FolderPart, FileNamePart, ExtensionPart);
	UObject* OutObject = nullptr;
	if (ExtensionPart == "ply"){
		OutObject = UGaussianSplattingEditorLibrary::LoadSplatPly(Filename, InParent, *FileNamePart);
		bOutOperationCanceled = false;
	}
	return OutObject;
}


FText UAssetDefinition_GaussianSplattingPointCloud::GetAssetDisplayName() const
{
	return LOCTEXT("GaussianSplattingPointCloud", "GaussianSplattingPointCloud");
}

TSoftClassPtr<UObject> UAssetDefinition_GaussianSplattingPointCloud::GetAssetClass() const
{
	return UGaussianSplattingPointCloud::StaticClass();
}

FLinearColor UAssetDefinition_GaussianSplattingPointCloud::GetAssetColor() const
{
	return FLinearColor(0.0f, 0.5f, 1.0f);
}

TConstArrayView<FAssetCategoryPath> UAssetDefinition_GaussianSplattingPointCloud::GetAssetCategories() const
{
	static const auto Categories = { EAssetCategoryPaths::Misc };
	return Categories;
}

EAssetCommandResult UAssetDefinition_GaussianSplattingPointCloud::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
	for (UGaussianSplattingPointCloud* PointCloud : OpenArgs.LoadObjects<UGaussianSplattingPointCloud>()){
		TSharedRef<FGaussianSplattingPointCloudEditor> NewGaussianSplattingPointCloudEditor(new FGaussianSplattingPointCloudEditor());
		NewGaussianSplattingPointCloudEditor->InitEditor(OpenArgs.GetToolkitMode(), OpenArgs.ToolkitHost, PointCloud);
	}

	return EAssetCommandResult::Handled;
}

UActorFactory_GaussianSplattingPointCloud::UActorFactory_GaussianSplattingPointCloud(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DisplayName = LOCTEXT("GaussianSplattingPointCloudDisplayName", "Gaussian Splatting Point Cloud");
	NewActorClass = AGaussianSplattingPointCloudActor::StaticClass();
	bUseSurfaceOrientation = true;
}

bool UActorFactory_GaussianSplattingPointCloud::CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg)
{
	if (!AssetData.IsValid() || !AssetData.IsInstanceOf(UGaussianSplattingPointCloud::StaticClass()))
	{
		OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoGaussianSplattingPointCloud", "A valid point cloud must be specified.");
		return false;
	}

	return true;
}

void UActorFactory_GaussianSplattingPointCloud::PostSpawnActor(UObject* Asset, AActor* NewActor)
{
	Super::PostSpawnActor(Asset, NewActor);

	UGaussianSplattingPointCloud* PointCloud = CastChecked<UGaussianSplattingPointCloud>(Asset);

	// Change properties
	AGaussianSplattingPointCloudActor* NiagaraActor = CastChecked<AGaussianSplattingPointCloudActor>(NewActor);
	UNiagaraComponent* NiagaraComponent = NiagaraActor->GetNiagaraComponent();
	check(NiagaraComponent);

	NiagaraComponent->UnregisterComponent();
	UGaussianSplattingEditorLibrary::SetupPointCloudToNiagaraComponent(PointCloud, NiagaraComponent);
	NiagaraComponent->RegisterComponent();
}

UObject* UActorFactory_GaussianSplattingPointCloud::GetAssetFromActorInstance(AActor* Instance)
{
	check(Instance->IsA(NewActorClass));
	AGaussianSplattingPointCloudActor* NiagaraActor = CastChecked<AGaussianSplattingPointCloudActor>(Instance);
	UNiagaraComponent* NiagaraComponent = NiagaraActor->GetNiagaraComponent();
	check(NiagaraComponent);
	if (UNiagaraDataInterfaceGaussianSplattingPointCloud* ArrayDI = UNiagaraFunctionLibrary::GetDataInterface<UNiagaraDataInterfaceGaussianSplattingPointCloud>(NiagaraComponent, "PointCloud")) {
		return ArrayDI->GetPointCloud();
	}
	return nullptr;
}

FQuat UActorFactory_GaussianSplattingPointCloud::AlignObjectToSurfaceNormal(const FVector& InSurfaceNormal, const FQuat& ActorRotation) const
{
	// Meshes align the Z (up) axis with the surface normal
	return FindActorAlignmentRotation(ActorRotation, FVector(0.f, 0.f, 1.f), InSurfaceNormal);
}

#undef LOCTEXT_NAMESPACE