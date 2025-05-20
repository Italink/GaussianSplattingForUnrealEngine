#pragma once

#include "GaussianSplattingEditorSettings.generated.h"

UCLASS(EditInlineNew, CollapseCategories, config = GaussianSplattingEditor, defaultconfig)
class UGaussianSplattingEditorSettings : public UObject {
	GENERATED_BODY()
public:
	FString GetWorkHome() const;

	FString GetWorkDir(FString WorkName) const;

	FString GetGaussianSplattingHelperPath() const;

	FString GetPythonExecutablePath() const;

	FString GetColmapExecutablePath() const;

	FString GetGaussianSplattingRepoDir() const;

	void PostInitProperties() override;

	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
public:
	UPROPERTY(EditAnywhere, meta = (FilePathFilter = "exe", RelativeToGameDir), Category = "Gaussian Splatting")
	FFilePath PythonExecutablePath;

	UPROPERTY(EditAnywhere, meta = (FilePathFilter = "exe", RelativeToGameDir), Category = "Gaussian Splatting")
	FFilePath ColmapExecutablePath;

	UPROPERTY(EditAnywhere, meta = (RelativeToGameDir), Category = "Gaussian Splatting")
	FDirectoryPath GaussianSplattingRepoDir;

	UPROPERTY(Config)
	FString PythonExecutablePathConifg;

	UPROPERTY(Config)
	FString ColmapExecutablePathConfig;

	UPROPERTY(Config)
	FString GaussianSplattingRepoDirConfig;
}; 
