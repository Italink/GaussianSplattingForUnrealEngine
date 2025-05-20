#include "GaussianSplattingPointCloudEditor.h"
#include "AssetEditorModeManager.h"
#include "SGaussianSplattingPointCloudEditorViewport.h"
#include "GaussianSplattingEditorLibrary.h"
#include "EditorViewportTabContent.h"
#include "AdvancedPreviewSceneModule.h"
#include "SGaussianSplattingPointCloudFeatureEditor.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"

#define LOCTEXT_NAMESPACE "GaussianSplatting"

const FName GaussianSplattingPointCloudEditorAppIdentifier = FName(TEXT("GaussianSplattingPointCloudEditorApp"));
const FName FGaussianSplattingPointCloudEditor::ViewportTabId(TEXT("GaussianSplattingPointCloudEditor_Viewport"));
const FName FGaussianSplattingPointCloudEditor::PropertiesTabId(TEXT("GaussianSplattingPointCloudEditor_Properties"));
const FName FGaussianSplattingPointCloudEditor::PreviewSceneSettingsTabId(TEXT("GaussianSplattingPointCloudEditor_PreviewScene"));
const FName FGaussianSplattingPointCloudEditor::FeatureEditorTabId(TEXT("GaussianSplattingPointCloudEditor_Features"));

FGaussianSplattingPointCloudEditor::~FGaussianSplattingPointCloudEditor()
{
	GEditor->UnregisterForUndo(this);
}

UGaussianSplattingPointCloud* FGaussianSplattingPointCloudEditor::GetPointCloud()
{
	return PointCloud;
}

void FGaussianSplattingPointCloudEditor::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UGaussianSplattingPointCloud* ObjectToEdit)
{
	PointCloud = ObjectToEdit;
	PointCloud->SetFlags(RF_Transactional);
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_GaussianSplattingPointCloudEditor_Layout_v6")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.7f)
					->Split
					(
						FTabManager::NewStack()
						->AddTab(ViewportTabId, ETabState::OpenedTab)
						->SetSizeCoefficient(0.8f)
						->SetHideTabWell(true)
					)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.2f)
						->AddTab(FeatureEditorTabId, ETabState::OpenedTab)
						->SetHideTabWell(true)
					)
				)
				->Split
				(
					FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.25f)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.7f)
						->AddTab(PropertiesTabId, ETabState::OpenedTab)
						->SetForegroundTab(PropertiesTabId)
					)
				)
			)
		);

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, GaussianSplattingPointCloudEditorAppIdentifier, StandaloneDefaultLayout, bCreateDefaultToolbar, bCreateDefaultStandaloneMenu, ObjectToEdit);

	GEditor->RegisterForUndo(this);
}

void FGaussianSplattingPointCloudEditor::SelectPointsByIndex(TArray<uint32> InIndices)
{
	SelectedIndices = InIndices;
	TArray<bool> Selection;
	Selection.AddZeroed(PointCloud->GetPointCount());
	for (auto Index : InIndices) {
		Selection[Index] = true;
	}
	UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayBool(GetViewport()->GetPreviewComponent(), "Selection", Selection);
}

void FGaussianSplattingPointCloudEditor::RemovePointsByIndex(TArray<uint32> InIndices)
{
	if (!InIndices.IsEmpty()) {
		TArray<FGaussianSplattingPoint> Points = PointCloud->GetPoints();
		InIndices.Sort();
		for (int32 i = InIndices.Num() - 1; i >= 0; --i){
			int32 IndexToRemove = InIndices[i];
			if (IndexToRemove < Points.Num()){
				Points.RemoveAt(IndexToRemove);
			}
		}

		GEditor->BeginTransaction(LOCTEXT("RemovePoints", "Remove Points"));       
		PointCloud->Modify();               
		PointCloud->SetPoints(Points);
		GEditor->EndTransaction();      
	}
	SelectPointsByIndex({});
}

void FGaussianSplattingPointCloudEditor::RemoveSelectedPoints()
{
	RemovePointsByIndex(SelectedIndices);
}

void FGaussianSplattingPointCloudEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_GaussianSplattingPointCloudEditor", "Gaussian Splatting Point Cloud Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(ViewportTabId, FOnSpawnTab::CreateSP(this, &FGaussianSplattingPointCloudEditor::SpawnTab_Viewport))
		.SetDisplayName(LOCTEXT("ViewportTab", "Viewport"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Viewports"))
		.SetReadOnlyBehavior(ETabReadOnlyBehavior::Custom);

	InTabManager->RegisterTabSpawner(PropertiesTabId, FOnSpawnTab::CreateSP(this, &FGaussianSplattingPointCloudEditor::SpawnTab_Properties))
		.SetDisplayName(LOCTEXT("PropertiesTab", "Details"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"))
		.SetReadOnlyBehavior(ETabReadOnlyBehavior::Custom);

	InTabManager->RegisterTabSpawner(PreviewSceneSettingsTabId, FOnSpawnTab::CreateSP(this, &FGaussianSplattingPointCloudEditor::SpawnTab_PreviewSceneSettings))
		.SetDisplayName(LOCTEXT("PreviewSceneTab", "Preview Scene Settings"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"))
		.SetReadOnlyBehavior(ETabReadOnlyBehavior::Custom);

	InTabManager->RegisterTabSpawner(FeatureEditorTabId, FOnSpawnTab::CreateSP(this, &FGaussianSplattingPointCloudEditor::SpawnTab_FeatureEditor))
		.SetDisplayName(LOCTEXT("PropertiesTab", "Features"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Features"))
		.SetReadOnlyBehavior(ETabReadOnlyBehavior::Custom);
}

void FGaussianSplattingPointCloudEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(ViewportTabId);
	InTabManager->UnregisterTabSpawner(PropertiesTabId);
}

TSharedRef<SDockTab> FGaussianSplattingPointCloudEditor::SpawnTab_Viewport(const FSpawnTabArgs& Args)
{
	TSharedRef<SDockTab> DockableTab = SNew(SDockTab);
	
	TWeakPtr<FGaussianSplattingPointCloudEditor> WeakSharedThis(SharedThis(this));
	AssetEditorViewportFactoryFunction MakeViewportFunc = [WeakSharedThis](const FAssetEditorViewportConstructionArgs& InArgs)
		{
			return SNew(SGaussianSplattingPointCloudEditorViewport)
				.Editor(WeakSharedThis);
		};

	ViewportTabContent = MakeShareable(new FEditorViewportTabContent());
	ViewportTabContent->OnViewportTabContentLayoutChanged().AddRaw(this, &FGaussianSplattingPointCloudEditor::OnEditorLayoutChanged);

	const FString LayoutId = FString("GaussianSplattingPointCloudEditorViewport");
	ViewportTabContent->Initialize(MakeViewportFunc, DockableTab, LayoutId);
	return DockableTab;
}

TSharedRef<SDockTab> FGaussianSplattingPointCloudEditor::SpawnTab_Properties(const FSpawnTabArgs& Args)
{
	FPropertyEditorModule& EditModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;
	//DetailsViewArgs.bAllowMultipleTopLevelObjects = true;
	DetailsViewArgs.bShowObjectLabel = false;
	DetailsViewArgs.bAllowSearch = true;
	DetailsViewArgs.bAllowFavoriteSystem = true;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::ENameAreaSettings::HideNameArea;
	DetailsViewArgs.ViewIdentifier = FName("BlueprintDefaults");
	auto DetailsView = EditModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(PointCloud);
	TWeakPtr<FGaussianSplattingPointCloudEditor> WeakSharedThis(SharedThis(this));
	TSharedRef<SDockTab> DockableTab = SNew(SDockTab)
		[
			DetailsView
		];
	return DockableTab;
}

TSharedRef<SDockTab> FGaussianSplattingPointCloudEditor::SpawnTab_FeatureEditor(const FSpawnTabArgs& Args)
{
	TWeakPtr<FGaussianSplattingPointCloudEditor> WeakSharedThis(SharedThis(this));
	TSharedRef<SDockTab> DockableTab = SNew(SDockTab)
		[
			SAssignNew(FeatureEditor, SGaussianSplattingPointCloudFeatureEditor)
				.Editor(WeakSharedThis)
		];
	return DockableTab;
}

TSharedRef<SDockTab> FGaussianSplattingPointCloudEditor::SpawnTab_PreviewSceneSettings(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == PreviewSceneSettingsTabId);
	return SAssignNew(PreviewSceneDockTab, SDockTab)
		.Label(LOCTEXT("StaticMeshPreviewScene_TabTitle", "Preview Scene Settings"))
		[
			AdvancedPreviewSettingsWidget.IsValid() ? AdvancedPreviewSettingsWidget.ToSharedRef() : SNullWidget::NullWidget
		];
}

void FGaussianSplattingPointCloudEditor::PostInitAssetEditor()
{

}

void FGaussianSplattingPointCloudEditor::CreateEditorModeManager()
{
	TSharedPtr<FAssetEditorModeManager> NewManager = MakeShared<FAssetEditorModeManager>();
	EditorModeManager = NewManager;
}

TSharedPtr<class SGaussianSplattingPointCloudEditorViewport> FGaussianSplattingPointCloudEditor::GetViewport() const
{
	if (ViewportTabContent.IsValid()){
		return StaticCastSharedPtr<SGaussianSplattingPointCloudEditorViewport>(ViewportTabContent->GetFirstViewport());
	}
	return TSharedPtr<SGaussianSplattingPointCloudEditorViewport>();
}

void FGaussianSplattingPointCloudEditor::ClearPropertyEditorSelection()
{
	FeatureEditor->ClearSelection();
}

void FGaussianSplattingPointCloudEditor::OnEditorLayoutChanged()
{
	TSharedPtr<class SGaussianSplattingPointCloudEditorViewport> Viewport = GetViewport();
	FAdvancedPreviewSceneModule& AdvancedPreviewSceneModule = FModuleManager::LoadModuleChecked<FAdvancedPreviewSceneModule>("AdvancedPreviewScene");

	AdvancedPreviewSettingsWidget = AdvancedPreviewSceneModule.CreateAdvancedPreviewSceneSettingsWidget(Viewport->GetPreviewScene(), nullptr, TArray<FAdvancedPreviewSceneModule::FDetailCustomizationInfo>(), TArray<FAdvancedPreviewSceneModule::FPropertyTypeCustomizationInfo>());
	if (PreviewSceneDockTab.IsValid()){
		PreviewSceneDockTab.Pin()->SetContent(AdvancedPreviewSettingsWidget.ToSharedRef());
	}
	UNiagaraSystem* DebugNiagraSystem = LoadObject<UNiagaraSystem>(nullptr, TEXT("/GaussianSplattingForUnrealEngine/Niagara/NS_GaussianSplattingPointCloudDebug.NS_GaussianSplattingPointCloudDebug"));
	UGaussianSplattingEditorLibrary::SetupPointCloudToNiagaraComponent(PointCloud, Viewport->GetPreviewComponent(), DebugNiagraSystem);
}

void FGaussianSplattingPointCloudEditor::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(PointCloud);
}

FString FGaussianSplattingPointCloudEditor::GetReferencerName() const
{
	return TEXT("FGaussianSplattingPointCloudEditor");
}

void FGaussianSplattingPointCloudEditor::PostUndo(bool bSuccess)
{
	if (PointCloud) {
		PointCloud->OnPointsChanged.Broadcast();
	}
}

void FGaussianSplattingPointCloudEditor::PostRedo(bool bSuccess)
{
	if (PointCloud) {
		PointCloud->OnPointsChanged.Broadcast();
	}
}

FName FGaussianSplattingPointCloudEditor::GetToolkitFName() const
{
	return FName("GaussianSplattingPointCloudEditor");
}

FText FGaussianSplattingPointCloudEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Gaussian Splatting Point Cloud Editor");
}

FString FGaussianSplattingPointCloudEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "GaussianSplattingPointCloud").ToString();
}

FLinearColor FGaussianSplattingPointCloudEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}

FString FGaussianSplattingPointCloudEditor::GetDocumentationLink() const
{
	return FString(TEXT("Engine/Content/Types/GaussianSplattingPointCloud/Editor"));
}

#undef LOCTEXT_NAMESPACE