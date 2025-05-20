#include "GaussianSplattingEditorSettings.h"
#include "Interfaces/IPluginManager.h"

FString UGaussianSplattingEditorSettings::GetWorkHome() const
{
	const FString PluginDir = IPluginManager::Get().FindPlugin(TEXT("GaussianSplattingForUnrealEngine"))->GetBaseDir();
	return FPaths::ConvertRelativePathToFull(PluginDir) / "Work";
}

FString UGaussianSplattingEditorSettings::GetWorkDir(FString WorkName) const
{
	FString WorkHome = GetWorkHome();
	return WorkHome / WorkName;;
}

FString UGaussianSplattingEditorSettings::GetGaussianSplattingHelperPath() const
{
	const FString PluginDir = IPluginManager::Get().FindPlugin(TEXT("GaussianSplattingForUnrealEngine"))->GetBaseDir();
	return PluginDir / "Scripts" / "gaussian_splatting_helper.py";
}

FString UGaussianSplattingEditorSettings::GetPythonExecutablePath() const
{
	return PythonExecutablePath.FilePath;
}

FString UGaussianSplattingEditorSettings::GetColmapExecutablePath() const
{
	return ColmapExecutablePath.FilePath;
}

FString UGaussianSplattingEditorSettings::GetGaussianSplattingRepoDir() const
{
	return GaussianSplattingRepoDir.Path;
}

void UGaussianSplattingEditorSettings::PostInitProperties()
{
	Super::PostInitProperties();
	PythonExecutablePath.FilePath = PythonExecutablePathConifg;
	ColmapExecutablePath.FilePath = ColmapExecutablePathConfig;
	GaussianSplattingRepoDir.Path = GaussianSplattingRepoDirConfig;

	if (PythonExecutablePath.FilePath.IsEmpty() || ColmapExecutablePath.FilePath.IsEmpty()) {
		FString SystemPath = FPlatformMisc::GetEnvironmentVariable(TEXT("Path"));
		TArray<FString> PathParts;
		SystemPath.ParseIntoArray(PathParts, TEXT(";"), true);
		for (const FString& PathPart : PathParts){
			FString PythonPath = FPaths::Combine(PathPart, TEXT("python.exe"));
			if (FPaths::FileExists(PythonPath)){
				PythonExecutablePath.FilePath = PythonPath.Replace(TEXT("\\"), TEXT("/"));
				break;
			}
		}
		for (const FString& PathPart : PathParts){
			FString ColmapPath = FPaths::Combine(PathPart, TEXT("colmap.exe"));
			if (FPaths::FileExists(ColmapPath)){
				ColmapExecutablePath.FilePath = ColmapPath.Replace(TEXT("\\"), TEXT("/"));
				break;
			}
		}
	}
}

void UGaussianSplattingEditorSettings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	const FName PropertyName = PropertyChangedEvent.GetMemberPropertyName();

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UGaussianSplattingEditorSettings, PythonExecutablePath)
		|| PropertyName == GET_MEMBER_NAME_CHECKED(UGaussianSplattingEditorSettings, ColmapExecutablePath)
		|| PropertyName == GET_MEMBER_NAME_CHECKED(UGaussianSplattingEditorSettings, GaussianSplattingRepoDir)
		) {
		Modify();
		PythonExecutablePathConifg = PythonExecutablePath.FilePath;
		ColmapExecutablePathConfig = ColmapExecutablePath.FilePath;
		GaussianSplattingRepoDirConfig = GaussianSplattingRepoDir.Path;
		TryUpdateDefaultConfigFile();
	}
}
