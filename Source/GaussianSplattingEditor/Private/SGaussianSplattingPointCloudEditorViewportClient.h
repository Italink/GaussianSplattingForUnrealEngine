#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"

class FGaussianSplattingPointCloudEditor;

class FGaussianSplattingPointCloudEditorViewportClient : public FEditorViewportClient
{
public:
	using FEditorViewportClient::FEditorViewportClient;
	void SetEditor(TWeakPtr<FGaussianSplattingPointCloudEditor> InEditor);
	FGaussianSplattingPointCloudEditor* GetEditor();
protected:
	void Tick(float DeltaSeconds) override;
	void DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas) override;
	bool InputKey(const FInputKeyEventArgs& EventArgs) override;
	TSharedPtr<FDragTool> MakeDragTool(EDragTool::Type DragToolType) override;

private:
	TWeakPtr<FGaussianSplattingPointCloudEditor> Editor;
};
