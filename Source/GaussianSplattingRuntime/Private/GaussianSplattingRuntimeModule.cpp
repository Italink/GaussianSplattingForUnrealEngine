#include "GaussianSplattingRuntimeModule.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "GaussianSplatting"

void FGaussianSplattingRuntimeModule::StartupModule()
{
}

void FGaussianSplattingRuntimeModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGaussianSplattingRuntimeModule, GaussianSplattingRuntime)