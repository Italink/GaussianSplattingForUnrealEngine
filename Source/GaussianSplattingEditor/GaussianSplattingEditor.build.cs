using UnrealBuildTool;
using System.IO;
public class GaussianSplattingEditor : ModuleRules
{
	public GaussianSplattingEditor(ReadOnlyTargetRules Target) : base(Target){
		bUsePrecompiled = true;
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
                "Niagara"
            }
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore", 
				"GaussianSplattingRuntime", 
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
                "NiagaraEditor"
            }
		);
	}
}