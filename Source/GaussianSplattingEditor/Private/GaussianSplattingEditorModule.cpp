#include "GaussianSplattingEditorModule.h"
#include "EditorModeRegistry.h"
#include "GaussianSplattingEdMode.h"
#include "GaussianSplattingEditorStyle.h"
#include "AssetToolsModule.h"
#include "ContentBrowserMenuContexts.h"
#include "GaussianSplattingPointCloud.h"
#include "ContentBrowserModule.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Framework/Notifications/NotificationManager.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Misc/Paths.h"
#include "GaussianSplattingEditorLibrary.h"
#include "IContentBrowserSingleton.h"
#include "NiagaraEditorStyle.h"


#define LOCTEXT_NAMESPACE "GaussianSplatting"

void FGaussianSplattingEditorModule::StartupModule()
{
	FEditorModeRegistry::Get().RegisterMode<FGaussianSplattingEdMode>(
		FGaussianSplattingEdMode::EdID,
		LOCTEXT("GaussianSplatting", "Gaussian Splatting"),
		FSlateIcon(),
		true,
		010200
	);

	FGaussianSplattingEditorStyle::Initialize();
	FGaussianSplattingEditorStyle::ReloadTextures();    
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FGaussianSplattingEditorModule::RegisterMenus));
}

void FGaussianSplattingEditorModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
	FGaussianSplattingEditorStyle::Shutdown();
	FEditorModeRegistry::Get().UnregisterMode(FGaussianSplattingEdMode::EdID);
}

void FGaussianSplattingEditorModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("ContentBrowser.AssetContextMenu.GaussianSplattingPointCloud");
	FToolMenuSection& Section = Menu->FindOrAddSection("GetAssetActions");
	Section.AddDynamicEntry("GaussianSplattingEditor ", FNewToolMenuSectionDelegate::CreateLambda([this](FToolMenuSection& Section){
			if (UContentBrowserAssetContextMenuContext* Context = Section.FindContext<UContentBrowserAssetContextMenuContext>()){
				if (Context->SelectedAssets.Num() == 1) {
					UGaussianSplattingPointCloud* PointCloud = Cast<UGaussianSplattingPointCloud>(Context->SelectedAssets[0].GetAsset());
					if (PointCloud == nullptr)
						return;
					Section.AddMenuEntry(
						"GS_CreateNiagara",
						LOCTEXT("GS_CreateNiagara", "Create Niagara System"),
						LOCTEXT("GS_CreateNiagaraTooltip", "Create Niagara System"),
						FSlateIcon(FNiagaraEditorStyle::Get().GetStyleSetName(), "ClassIcon.NiagaraActor"),
						FUIAction(
							FExecuteAction::CreateRaw(this, &FGaussianSplattingEditorModule::CreateNiagara, PointCloud)
						)
					);

					//Section.AddMenuEntry(
					//	"GS_CreateStaticMesh",
					//	LOCTEXT("GS_CreateStaticMesh", "Create Static Mesh"),
					//	LOCTEXT("GS_CreateStaticMeshTooltip", "Create Static Mesh"),
					//	FSlateIcon(FAppStyle::GetAppStyleSetName(), "ClassIcon.StaticMeshActor"),
					//	FUIAction(
					//		FExecuteAction::CreateRaw(this, &FGaussianSplattingEditorModule::CreateStaticMesh, PointCloud)
					//	)
					//);
				}
			}
		}));
}

void FGaussianSplattingEditorModule::CreateStaticMesh(UGaussianSplattingPointCloud* PointCloud)
{
	if (PointCloud == nullptr) {
		return;
	}

	FSaveAssetDialogConfig SaveAssetDialogConfig;
	SaveAssetDialogConfig.DefaultPath = FPackageName::GetLongPackagePath(PointCloud->GetOutermost()->GetName());
	SaveAssetDialogConfig.DefaultAssetName = FString::Printf(TEXT("SM_%s"), *PointCloud->GetName());
	SaveAssetDialogConfig.AssetClassNames.Add(UGaussianSplattingStep_GaussianSplatting::StaticClass()->GetClassPathName());
	SaveAssetDialogConfig.ExistingAssetPolicy = ESaveAssetDialogExistingAssetPolicy::AllowButWarn;
	SaveAssetDialogConfig.DialogTitleOverride = FText::FromString("Save As");

	const FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	const FString SaveObjectPath = ContentBrowserModule.Get().CreateModalSaveAssetDialog(SaveAssetDialogConfig);
	if (SaveObjectPath.IsEmpty()){
		FNotificationInfo NotifyInfo(FText::FromString("Path is empty"));
		NotifyInfo.ExpireDuration = 5.0f;
		FSlateNotificationManager::Get().AddNotification(NotifyInfo);
		return;
	}
	const FString PackagePath = FPackageName::ObjectPathToPackageName(SaveObjectPath);
	const FString AssetName = FPaths::GetBaseFilename(PackagePath, true);
	if (!AssetName.IsEmpty()) {
		UPackage* NewPackage = CreatePackage(*PackagePath);
		UObject* NewAsset = UGaussianSplattingEditorLibrary::CreateStaticMeshFromPointCloud(PointCloud, NewPackage, *AssetName);
		NewAsset->SetFlags(RF_Public | RF_Standalone);
		FAssetRegistryModule::AssetCreated(NewAsset);
		FPackagePath NewPackagePath = FPackagePath::FromPackageNameChecked(NewPackage->GetName());
		FString PackageLocalPath = NewPackagePath.GetLocalFullPath();
		UPackage::SavePackage(NewPackage, NewAsset, RF_Public | RF_Standalone, *PackageLocalPath, GError, nullptr, false, true, SAVE_NoError);
		TArray<UObject*> ObjectsToSync;
		ObjectsToSync.Add(NewAsset);
		GEditor->SyncBrowserToObjects(ObjectsToSync);
	}
}

void FGaussianSplattingEditorModule::CreateNiagara(UGaussianSplattingPointCloud* PointCloud)
{
	if (PointCloud == nullptr) {
		return;
	}

	FSaveAssetDialogConfig SaveAssetDialogConfig;
	SaveAssetDialogConfig.DefaultPath = FPackageName::GetLongPackagePath(PointCloud->GetOutermost()->GetName());;
	SaveAssetDialogConfig.DefaultAssetName = FString::Printf(TEXT("FX_%s"), *PointCloud->GetName());
	SaveAssetDialogConfig.AssetClassNames.Add(UGaussianSplattingStep_GaussianSplatting::StaticClass()->GetClassPathName());
	SaveAssetDialogConfig.ExistingAssetPolicy = ESaveAssetDialogExistingAssetPolicy::AllowButWarn;
	SaveAssetDialogConfig.DialogTitleOverride = FText::FromString("Save As");

	const FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	const FString SaveObjectPath = ContentBrowserModule.Get().CreateModalSaveAssetDialog(SaveAssetDialogConfig);
	if (SaveObjectPath.IsEmpty()) {
		FNotificationInfo NotifyInfo(FText::FromString("Path is empty"));
		NotifyInfo.ExpireDuration = 5.0f;
		FSlateNotificationManager::Get().AddNotification(NotifyInfo);
		return;
	}

	const FString PackagePath = FPackageName::ObjectPathToPackageName(SaveObjectPath);
	const FString AssetName = FPaths::GetBaseFilename(PackagePath, true);
	if (!AssetName.IsEmpty()) {
		UPackage* NewPackage = CreatePackage(*PackagePath);
		UObject* NewAsset = UGaussianSplattingEditorLibrary::CreateNiagaraSystemFromPointCloud(PointCloud, NewPackage, *AssetName);
		NewAsset->SetFlags(RF_Public | RF_Standalone);
		FAssetRegistryModule::AssetCreated(NewAsset);
		FPackagePath NewPackagePath = FPackagePath::FromPackageNameChecked(NewPackage->GetName());
		FString PackageLocalPath = NewPackagePath.GetLocalFullPath();
		UPackage::SavePackage(NewPackage, NewAsset, RF_Public | RF_Standalone, *PackageLocalPath, GError, nullptr, false, true, SAVE_NoError);
		TArray<UObject*> ObjectsToSync;
		ObjectsToSync.Add(NewAsset);
		GEditor->SyncBrowserToObjects(ObjectsToSync);
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGaussianSplattingEditorModule, GaussianSplattingEditor)