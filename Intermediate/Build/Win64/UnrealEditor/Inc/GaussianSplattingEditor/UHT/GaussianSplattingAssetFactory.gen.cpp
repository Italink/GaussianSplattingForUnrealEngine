// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GaussianSplattingEditor/Public/GaussianSplattingAssetFactory.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGaussianSplattingAssetFactory() {}

// Begin Cross Module References
GAUSSIANSPLATTINGEDITOR_API UClass* Z_Construct_UClass_UGaussianSplattingAssetFactory();
GAUSSIANSPLATTINGEDITOR_API UClass* Z_Construct_UClass_UGaussianSplattingAssetFactory_NoRegister();
UNREALED_API UClass* Z_Construct_UClass_UFactory();
UPackage* Z_Construct_UPackage__Script_GaussianSplattingEditor();
// End Cross Module References

// Begin Class UGaussianSplattingAssetFactory
void UGaussianSplattingAssetFactory::StaticRegisterNativesUGaussianSplattingAssetFactory()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGaussianSplattingAssetFactory);
UClass* Z_Construct_UClass_UGaussianSplattingAssetFactory_NoRegister()
{
	return UGaussianSplattingAssetFactory::StaticClass();
}
struct Z_Construct_UClass_UGaussianSplattingAssetFactory_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Object" },
		{ "IncludePath", "GaussianSplattingAssetFactory.h" },
		{ "ModuleRelativePath", "Public/GaussianSplattingAssetFactory.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGaussianSplattingAssetFactory>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UGaussianSplattingAssetFactory_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UFactory,
	(UObject* (*)())Z_Construct_UPackage__Script_GaussianSplattingEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingAssetFactory_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGaussianSplattingAssetFactory_Statics::ClassParams = {
	&UGaussianSplattingAssetFactory::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingAssetFactory_Statics::Class_MetaDataParams), Z_Construct_UClass_UGaussianSplattingAssetFactory_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGaussianSplattingAssetFactory()
{
	if (!Z_Registration_Info_UClass_UGaussianSplattingAssetFactory.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGaussianSplattingAssetFactory.OuterSingleton, Z_Construct_UClass_UGaussianSplattingAssetFactory_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGaussianSplattingAssetFactory.OuterSingleton;
}
template<> GAUSSIANSPLATTINGEDITOR_API UClass* StaticClass<UGaussianSplattingAssetFactory>()
{
	return UGaussianSplattingAssetFactory::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGaussianSplattingAssetFactory);
UGaussianSplattingAssetFactory::~UGaussianSplattingAssetFactory() {}
// End Class UGaussianSplattingAssetFactory

// Begin Registration
struct Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Private_Source_GaussianSplattingEditor_Public_GaussianSplattingAssetFactory_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGaussianSplattingAssetFactory, UGaussianSplattingAssetFactory::StaticClass, TEXT("UGaussianSplattingAssetFactory"), &Z_Registration_Info_UClass_UGaussianSplattingAssetFactory, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGaussianSplattingAssetFactory), 3863334898U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Private_Source_GaussianSplattingEditor_Public_GaussianSplattingAssetFactory_h_3967649682(TEXT("/Script/GaussianSplattingEditor"),
	Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Private_Source_GaussianSplattingEditor_Public_GaussianSplattingAssetFactory_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Private_Source_GaussianSplattingEditor_Public_GaussianSplattingAssetFactory_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
