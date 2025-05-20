#include "SGaussianSplattingPointCloudEditorViewportClient.h"
#include "SGaussianSplattingPointCloudEditorViewport.h"
#include "GaussianSplattingPointCloudEditor.h"
#include "CanvasTypes.h"
#include "CanvasItem.h"
#include "EditorDragTools.h"
#include "AdvancedPreviewScene.h"

class FDragTool_PointsFrustumSelect : public FDragTool
{
public:
	explicit FDragTool_PointsFrustumSelect(FGaussianSplattingPointCloudEditorViewportClient* InViewportClient)
		: FDragTool(InViewportClient->GetModeTools())
		, ViewportClient(InViewportClient)
	{

	}

	virtual void AddDelta(const FVector& InDelta) override {
		FIntPoint MousePos;
		ViewportClient->Viewport->GetMousePos(MousePos);

		EndWk = FVector(MousePos);
		End = EndWk;
	}

	virtual void StartDrag(FEditorViewportClient* InViewportClient, const FVector& InStart, const FVector2D& InStartScreen) override {
		FDragTool::StartDrag(InViewportClient, InStart, InStartScreen);

		const bool bUseHoverFeedback = GEditor != NULL && GetDefault<ULevelEditorViewportSettings>()->bEnableViewportHoverFeedback;

		FIntPoint MousePos;
		InViewportClient->Viewport->GetMousePos(MousePos);

		Start = FVector(InStartScreen.X, InStartScreen.Y, 0);
		End = EndWk = Start;
	}

	virtual void EndDrag() override {
		const int32 ViewportSizeX = ViewportClient->Viewport->GetSizeXY().X;
		const int32 ViewportSizeY = ViewportClient->Viewport->GetSizeXY().Y;
		if (Start.X > End.X){
			Swap(Start.X, End.X);
		}
		if (Start.Y > End.Y){
			Swap(Start.Y, End.Y);
		}

		TSharedRef<FAdvancedPreviewScene> PreviewScene = ViewportClient->GetEditor()->GetViewport()->GetPreviewScene();
		UNiagaraComponent* PreviewComponent = ViewportClient->GetEditor()->GetViewport()->GetPreviewComponent();
		UGaussianSplattingPointCloud* PointCloud = ViewportClient->GetEditor()->PointCloud;
		const TArray<FGaussianSplattingPoint>& Points = PointCloud->GetPoints();

		FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(ViewportClient->Viewport, PreviewScene->GetScene(), ViewportClient->EngineShowFlags));
		FSceneView* View = ViewportClient->CalcSceneView(&ViewFamily);
		const FMatrix& ViewMatrix = View->ViewMatrices.GetViewMatrix();
		const FMatrix& ProjectionMatrix = View->ViewMatrices.GetProjectionMatrix();
		const FMatrix ModelMatrix = PreviewComponent->GetComponentTransform().ToMatrixWithScale();
		FMatrix MVPMatrix = ModelMatrix * ViewMatrix * ProjectionMatrix;

		TArray<uint32> SelectedIndices;

		for (int i = 0; i < Points.Num(); i++) {
			FVector4 Point(Points[i].Position);	
			FVector4 TransformedPoint = MVPMatrix.TransformFVector4(Point);
			if (TransformedPoint.W != 0.0f) {
				TransformedPoint /= TransformedPoint.W;
			}
			FVector2D ViewportPoint;
			ViewportPoint.X = (TransformedPoint.X + 1.0f) * 0.5f * ViewportSizeX;
			ViewportPoint.Y = (1.0f - (TransformedPoint.Y + 1.0f) * 0.5f) * ViewportSizeY;
			bool bIsInside = (ViewportPoint.X >= Start.X) && (ViewportPoint.X <= End.X) &&
				(ViewportPoint.Y >= Start.Y) && (ViewportPoint.Y <= End.Y);
			if (bIsInside) {
				SelectedIndices.Add(i);
			}
		}
		ViewportClient->GetEditor()->ClearPropertyEditorSelection();
		ViewportClient->GetEditor()->SelectPointsByIndex(SelectedIndices);
		FDragTool::EndDrag();
	}
	virtual void Render(const FSceneView* View, FCanvas* Canvas) override {
		FCanvasBoxItem BoxItem(FVector2D(Start.X, Start.Y) / Canvas->GetDPIScale(), FVector2D(End.X - Start.X, End.Y - Start.Y) / Canvas->GetDPIScale());
		BoxItem.SetColor(FLinearColor::White);
		Canvas->DrawItem(BoxItem);


	}
private:
	FGaussianSplattingPointCloudEditorViewportClient* ViewportClient;
};


void FGaussianSplattingPointCloudEditorViewportClient::SetEditor(TWeakPtr<FGaussianSplattingPointCloudEditor> InEditor)
{
	Editor = InEditor;
}

FGaussianSplattingPointCloudEditor* FGaussianSplattingPointCloudEditorViewportClient::GetEditor()
{
	return Editor.Pin().Get();
}

void FGaussianSplattingPointCloudEditorViewportClient::Tick(float DeltaSeconds)
{
	FEditorViewportClient::Tick(DeltaSeconds);
	PreviewScene->GetWorld()->Tick(LEVELTICK_All, DeltaSeconds);
}

void FGaussianSplattingPointCloudEditorViewportClient::DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas)
{
	FEditorViewportClient::DrawCanvas(InViewport, View, Canvas);
}

bool FGaussianSplattingPointCloudEditorViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
	if (EventArgs.Key == EKeys::Delete && EventArgs.Event == IE_Pressed) {
		Editor.Pin()->RemoveSelectedPoints();
	}
	return FEditorViewportClient::InputKey(EventArgs);
}

TSharedPtr<FDragTool> FGaussianSplattingPointCloudEditorViewportClient::MakeDragTool(EDragTool::Type DragToolType)
{
	TSharedPtr<FDragTool> DragTool;
	switch (DragToolType){
	case EDragTool::BoxSelect:
		DragTool = MakeShareable(new FDragTool_PointsFrustumSelect(this));
		break;
	case EDragTool::FrustumSelect:
		DragTool = MakeShareable(new FDragTool_PointsFrustumSelect(this));
		break;
	case EDragTool::Measure:
		break;
	case EDragTool::ViewportChange:
		break;
	};
	return DragTool;
}
