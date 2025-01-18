// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GaussianSplattingEditor/Private/HLODBuilderGaussianSplatting.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHLODBuilderGaussianSplatting() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UHLODBuilder();
ENGINE_API UClass* Z_Construct_UClass_UHLODBuilderSettings();
GAUSSIANSPLATTINGEDITOR_API UClass* Z_Construct_UClass_UGaussianSplattingStep_Capture_NoRegister();
GAUSSIANSPLATTINGEDITOR_API UClass* Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_NoRegister();
GAUSSIANSPLATTINGEDITOR_API UClass* Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_NoRegister();
GAUSSIANSPLATTINGEDITOR_API UClass* Z_Construct_UClass_UHLODBuilderGaussianSplatting();
GAUSSIANSPLATTINGEDITOR_API UClass* Z_Construct_UClass_UHLODBuilderGaussianSplatting_NoRegister();
GAUSSIANSPLATTINGEDITOR_API UClass* Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings();
GAUSSIANSPLATTINGEDITOR_API UClass* Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings_NoRegister();
UPackage* Z_Construct_UPackage__Script_GaussianSplattingEditor();
// End Cross Module References

// Begin Class UHLODBuilderGaussianSplattingSettings
void UHLODBuilderGaussianSplattingSettings::StaticRegisterNativesUHLODBuilderGaussianSplattingSettings()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UHLODBuilderGaussianSplattingSettings);
UClass* Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings_NoRegister()
{
	return UHLODBuilderGaussianSplattingSettings::StaticClass();
}
struct Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "HLODBuilderGaussianSplatting.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Private/HLODBuilderGaussianSplatting.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CaptureSettings_MetaData[] = {
		{ "Category", "HLODBuilderGaussianSplattingSettings" },
		{ "EditInline", "" },
		{ "ModuleRelativePath", "Private/HLODBuilderGaussianSplatting.h" },
		{ "NoResetToDefault", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SparseReconstructionSettings_MetaData[] = {
		{ "Category", "HLODBuilderGaussianSplattingSettings" },
		{ "EditInline", "" },
		{ "ModuleRelativePath", "Private/HLODBuilderGaussianSplatting.h" },
		{ "NoResetToDefault", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GaussianSplattingSettings_MetaData[] = {
		{ "Category", "HLODBuilderGaussianSplattingSettings" },
		{ "EditInline", "" },
		{ "ModuleRelativePath", "Private/HLODBuilderGaussianSplatting.h" },
		{ "NoResetToDefault", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CaptureSettings;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SparseReconstructionSettings;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_GaussianSplattingSettings;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHLODBuilderGaussianSplattingSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings_Statics::NewProp_CaptureSettings = { "CaptureSettings", nullptr, (EPropertyFlags)0x0114000002020009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHLODBuilderGaussianSplattingSettings, CaptureSettings), Z_Construct_UClass_UGaussianSplattingStep_Capture_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CaptureSettings_MetaData), NewProp_CaptureSettings_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings_Statics::NewProp_SparseReconstructionSettings = { "SparseReconstructionSettings", nullptr, (EPropertyFlags)0x0114000002020009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHLODBuilderGaussianSplattingSettings, SparseReconstructionSettings), Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SparseReconstructionSettings_MetaData), NewProp_SparseReconstructionSettings_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings_Statics::NewProp_GaussianSplattingSettings = { "GaussianSplattingSettings", nullptr, (EPropertyFlags)0x0114000002020009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHLODBuilderGaussianSplattingSettings, GaussianSplattingSettings), Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GaussianSplattingSettings_MetaData), NewProp_GaussianSplattingSettings_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings_Statics::NewProp_CaptureSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings_Statics::NewProp_SparseReconstructionSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings_Statics::NewProp_GaussianSplattingSettings,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UHLODBuilderSettings,
	(UObject* (*)())Z_Construct_UPackage__Script_GaussianSplattingEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings_Statics::ClassParams = {
	&UHLODBuilderGaussianSplattingSettings::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings_Statics::PropPointers),
	0,
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings()
{
	if (!Z_Registration_Info_UClass_UHLODBuilderGaussianSplattingSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UHLODBuilderGaussianSplattingSettings.OuterSingleton, Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UHLODBuilderGaussianSplattingSettings.OuterSingleton;
}
template<> GAUSSIANSPLATTINGEDITOR_API UClass* StaticClass<UHLODBuilderGaussianSplattingSettings>()
{
	return UHLODBuilderGaussianSplattingSettings::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UHLODBuilderGaussianSplattingSettings);
UHLODBuilderGaussianSplattingSettings::~UHLODBuilderGaussianSplattingSettings() {}
// End Class UHLODBuilderGaussianSplattingSettings

// Begin Class UHLODBuilderGaussianSplatting
void UHLODBuilderGaussianSplatting::StaticRegisterNativesUHLODBuilderGaussianSplatting()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UHLODBuilderGaussianSplatting);
UClass* Z_Construct_UClass_UHLODBuilderGaussianSplatting_NoRegister()
{
	return UHLODBuilderGaussianSplatting::StaticClass();
}
struct Z_Construct_UClass_UHLODBuilderGaussianSplatting_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "HLODBuilderGaussianSplatting.h" },
		{ "ModuleRelativePath", "Private/HLODBuilderGaussianSplatting.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHLODBuilderGaussianSplatting>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UHLODBuilderGaussianSplatting_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UHLODBuilder,
	(UObject* (*)())Z_Construct_UPackage__Script_GaussianSplattingEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHLODBuilderGaussianSplatting_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UHLODBuilderGaussianSplatting_Statics::ClassParams = {
	&UHLODBuilderGaussianSplatting::StaticClass,
	"Editor",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x000000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UHLODBuilderGaussianSplatting_Statics::Class_MetaDataParams), Z_Construct_UClass_UHLODBuilderGaussianSplatting_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UHLODBuilderGaussianSplatting()
{
	if (!Z_Registration_Info_UClass_UHLODBuilderGaussianSplatting.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UHLODBuilderGaussianSplatting.OuterSingleton, Z_Construct_UClass_UHLODBuilderGaussianSplatting_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UHLODBuilderGaussianSplatting.OuterSingleton;
}
template<> GAUSSIANSPLATTINGEDITOR_API UClass* StaticClass<UHLODBuilderGaussianSplatting>()
{
	return UHLODBuilderGaussianSplatting::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UHLODBuilderGaussianSplatting);
UHLODBuilderGaussianSplatting::~UHLODBuilderGaussianSplatting() {}
// End Class UHLODBuilderGaussianSplatting

// Begin Registration
struct Z_CompiledInDeferFile_FID_Publish_Proj55_Plugins_GaussianSplattingForUnrealEngine_Source_GaussianSplattingEditor_Private_HLODBuilderGaussianSplatting_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UHLODBuilderGaussianSplattingSettings, UHLODBuilderGaussianSplattingSettings::StaticClass, TEXT("UHLODBuilderGaussianSplattingSettings"), &Z_Registration_Info_UClass_UHLODBuilderGaussianSplattingSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UHLODBuilderGaussianSplattingSettings), 3797726338U) },
		{ Z_Construct_UClass_UHLODBuilderGaussianSplatting, UHLODBuilderGaussianSplatting::StaticClass, TEXT("UHLODBuilderGaussianSplatting"), &Z_Registration_Info_UClass_UHLODBuilderGaussianSplatting, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UHLODBuilderGaussianSplatting), 1458571483U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Publish_Proj55_Plugins_GaussianSplattingForUnrealEngine_Source_GaussianSplattingEditor_Private_HLODBuilderGaussianSplatting_h_1054155925(TEXT("/Script/GaussianSplattingEditor"),
	Z_CompiledInDeferFile_FID_Publish_Proj55_Plugins_GaussianSplattingForUnrealEngine_Source_GaussianSplattingEditor_Private_HLODBuilderGaussianSplatting_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Publish_Proj55_Plugins_GaussianSplattingForUnrealEngine_Source_GaussianSplattingEditor_Private_HLODBuilderGaussianSplatting_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
