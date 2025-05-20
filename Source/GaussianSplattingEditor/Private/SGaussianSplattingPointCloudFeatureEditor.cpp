#include "SGaussianSplattingPointCloudFeatureEditor.h"
#include "GaussianSplattingPointCloud.h"
#include "GaussianSplattingPointCloudEditor.h"

#define MAKE_PAINT_GEOMETRY_PT(Geometry, X, Y)       Geometry.ToPaintGeometry(FSlateLayoutTransform(1.0f, FVector2D(X, Y)))
#define MAKE_PAINT_GEOMETRY_RC(Geometry, X, Y, W, H) Geometry.ToPaintGeometry(FVector2D(W, H), FSlateLayoutTransform(1.0f, FVector2D(X, Y)))

class SGaussianSplattingPointCloudHistogram : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGaussianSplattingPointCloudHistogram) {}
		SLATE_ARGUMENT(TObjectPtr<UGaussianSplattingPointCloud>, PointCloud)
	SLATE_END_ARGS()
public:
	void Construct(const FArguments& InArgs) {
		PointCloud = InArgs._PointCloud;
		PointCloud->OnPointsChanged.AddSP(this, &SGaussianSplattingPointCloudHistogram::RefreshData);
		RefreshData();
		SetPixelSnapping(EWidgetPixelSnapping::Disabled);
	}
	int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override {
		static const FSlateBrush* WhiteBrush = FAppStyle::GetBrush("WhiteBrush");
		const bool bEnabled = ShouldBeEnabled(bParentEnabled);
		const ESlateDrawEffect DrawEffects = bEnabled ? ESlateDrawEffect::NoPixelSnapping : ESlateDrawEffect::DisabledEffect;
		int ViewWidth = AllottedGeometry.GetLocalSize().X;
		int ViewHeight = AllottedGeometry.GetLocalSize().Y;
		float BarWidth = ViewWidth / (float) HistogramData.Num();
		for (int i = 0; i < HistogramData.Num(); i++) {
			int Count = HistogramData[i];
			float Factor = FMath::Clamp(Count / (float) MaxBarCount, 0.0f, 1.0f);
			float BarHeight = ViewHeight * Factor;
			FLinearColor Color = SelectBar.Contains(i) ? FLinearColor(0.368f, 0.262f, 0.560f) : FLinearColor(0.1f, 0.5f, 0.9f);
			FSlateDrawElement::MakeBox(OutDrawElements, LayerId, MAKE_PAINT_GEOMETRY_RC(AllottedGeometry, i * BarWidth, ViewHeight - BarHeight, BarWidth - 1, BarHeight), WhiteBrush, DrawEffects, Color);
		}
		if (!MouseDownPosition.IsZero()) {
			float StartPosX = MouseDownPosition.X;
			float EndPosX = MouseMovePosition.X;
			if (StartPosX > EndPosX) {
				Swap(StartPosX, EndPosX);
			}
			FSlateDrawElement::MakeBox(OutDrawElements, LayerId, MAKE_PAINT_GEOMETRY_RC(AllottedGeometry, StartPosX, 0, EndPosX - StartPosX, ViewHeight), WhiteBrush, DrawEffects, FLinearColor(0.368f, 0.262f, 0.560f, 0.5f));
		}
		return LayerId; 
	}

	FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override {
		if (MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton)) {
			MouseDownPosition = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());	
			MouseMovePosition = MouseDownPosition;
			return FReply::Handled().CaptureMouse(SharedThis(this));									
		}
		return FReply::Handled();
	}
	FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override {
		if (MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton)) {
			MouseMovePosition = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
		}
		return FReply::Handled();
	}
	FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override {
		if (!MouseEvent.IsAltDown()) {
			SelectBar.Reset();
		}
		int ViewWidth = MyGeometry.GetLocalSize().X;
		float StartPosX = MouseDownPosition.X;
		float EndPosX = MouseMovePosition.X;
		if (StartPosX > EndPosX) {
			Swap(StartPosX, EndPosX);
		}
		float BarWidth = ViewWidth / (float)HistogramData.Num();
		for (int i = 0; i < HistogramData.Num(); i++) {
			float BarLeft = i * BarWidth;
			float BarRight = BarLeft + BarWidth;
			if ((BarLeft >= StartPosX && BarLeft < EndPosX) ||(BarRight >= StartPosX && BarRight < EndPosX)) {
				SelectBar.Add(i);
			}
		}
		FString Str;
		for (auto Item : GetSelectIndices()) {
			Str += FString::Printf(TEXT(", %d"), (int)Item);
		}
		OnSelectChanged.ExecuteIfBound();
		MouseDownPosition = FVector2D::ZeroVector;
		MouseMovePosition = FVector2D::ZeroVector;
		return FReply::Handled().ReleaseMouseCapture();                                        
	}
	void RefreshData() {
		auto Points = PointCloud->GetPoints();
		if (!Points.IsEmpty()) {
			float MaxSize = Points[0].Scale.Length();
			float MinSize = Points.Last().Scale.Length();
			HistogramData.Reset();
			HistogramData.AddZeroed(FMath::Min(NumOfBar, Points.Num()));
			MaxBarCount = 0;
			for (int i = 0; i < Points.Num(); i++) {
				float Size = Points[i].Scale.Length();
				int Index = ((Size - MinSize) / ( MaxSize - MinSize)) * (HistogramData.Num() - 1);
				Index = FMath::Clamp(Index, 0, HistogramData.Num() - 1);    
				HistogramData[Index]++;
				MaxBarCount = FMath::Max(MaxBarCount, HistogramData[Index]);
			}
		}
		SelectBar.Reset();
	}

	TArray<uint32> GetSelectIndices() {
		TArray<uint32> Indices;
		if (SelectBar.IsEmpty())
			return Indices;
		int NumPoint = PointCloud->GetPoints().Num();
		int StartIndex = 0;
		for (int i = HistogramData.Num() - 1; i >= 0 ; i--) {
			int BarCount = HistogramData[i];
			if (SelectBar.Contains(i)) {
				for (int j = 0; j < BarCount; j++) {
					Indices.Add(StartIndex + j);
				}
			}
			StartIndex += BarCount;
		}
		Indices.Sort();
		return Indices;
	}
public:
	TObjectPtr<UGaussianSplattingPointCloud> PointCloud;
	const int NumOfBar = 128;
	TArray<int> HistogramData;
	TSet<uint32> SelectBar;
	int MaxBarCount = 0;
	FVector2D MouseDownPosition = FVector2D::ZeroVector;
	FVector2D MouseMovePosition = FVector2D::ZeroVector;
	FSimpleDelegate OnSelectChanged;
};

void SGaussianSplattingPointCloudFeatureEditor::Construct(const FArguments& InArgs)
{
	Editor = InArgs._Editor;

	ChildSlot
		[
			SNew(SBox)
				.HeightOverride(100)
				[
					SAssignNew(Histogram, SGaussianSplattingPointCloudHistogram)
						.PointCloud(Editor.Pin()->PointCloud)
				]
		];

	Histogram->OnSelectChanged.BindSPLambda(this, [this]() {
		Editor.Pin()->SelectPointsByIndex(Histogram->GetSelectIndices());
	});
}

void SGaussianSplattingPointCloudFeatureEditor::ClearSelection()
{
	Histogram->SelectBar.Reset();
}

FReply SGaussianSplattingPointCloudFeatureEditor::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Delete)
	{
		if (TSharedPtr<FGaussianSplattingPointCloudEditor> EditorPtr = Editor.Pin())
		{
			EditorPtr->RemoveSelectedPoints();
		}
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

