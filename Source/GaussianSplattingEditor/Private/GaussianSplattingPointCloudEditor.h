#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineBaseTypes.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "GaussianSplattingPointCloud.h"

class FGaussianSplattingPointCloudEditor : public FAssetEditorToolkit, public FGCObject, public FEditorUndoClient
{
public:
	~FGaussianSplattingPointCloudEditor();
	UGaussianSplattingPointCloud* GetPointCloud();
	void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UGaussianSplattingPointCloud* ObjectToEdit);
	void SelectPointsByIndex(TArray<uint32> InIndices);
	void RemovePointsByIndex(TArray<uint32> InIndices);
	void RemoveSelectedPoints();
	TSharedPtr<class SGaussianSplattingPointCloudEditorViewport> GetViewport() const;
	void ClearPropertyEditorSelection();
protected:
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetDocumentationLink() const override;

	virtual void PostInitAssetEditor() override;
	void CreateEditorModeManager() override;
	void OnEditorLayoutChanged();

	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;

	TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_FeatureEditor(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_PreviewSceneSettings(const FSpawnTabArgs& Args);

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override;

	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override;
public:
	static const FName ViewportTabId;
	static const FName PropertiesTabId;
	static const FName PreviewSceneSettingsTabId;
	static const FName FeatureEditorTabId;

	TObjectPtr<UGaussianSplattingPointCloud> PointCloud;
	TSharedPtr<class FEditorViewportTabContent> ViewportTabContent;
	TSharedPtr<SWidget> AdvancedPreviewSettingsWidget;
	TWeakPtr<SDockTab> PreviewSceneDockTab;
	TSharedPtr<class SGaussianSplattingPointCloudFeatureEditor> FeatureEditor;
	TArray<uint32> SelectedIndices;
};


