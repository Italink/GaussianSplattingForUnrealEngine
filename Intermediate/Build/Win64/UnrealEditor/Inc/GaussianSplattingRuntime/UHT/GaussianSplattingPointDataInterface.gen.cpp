// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GaussianSplattingRuntime/Public/GaussianSplattingPointDataInterface.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGaussianSplattingPointDataInterface() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FQuat4f();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector3f();
GAUSSIANSPLATTINGRUNTIME_API UClass* Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints();
GAUSSIANSPLATTINGRUNTIME_API UClass* Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints_NoRegister();
GAUSSIANSPLATTINGRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FGaussianSplattingPoint();
NIAGARA_API UClass* Z_Construct_UClass_UNiagaraDataInterface();
UPackage* Z_Construct_UPackage__Script_GaussianSplattingRuntime();
// End Cross Module References

// Begin ScriptStruct FGaussianSplattingPoint
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_GaussianSplattingPoint;
class UScriptStruct* FGaussianSplattingPoint::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_GaussianSplattingPoint.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_GaussianSplattingPoint.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FGaussianSplattingPoint, (UObject*)Z_Construct_UPackage__Script_GaussianSplattingRuntime(), TEXT("GaussianSplattingPoint"));
	}
	return Z_Registration_Info_UScriptStruct_GaussianSplattingPoint.OuterSingleton;
}
template<> GAUSSIANSPLATTINGRUNTIME_API UScriptStruct* StaticStruct<FGaussianSplattingPoint>()
{
	return FGaussianSplattingPoint::StaticStruct();
}
struct Z_Construct_UScriptStruct_FGaussianSplattingPoint_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "DisplayName", "Gaussian Splatting Point" },
		{ "ModuleRelativePath", "Public/GaussianSplattingPointDataInterface.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[] = {
		{ "Category", "GaussianSplattingPoint" },
		{ "ModuleRelativePath", "Public/GaussianSplattingPointDataInterface.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Quat_MetaData[] = {
		{ "Category", "GaussianSplattingPoint" },
		{ "ModuleRelativePath", "Public/GaussianSplattingPointDataInterface.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Scale_MetaData[] = {
		{ "Category", "GaussianSplattingPoint" },
		{ "ModuleRelativePath", "Public/GaussianSplattingPointDataInterface.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Color_MetaData[] = {
		{ "Category", "GaussianSplattingPoint" },
		{ "ModuleRelativePath", "Public/GaussianSplattingPointDataInterface.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Quat;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Scale;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Color;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FGaussianSplattingPoint>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGaussianSplattingPoint_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianSplattingPoint, Position), Z_Construct_UScriptStruct_FVector3f, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGaussianSplattingPoint_Statics::NewProp_Quat = { "Quat", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianSplattingPoint, Quat), Z_Construct_UScriptStruct_FQuat4f, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Quat_MetaData), NewProp_Quat_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGaussianSplattingPoint_Statics::NewProp_Scale = { "Scale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianSplattingPoint, Scale), Z_Construct_UScriptStruct_FVector3f, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Scale_MetaData), NewProp_Scale_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGaussianSplattingPoint_Statics::NewProp_Color = { "Color", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGaussianSplattingPoint, Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Color_MetaData), NewProp_Color_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FGaussianSplattingPoint_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGaussianSplattingPoint_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGaussianSplattingPoint_Statics::NewProp_Quat,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGaussianSplattingPoint_Statics::NewProp_Scale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGaussianSplattingPoint_Statics::NewProp_Color,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGaussianSplattingPoint_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FGaussianSplattingPoint_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_GaussianSplattingRuntime,
	nullptr,
	&NewStructOps,
	"GaussianSplattingPoint",
	Z_Construct_UScriptStruct_FGaussianSplattingPoint_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGaussianSplattingPoint_Statics::PropPointers),
	sizeof(FGaussianSplattingPoint),
	alignof(FGaussianSplattingPoint),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGaussianSplattingPoint_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FGaussianSplattingPoint_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FGaussianSplattingPoint()
{
	if (!Z_Registration_Info_UScriptStruct_GaussianSplattingPoint.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_GaussianSplattingPoint.InnerSingleton, Z_Construct_UScriptStruct_FGaussianSplattingPoint_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_GaussianSplattingPoint.InnerSingleton;
}
// End ScriptStruct FGaussianSplattingPoint

// Begin Class UNiagaraDataInterfaceGaussianSplattingPoints
void UNiagaraDataInterfaceGaussianSplattingPoints::StaticRegisterNativesUNiagaraDataInterfaceGaussianSplattingPoints()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UNiagaraDataInterfaceGaussianSplattingPoints);
UClass* Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints_NoRegister()
{
	return UNiagaraDataInterfaceGaussianSplattingPoints::StaticClass();
}
struct Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Category", "Array" },
		{ "DisplayName", "Gaussian Splatting Points" },
		{ "Experimental", "" },
		{ "IncludePath", "GaussianSplattingPointDataInterface.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/GaussianSplattingPointDataInterface.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PointData_MetaData[] = {
		{ "Category", "NiagaraDataInterfaceGaussianSplattingPoints" },
		{ "ModuleRelativePath", "Public/GaussianSplattingPointDataInterface.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_PointData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_PointData;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNiagaraDataInterfaceGaussianSplattingPoints>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints_Statics::NewProp_PointData_Inner = { "PointData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FGaussianSplattingPoint, METADATA_PARAMS(0, nullptr) }; // 535220827
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints_Statics::NewProp_PointData = { "PointData", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNiagaraDataInterfaceGaussianSplattingPoints, PointData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PointData_MetaData), NewProp_PointData_MetaData) }; // 535220827
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints_Statics::NewProp_PointData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints_Statics::NewProp_PointData,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UNiagaraDataInterface,
	(UObject* (*)())Z_Construct_UPackage__Script_GaussianSplattingRuntime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints_Statics::ClassParams = {
	&UNiagaraDataInterfaceGaussianSplattingPoints::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints_Statics::PropPointers),
	0,
	0x001010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints_Statics::Class_MetaDataParams), Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints()
{
	if (!Z_Registration_Info_UClass_UNiagaraDataInterfaceGaussianSplattingPoints.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNiagaraDataInterfaceGaussianSplattingPoints.OuterSingleton, Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNiagaraDataInterfaceGaussianSplattingPoints.OuterSingleton;
}
template<> GAUSSIANSPLATTINGRUNTIME_API UClass* StaticClass<UNiagaraDataInterfaceGaussianSplattingPoints>()
{
	return UNiagaraDataInterfaceGaussianSplattingPoints::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UNiagaraDataInterfaceGaussianSplattingPoints);
UNiagaraDataInterfaceGaussianSplattingPoints::~UNiagaraDataInterfaceGaussianSplattingPoints() {}
// End Class UNiagaraDataInterfaceGaussianSplattingPoints

// Begin Registration
struct Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Source_GaussianSplattingRuntime_Public_GaussianSplattingPointDataInterface_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FGaussianSplattingPoint::StaticStruct, Z_Construct_UScriptStruct_FGaussianSplattingPoint_Statics::NewStructOps, TEXT("GaussianSplattingPoint"), &Z_Registration_Info_UScriptStruct_GaussianSplattingPoint, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FGaussianSplattingPoint), 535220827U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNiagaraDataInterfaceGaussianSplattingPoints, UNiagaraDataInterfaceGaussianSplattingPoints::StaticClass, TEXT("UNiagaraDataInterfaceGaussianSplattingPoints"), &Z_Registration_Info_UClass_UNiagaraDataInterfaceGaussianSplattingPoints, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNiagaraDataInterfaceGaussianSplattingPoints), 722354704U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Source_GaussianSplattingRuntime_Public_GaussianSplattingPointDataInterface_h_373915176(TEXT("/Script/GaussianSplattingRuntime"),
	Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Source_GaussianSplattingRuntime_Public_GaussianSplattingPointDataInterface_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Source_GaussianSplattingRuntime_Public_GaussianSplattingPointDataInterface_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Source_GaussianSplattingRuntime_Public_GaussianSplattingPointDataInterface_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Source_GaussianSplattingRuntime_Public_GaussianSplattingPointDataInterface_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
