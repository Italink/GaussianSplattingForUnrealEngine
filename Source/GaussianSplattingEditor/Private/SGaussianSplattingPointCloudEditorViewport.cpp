#include "SGaussianSplattingPointCloudEditorViewport.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Editor/UnrealEdEngine.h"
#include "UnrealEdGlobals.h"
#include "EditorViewportCommands.h"
#include "EditorViewportTabContent.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "AdvancedPreviewScene.h"
#include "Particles/ParticlePerfStatsManager.h"
#include "NiagaraSystemInstanceController.h"
#include "SGaussianSplattingPointCloudEditorViewportClient.h"

#define LOCTEXT_NAMESPACE "GaussianSplatting"

void SGaussianSplattingPointCloudEditorViewport::Construct(const FArguments& InArgs)
{
	Editor = InArgs._Editor;

	PreviewScene = MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues()));
	PreviewScene->SetFloorVisibility(false);
	PreviewScene->SetEnvironmentVisibility(true);

	PreviewComponent = NewObject<UNiagaraComponent>(GetTransientPackage(), NAME_None, RF_Transient);
	PreviewComponent->CastShadow = 0;
	PreviewComponent->bCastDynamicShadow = 0;
	PreviewComponent->SetAllowScalability(false);
	PreviewComponent->SetForceSolo(true);
	PreviewComponent->SetAgeUpdateMode(ENiagaraAgeUpdateMode::TickDeltaTime);
	PreviewComponent->SetCanRenderWhileSeeking(false);
	PreviewComponent->SetRelativeLocation(FVector::ZeroVector);

	PreviewScene->AddComponent(PreviewComponent, PreviewComponent->GetRelativeTransform());

	SEditorViewport::FArguments ViewportArgs;
	SEditorViewport::Construct(ViewportArgs);
}

TSharedRef<FEditorViewportClient> SGaussianSplattingPointCloudEditorViewport::MakeEditorViewportClient()
{
	TSharedPtr<FGaussianSplattingPointCloudEditorViewportClient> ViewportClient = MakeShareable(new FGaussianSplattingPointCloudEditorViewportClient(nullptr, PreviewScene.Get(), SharedThis(this)));
	ViewportClient->SetEditor(Editor);
	Client = ViewportClient;
	Client->SetViewportType(LVT_Perspective);
	Client->SetRealtime(true);
	Client->SetViewLocation(EditorViewportDefs::DefaultPerspectiveViewLocation);
	Client->SetViewRotation(EditorViewportDefs::DefaultPerspectiveViewRotation);
	Client->bSetListenerPosition = false;
	return Client.ToSharedRef();
}

#undef LOCTEXT_NAMESPACE
