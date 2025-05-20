#include "SGaussianSplattingEdModePanel.h"
#include "Widgets/Layout/SWrapBox.h"
#include "GaussianSplattingEditorStyle.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Misc/Optional.h"
#include "LevelEditor.h"
#include "ThumbnailRendering/ThumbnailManager.h"
#include "GaussianSplattingEditorSettings.h"
#include "Widgets/Notifications/SProgressBar.h"
#include "IContentBrowserSingleton.h"
#include "ContentBrowserModule.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Framework/Notifications/NotificationManager.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Widgets/Input/SSegmentedControl.h"
#include "PropertyCustomizationHelpers.h"

#define LOCTEXT_NAMESPACE "GaussianSplatting"

SGaussianSplattingEdModePanel::~SGaussianSplattingEdModePanel()
{
	if (StepCapture) {
		StepCapture->Deactivate();
	}
	if (StepSparseReconstruction) {
		StepSparseReconstruction->Deactivate();
	}	
	if (StepGaussianSplatting) {
		StepGaussianSplatting->Deactivate();
	}
}

void SGaussianSplattingEdModePanel::Construct(const FArguments& InArgs)
{
	FPropertyEditorModule& EditModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;
	//DetailsViewArgs.bAllowMultipleTopLevelObjects = true;
	DetailsViewArgs.bShowObjectLabel = false;
	DetailsViewArgs.bAllowSearch = true;
	DetailsViewArgs.bAllowFavoriteSystem = true;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::ENameAreaSettings::HideNameArea;
	DetailsViewArgs.ViewIdentifier = FName("BlueprintDefaults");
	DetailsView = EditModule.CreateDetailView(DetailsViewArgs);
	DetailsView->OnFinishedChangingProperties().AddSP(this, &SGaussianSplattingEdModePanel::OnTabPropertyChanged);

	UWorld* EditorWorld = GEditor->GetEditorWorldContext().World();

	bool bPackageDirty = EditorWorld->GetPackage()->IsDirty();

	UObject* Outer = EditorWorld != nullptr ? EditorWorld->GetPackage() : GetTransientPackage();
	WorkDir = GetDefault<UGaussianSplattingEditorSettings>()->GetWorkDir("GaussianSplattingEditor");

	StepCapture = NewObject<UGaussianSplattingStep_Capture>(Outer, NAME_None, RF_Transient);
	StepSparseReconstruction = NewObject<UGaussianSplattingStep_SparseReconstruction>(Outer, NAME_None, RF_Transient);
	StepGaussianSplatting = NewObject<UGaussianSplattingStep_GaussianSplatting>(Outer, NAME_None, RF_Transient);

	StepCapture->SetWorld(EditorWorld);
	StepCapture->SetWorkDir(WorkDir);
	StepCapture->LoadConfig();
	StepCapture->Activate();

	StepSparseReconstruction->SetWorld(EditorWorld);
	StepSparseReconstruction->SetWorkDir(WorkDir);
	StepSparseReconstruction->LoadConfig();
	StepSparseReconstruction->Activate();

	StepGaussianSplatting->SetWorld(EditorWorld);
	StepGaussianSplatting->SetWorkDir(WorkDir);
	StepGaussianSplatting->LoadConfig();
	StepGaussianSplatting->Activate();

	if (!bPackageDirty) {
		EditorWorld->GetPackage()->SetDirtyFlag(false);
	}

	StepCapture->OnRequestTaskStart.BindSP(this, &SGaussianSplattingEdModePanel::OnRequestTaskStart, (UGaussianSplattingStepBase*) StepCapture.Get());
	StepSparseReconstruction->OnRequestTaskStart.BindSP(this, &SGaussianSplattingEdModePanel::OnRequestTaskStart, (UGaussianSplattingStepBase*)StepSparseReconstruction.Get());
	StepGaussianSplatting->OnRequestTaskStart.BindSP(this, &SGaussianSplattingEdModePanel::OnRequestTaskStart, (UGaussianSplattingStepBase*)StepGaussianSplatting.Get());

	StepCapture->OnTaskFinished.AddSP(this, &SGaussianSplattingEdModePanel::OnTaskFinished, (UGaussianSplattingStepBase*)StepCapture.Get());
	StepSparseReconstruction->OnTaskFinished.AddSP(this, &SGaussianSplattingEdModePanel::OnTaskFinished, (UGaussianSplattingStepBase*)StepSparseReconstruction.Get());
	StepGaussianSplatting->OnTaskFinished.AddSP(this, &SGaussianSplattingEdModePanel::OnTaskFinished, (UGaussianSplattingStepBase*)StepGaussianSplatting.Get());

	ChildSlot
		[
		SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.Padding(0)
			.AutoHeight()
			.MaxHeight(100)
			.VAlign(VAlign_Top)
			[
				SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.FillWidth(100)
					[
						SNew(SSegmentedControl<int32>)
							.Value(0) // InitialValue
							.OnValueChanged(this, &SGaussianSplattingEdModePanel::OnTabChanged)
							+ SSegmentedControl<int32>::Slot(0)
							.Icon(FGaussianSplattingEditorStyle::Get().GetBrush("GaussianSplattingEditor.Capture"))
							.Text(LOCTEXT("Capture", "Capture"))

							+ SSegmentedControl<int32>::Slot(1)
							.Icon(FGaussianSplattingEditorStyle::Get().GetBrush("GaussianSplattingEditor.SparseReconstruction"))
							.Text(LOCTEXT("Sparse", "Sparse"))

							+ SSegmentedControl<int32>::Slot(2)
							.Icon(FGaussianSplattingEditorStyle::Get().GetBrush("GaussianSplattingEditor.GaussianSplatting"))
							.Text(LOCTEXT("Gaussian", "Gaussian"))

							+ SSegmentedControl<int32>::Slot(3)
							.Icon(FAppStyle::Get().GetBrush("Icons.Settings"))
							.Text(LOCTEXT("Settings", "Settings"))
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(5)
					[
						PropertyCustomizationHelpers::MakeBrowseButton(
							FSimpleDelegate::CreateSP(this, &SGaussianSplattingEdModePanel::OnClicked_Browse),
							FText()
						)
					]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Fill)
			.Padding(10, 5)
			[
				SNew(SHorizontalBox)
					.Visibility(this, &SGaussianSplattingEdModePanel::OnGetProgressBarVisibility)
					+ SHorizontalBox::Slot()
					.FillWidth(100)
					[
						SNew(SBox)
							.HeightOverride(5)
							[
								SNew(SProgressBar)
									.Percent(this, &SGaussianSplattingEdModePanel::OnGetProgressPercent)
									.FillColorAndOpacity(FSlateColor(FLinearColor(0.0f, 1.0f, 1.0f)))
							]
					]
					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					.AutoWidth()
					.Padding(5, 0)
					[
						SNew(SButton)
							.ToolTipText(LOCTEXT("Cancel", "Cancel Current Task"))
							.OnClicked(this, &SGaussianSplattingEdModePanel::OnClicked_Cancel)
							.ContentPadding(0.0f)
							[
								SNew(SImage)
									.Image(FAppStyle::GetBrush("Symbols.X"))
									.DesiredSizeOverride(FVector2D(12, 12))
									.ColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f))
							]
					]
			]
			+SVerticalBox::Slot()
			.VAlign(VAlign_Fill)
			.FillHeight(100)
			[
				DetailsView.ToSharedRef()
			]
	];

	OnTabChanged(0);
}

void SGaussianSplattingEdModePanel::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(StepCapture);
	Collector.AddReferencedObject(StepSparseReconstruction);
	Collector.AddReferencedObject(StepGaussianSplatting);
}

void SGaussianSplattingEdModePanel::OnTabChanged(int32 TabIndex)
{
	UObject* ObjectToEdit = nullptr;
	if (TabIndex == 0) {
		ObjectToEdit = StepCapture;
	}
	else if (TabIndex == 1) {
		ObjectToEdit = StepSparseReconstruction;
	}
	else if (TabIndex == 2) {
		ObjectToEdit = StepGaussianSplatting;
	}
	else {
		ObjectToEdit = GetMutableDefault<UGaussianSplattingEditorSettings>();
	}
	DetailsView->SetObject(ObjectToEdit);
}

void SGaussianSplattingEdModePanel::OnTabPropertyChanged(const FPropertyChangedEvent& ChangedEvent)
{
	if (ChangedEvent.GetNumObjectsBeingEdited() == 1) {
		if (UObject* ObjectToEdit = const_cast<UObject*>(ChangedEvent.GetObjectBeingEdited(0))) {
			ObjectToEdit->TryUpdateDefaultConfigFile();
		}
	}
}

bool SGaussianSplattingEdModePanel::OnRequestTaskStart(UGaussianSplattingStepBase* Step)
{
	if (CurrentTask != nullptr) {
		FNotificationInfo NotifyInfo(LOCTEXT("ExecutionFailed", "Execution failed\n there is currently a running task"));
		NotifyInfo.ExpireDuration = 5.0f;
		NotifyInfo.bUseSuccessFailIcons = true;
		TSharedPtr<SNotificationItem> NotificationPtr = FSlateNotificationManager::Get().AddNotification(NotifyInfo);
		if (NotificationPtr){
			NotificationPtr->SetCompletionState(SNotificationItem::CS_Fail);
		}
		return false;
	}
	CurrentTask = Step;
	return true;
}

EVisibility SGaussianSplattingEdModePanel::OnGetProgressBarVisibility() const
{
	return CurrentTask ? EVisibility::Visible : EVisibility::Hidden;
}

TOptional<float> SGaussianSplattingEdModePanel::OnGetProgressPercent() const
{
	return CurrentTask ? CurrentTask->TaskProgressPercent : 0;
}

void SGaussianSplattingEdModePanel::OnTaskFinished(UGaussianSplattingStepBase* Step)
{
	CurrentTask = nullptr;
}

void SGaussianSplattingEdModePanel::OnClicked_Browse()
{
	if (!IFileManager::Get().DirectoryExists(*WorkDir))
		return;
	FPlatformProcess::ExploreFolder(*WorkDir);
}

FReply SGaussianSplattingEdModePanel::OnClicked_Cancel()
{
	if (CurrentTask) {
		CurrentTask->bRequestCancelTask = true;
	}
	return FReply::Handled();
}

//FReply SGaussianSplattingEdModePanel::OnClicked_Export()
//{
//	UObject* Cache = AssetThumbnail->GetAsset();
//	if (!Cache) {
//		return FReply::Handled();
//	}
//	FSaveAssetDialogConfig SaveAssetDialogConfig;
//	SaveAssetDialogConfig.DefaultPath = LastSavePath;
//	SaveAssetDialogConfig.DefaultAssetName = "GaussianSplattingPoints";
//	SaveAssetDialogConfig.AssetClassNames.Add(UTexture2D::StaticClass()->GetClassPathName());
//	SaveAssetDialogConfig.ExistingAssetPolicy = ESaveAssetDialogExistingAssetPolicy::AllowButWarn;
//	SaveAssetDialogConfig.DialogTitleOverride = FText::FromString("Save As");
//
//	const FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
//	const FString SaveObjectPath = ContentBrowserModule.Get().CreateModalSaveAssetDialog(SaveAssetDialogConfig);
//	if (SaveObjectPath.IsEmpty()){
//		FNotificationInfo NotifyInfo(FText::FromString("Path is empty"));
//		NotifyInfo.ExpireDuration = 5.0f;
//		FSlateNotificationManager::Get().AddNotification(NotifyInfo);
//		return FReply::Handled();
//	}
//	const FString PackagePath = FPackageName::ObjectPathToPackageName(SaveObjectPath);
//	const FString AssetName = FPaths::GetBaseFilename(PackagePath, true);
//	LastSavePath = PackagePath;
//	if (!AssetName.IsEmpty()) {
//		UPackage* NewPackage = CreatePackage(*PackagePath);
//		UObject* NewAsset = DuplicateObject<UObject>(Cache, NewPackage, *AssetName);
//		NewAsset->SetFlags(RF_Public | RF_Standalone);
//		FAssetRegistryModule::AssetCreated(NewAsset);
//		FPackagePath NewPackagePath = FPackagePath::FromPackageNameChecked(NewPackage->GetName());
//		FString PackageLocalPath = NewPackagePath.GetLocalFullPath();
//		UPackage::SavePackage(NewPackage, NewAsset, RF_Public | RF_Standalone, *PackageLocalPath, GError, nullptr, false, true, SAVE_NoError);
//		TArray<UObject*> ObjectsToSync;
//		ObjectsToSync.Add(NewAsset);
//		GEditor->SyncBrowserToObjects(ObjectsToSync);
//		AssetThumbnail->SetAsset(NewAsset);
//		AssetThumbnailBox->SetContent(
//			AssetThumbnail->MakeThumbnailWidget()
//		);
//	}
//	return FReply::Handled();
//}


FText SGaussianSplattingEdModePanel::OnGetStatusText() const
{
	//if (CurrentSelectedStepObject)
	//	return CurrentSelectedStepObject->LastStatusText;
	return FText();
}

#undef LOCTEXT_NAMESPACE
