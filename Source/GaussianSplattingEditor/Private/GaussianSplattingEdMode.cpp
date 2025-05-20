#include "GaussianSplattingEdMode.h"
#include "EditorModeManager.h"
#include "ScopedTransaction.h"
#include "Toolkits/ToolkitManager.h"

const FEditorModeID FGaussianSplattingEdMode::EdID(TEXT("EM_GaussianSplatting"));

void FGaussianSplattingEdMode::Enter()
{
    FEdMode::Enter();
    if (!Toolkit.IsValid()){
        Toolkit = MakeShareable(new FGaussianSplattingEdModeToolkit);
        Toolkit->Init(Owner->GetToolkitHost());
    }
}

void FGaussianSplattingEdMode::Exit()
{
    FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
    Toolkit.Reset();
    FEdMode::Exit();
}

FGaussianSplattingEdModeToolkit::FGaussianSplattingEdModeToolkit()
{
	GaussianSplattingEditor = SNew(SGaussianSplattingEdModePanel);
}

FGaussianSplattingEdModeToolkit::~FGaussianSplattingEdModeToolkit()
{
}

FName FGaussianSplattingEdModeToolkit::GetToolkitFName() const
{
	return FName("GaussianSplattingEdMode");
}

FText FGaussianSplattingEdModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("GaussianSplatting", "GaussianSplatting", "Gaussian Splatting");
}

class FEdMode* FGaussianSplattingEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FGaussianSplattingEdMode::EdID);
}

TSharedPtr<class SWidget> FGaussianSplattingEdModeToolkit::GetInlineContent() const
{
	return GaussianSplattingEditor;
}
