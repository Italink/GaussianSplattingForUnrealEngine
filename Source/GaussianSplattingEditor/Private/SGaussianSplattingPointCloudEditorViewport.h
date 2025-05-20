#pragma once

#include "CoreMinimal.h"
#include "Widgets/SWidget.h"
#include "SEditorViewport.h"
#include "AssetEditorViewportLayout.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "SAssetEditorViewport.h"

class FEditorViewportClient;
class FViewportTabContent;
class FMenuBuilder;
class FAdvancedPreviewScene;
class FGaussianSplattingPointCloudEditor;

class SGaussianSplattingPointCloudEditorViewport : public SAssetEditorViewport
{
	SLATE_BEGIN_ARGS(SGaussianSplattingPointCloudEditorViewport) {}
		SLATE_ARGUMENT(TWeakPtr<FGaussianSplattingPointCloudEditor>, Editor)
	SLATE_END_ARGS()
public:
	void Construct(const FArguments& InArgs);
	TObjectPtr<UNiagaraComponent> GetPreviewComponent() { return PreviewComponent; }
	TSharedRef<FAdvancedPreviewScene> GetPreviewScene() { return PreviewScene.ToSharedRef(); }
protected:
	virtual void BindCommands() override {}
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
private:
	TWeakPtr<FGaussianSplattingPointCloudEditor> Editor;
	TSharedPtr<FAdvancedPreviewScene> PreviewScene;
	TObjectPtr<UNiagaraComponent> PreviewComponent = nullptr;
};
