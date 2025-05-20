#pragma once

#include "Widgets/SCompoundWidget.h"

class FGaussianSplattingPointCloudEditor;

class SGaussianSplattingPointCloudFeatureEditor : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SGaussianSplattingPointCloudFeatureEditor) {}
		SLATE_ARGUMENT(TWeakPtr<FGaussianSplattingPointCloudEditor>, Editor)
	SLATE_END_ARGS()
public:
	void Construct(const FArguments& InArgs);
	void ClearSelection();
protected:
	virtual bool SupportsKeyboardFocus() const override { return true; }
	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
private:
	TWeakPtr<FGaussianSplattingPointCloudEditor> Editor;
	TSharedPtr<class SGaussianSplattingPointCloudHistogram> Histogram;
};
