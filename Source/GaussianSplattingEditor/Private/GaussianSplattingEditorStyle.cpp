#include "GaussianSplattingEditorStyle.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir
TSharedPtr<FSlateStyleSet> FGaussianSplattingEditorStyle::StyleInstance = nullptr;

void FGaussianSplattingEditorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();

		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FGaussianSplattingEditorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);

	ensure(StyleInstance.IsUnique());

	StyleInstance.Reset();
}

FName FGaussianSplattingEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("GaussianSplattingEditorStyle"));

	return StyleSetName;
}

TSharedRef<FSlateStyleSet> FGaussianSplattingEditorStyle::Create()
{
	const FVector2D IconSize(16, 16);
	TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet("GaussianSplattingEditorStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("GaussianSplattingForUnrealEngine")->GetBaseDir() / TEXT("Resources"));
	Style->Set("GaussianSplattingEditor.Capture", new IMAGE_BRUSH_SVG(TEXT("Capture"), IconSize));
	Style->Set("GaussianSplattingEditor.SparseReconstruction", new IMAGE_BRUSH_SVG(TEXT("SparseReconstruction"), IconSize));
	Style->Set("GaussianSplattingEditor.GaussianSplatting", new IMAGE_BRUSH_SVG(TEXT("GaussianSplatting"), IconSize));
	return Style;
}

void FGaussianSplattingEditorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FGaussianSplattingEditorStyle::Get()
{
	return *StyleInstance;
}
