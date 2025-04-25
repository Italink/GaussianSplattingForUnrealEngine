#pragma once

#include "Modules/ModuleManager.h"
#include "GaussianSplattingPointCloudAssetFactory.h"

class UGaussianSplattingPointCloud;

class FGaussianSplattingEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
	void RegisterMenus();
	void CreateStaticMesh(UGaussianSplattingPointCloud* PointCloud);
	void CreateNiagara(UGaussianSplattingPointCloud* PointCloud);
};
