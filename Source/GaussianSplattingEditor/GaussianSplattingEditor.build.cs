using UnrealBuildTool;
using System.IO;
public class GaussianSplattingEditor : ModuleRules
{
	public GaussianSplattingEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		AddEngineThirdPartyPrivateStaticDependencies(Target, "zlib");

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"UnrealEd", 
				"AssetTools",
				"Kismet",
				"Core",
				"RenderCore",
				"RHI",
				"AssetRegistry",
                "EditorFramework",
                "ImageCore",
                "Niagara",
                "GaussianSplattingRuntime",
            }
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore", 
				"Niagara",
                "MeshDescription",
                "StaticMeshDescription",
                "PropertyEditor",
                "UnrealEd",
                "AssetRegistry",
                "EditorStyle",
                "InputCore",
                "ContentBrowser",
                "ContentBrowserData",
                "ToolMenus",
                "Projects",
                "NiagaraEditor",
                "LevelEditor",
				"Json",
                "AssetTools",
				"Landscape",
                "AdvancedPreviewScene",
                "AssetDefinition",
                "JsonUtilities",
            }
		);
	}
}