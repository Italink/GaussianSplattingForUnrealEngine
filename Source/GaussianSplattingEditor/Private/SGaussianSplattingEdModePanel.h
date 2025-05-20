#pragma once

#include "Components/DirectionalLightComponent.h"
#include "Engine/SceneCapture2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "HAL/RunnableThread.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Input/STextComboBox.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "Widgets/Input/SSuggestionTextBox.h"
#include "GaussianSplattingStep.h"
#include "AssetThumbnail.h"
#include "Misc/Optional.h"

class SGaussianSplattingEdModePanel : public SCompoundWidget, public FGCObject
{
public:
	SLATE_BEGIN_ARGS(SGaussianSplattingEdModePanel) {}
	SLATE_END_ARGS()
public:
	~SGaussianSplattingEdModePanel();
	void Construct(const FArguments& InArgs);
protected:
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	virtual FString GetReferencerName() const override { return TEXT("GaussianSplattingEditor"); }

	void OnTabChanged(int32 TabIndex);

	void OnTabPropertyChanged(const FPropertyChangedEvent& ChangedEvent);

	bool OnRequestTaskStart(UGaussianSplattingStepBase* Step);

	EVisibility OnGetProgressBarVisibility() const;

	TOptional<float> OnGetProgressPercent() const;

	void OnTaskFinished(UGaussianSplattingStepBase* Step);

	void OnClicked_Browse();

	FReply OnClicked_Cancel();

	FText OnGetStatusText() const;

private:
	FString WorkDir;
	TSharedPtr<IDetailsView> DetailsView;
	TObjectPtr<UGaussianSplattingStep_Capture> StepCapture;
	TObjectPtr<UGaussianSplattingStep_SparseReconstruction> StepSparseReconstruction;
	TObjectPtr<UGaussianSplattingStep_GaussianSplatting> StepGaussianSplatting;

	TObjectPtr<UGaussianSplattingStepBase> CurrentTask;
	TSharedPtr<FRunnable> Worker;
	TSharedPtr<FRunnableThread> WorkThread;
	FString LastSavePath;
};