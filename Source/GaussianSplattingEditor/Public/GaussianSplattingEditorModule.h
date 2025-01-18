#pragma once

#include "Modules/ModuleManager.h"

class FGaussianSplattingEditorModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
