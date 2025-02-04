// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GaussianSplattingEditor/Private/GaussianSplattingSettings.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGaussianSplattingSettings() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FDirectoryPath();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FFilePath();
GAUSSIANSPLATTINGEDITOR_API UClass* Z_Construct_UClass_UGaussianSplattingSettings();
GAUSSIANSPLATTINGEDITOR_API UClass* Z_Construct_UClass_UGaussianSplattingSettings_NoRegister();
UPackage* Z_Construct_UPackage__Script_GaussianSplattingEditor();
// End Cross Module References

// Begin Class UGaussianSplattingSettings
void UGaussianSplattingSettings::StaticRegisterNativesUGaussianSplattingSettings()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGaussianSplattingSettings);
UClass* Z_Construct_UClass_UGaussianSplattingSettings_NoRegister()
{
	return UGaussianSplattingSettings::StaticClass();
}
struct Z_Construct_UClass_UGaussianSplattingSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "GaussianSplattingSettings.h" },
		{ "ModuleRelativePath", "Private/GaussianSplattingSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PythonExecutablePath_MetaData[] = {
		{ "Category", "GaussianSplattingSettings" },
		{ "FilePathFilter", "exe" },
		{ "ModuleRelativePath", "Private/GaussianSplattingSettings.h" },
		{ "RelativeToGameDir", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ColmapExecutablePath_MetaData[] = {
		{ "Category", "GaussianSplattingSettings" },
		{ "FilePathFilter", "exe" },
		{ "ModuleRelativePath", "Private/GaussianSplattingSettings.h" },
		{ "RelativeToGameDir", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GaussianSplattingRepoDir_MetaData[] = {
		{ "Category", "GaussianSplattingSettings" },
		{ "ModuleRelativePath", "Private/GaussianSplattingSettings.h" },
		{ "RelativeToGameDir", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PythonExecutablePathConifg_MetaData[] = {
		{ "ModuleRelativePath", "Private/GaussianSplattingSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ColmapExecutablePathConfig_MetaData[] = {
		{ "ModuleRelativePath", "Private/GaussianSplattingSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GaussianSplattingRepoDirConfig_MetaData[] = {
		{ "ModuleRelativePath", "Private/GaussianSplattingSettings.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_PythonExecutablePath;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ColmapExecutablePath;
	static const UECodeGen_Private::FStructPropertyParams NewProp_GaussianSplattingRepoDir;
	static const UECodeGen_Private::FStrPropertyParams NewProp_PythonExecutablePathConifg;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ColmapExecutablePathConfig;
	static const UECodeGen_Private::FStrPropertyParams NewProp_GaussianSplattingRepoDirConfig;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGaussianSplattingSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UGaussianSplattingSettings_Statics::NewProp_PythonExecutablePath = { "PythonExecutablePath", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingSettings, PythonExecutablePath), Z_Construct_UScriptStruct_FFilePath, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PythonExecutablePath_MetaData), NewProp_PythonExecutablePath_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UGaussianSplattingSettings_Statics::NewProp_ColmapExecutablePath = { "ColmapExecutablePath", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingSettings, ColmapExecutablePath), Z_Construct_UScriptStruct_FFilePath, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ColmapExecutablePath_MetaData), NewProp_ColmapExecutablePath_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UGaussianSplattingSettings_Statics::NewProp_GaussianSplattingRepoDir = { "GaussianSplattingRepoDir", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingSettings, GaussianSplattingRepoDir), Z_Construct_UScriptStruct_FDirectoryPath, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GaussianSplattingRepoDir_MetaData), NewProp_GaussianSplattingRepoDir_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGaussianSplattingSettings_Statics::NewProp_PythonExecutablePathConifg = { "PythonExecutablePathConifg", nullptr, (EPropertyFlags)0x0010000000004000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingSettings, PythonExecutablePathConifg), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PythonExecutablePathConifg_MetaData), NewProp_PythonExecutablePathConifg_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGaussianSplattingSettings_Statics::NewProp_ColmapExecutablePathConfig = { "ColmapExecutablePathConfig", nullptr, (EPropertyFlags)0x0010000000004000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingSettings, ColmapExecutablePathConfig), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ColmapExecutablePathConfig_MetaData), NewProp_ColmapExecutablePathConfig_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGaussianSplattingSettings_Statics::NewProp_GaussianSplattingRepoDirConfig = { "GaussianSplattingRepoDirConfig", nullptr, (EPropertyFlags)0x0010000000004000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingSettings, GaussianSplattingRepoDirConfig), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GaussianSplattingRepoDirConfig_MetaData), NewProp_GaussianSplattingRepoDirConfig_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGaussianSplattingSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingSettings_Statics::NewProp_PythonExecutablePath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingSettings_Statics::NewProp_ColmapExecutablePath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingSettings_Statics::NewProp_GaussianSplattingRepoDir,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingSettings_Statics::NewProp_PythonExecutablePathConifg,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingSettings_Statics::NewProp_ColmapExecutablePathConfig,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingSettings_Statics::NewProp_GaussianSplattingRepoDirConfig,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingSettings_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UGaussianSplattingSettings_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_GaussianSplattingEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingSettings_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGaussianSplattingSettings_Statics::ClassParams = {
	&UGaussianSplattingSettings::StaticClass,
	"GaussianSplattingEditor",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UGaussianSplattingSettings_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingSettings_Statics::PropPointers),
	0,
	0x000030A6u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UGaussianSplattingSettings_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGaussianSplattingSettings()
{
	if (!Z_Registration_Info_UClass_UGaussianSplattingSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGaussianSplattingSettings.OuterSingleton, Z_Construct_UClass_UGaussianSplattingSettings_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGaussianSplattingSettings.OuterSingleton;
}
template<> GAUSSIANSPLATTINGEDITOR_API UClass* StaticClass<UGaussianSplattingSettings>()
{
	return UGaussianSplattingSettings::StaticClass();
}
UGaussianSplattingSettings::UGaussianSplattingSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGaussianSplattingSettings);
UGaussianSplattingSettings::~UGaussianSplattingSettings() {}
// End Class UGaussianSplattingSettings

// Begin Registration
struct Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Private_Source_GaussianSplattingEditor_Private_GaussianSplattingSettings_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGaussianSplattingSettings, UGaussianSplattingSettings::StaticClass, TEXT("UGaussianSplattingSettings"), &Z_Registration_Info_UClass_UGaussianSplattingSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGaussianSplattingSettings), 1385848650U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Private_Source_GaussianSplattingEditor_Private_GaussianSplattingSettings_h_2425615092(TEXT("/Script/GaussianSplattingEditor"),
	Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Private_Source_GaussianSplattingEditor_Private_GaussianSplattingSettings_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Private_Source_GaussianSplattingEditor_Private_GaussianSplattingSettings_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
