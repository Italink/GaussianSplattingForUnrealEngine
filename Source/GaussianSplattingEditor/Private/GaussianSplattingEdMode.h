#pragma once
#include "EditorModes.h"
#include "EdMode.h"
#include "Editor.h"
#include "EditorModeManager.h"
#include "SGaussianSplattingEdModePanel.h"

class FGaussianSplattingEdMode : public FEdMode
{
public:
    const static FEditorModeID EdID;
    void Enter() override;
    void Exit() override;
};

class FGaussianSplattingEdModeToolkit : public FModeToolkit
{
public:
    FGaussianSplattingEdModeToolkit();
    ~FGaussianSplattingEdModeToolkit();
    /** IToolkit interface */
    virtual FName GetToolkitFName() const override;
    virtual FText GetBaseToolkitName() const override;
    virtual class FEdMode* GetEditorMode() const override;
    virtual TSharedPtr<class SWidget> GetInlineContent() const override;
private:
    TSharedPtr<SGaussianSplattingEdModePanel> GaussianSplattingEditor;
    TSharedPtr<IDetailsView> DetailsView;
};