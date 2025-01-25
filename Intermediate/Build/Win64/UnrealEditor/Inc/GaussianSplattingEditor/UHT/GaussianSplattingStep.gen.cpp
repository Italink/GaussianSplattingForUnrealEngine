// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GaussianSplattingEditor/Private/GaussianSplattingStep.h"
#include "Runtime/Engine/Classes/Components/SceneCaptureComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGaussianSplattingStep() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FBox();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_ASceneCapture2D_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_ATriggerSphere_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UTextureRenderTarget2D_NoRegister();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FEngineShowFlagsSetting();
GAUSSIANSPLATTINGEDITOR_API UClass* Z_Construct_UClass_UGaussianSplattingStep_Capture();
GAUSSIANSPLATTINGEDITOR_API UClass* Z_Construct_UClass_UGaussianSplattingStep_Capture_NoRegister();
GAUSSIANSPLATTINGEDITOR_API UClass* Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting();
GAUSSIANSPLATTINGEDITOR_API UClass* Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_NoRegister();
GAUSSIANSPLATTINGEDITOR_API UClass* Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction();
GAUSSIANSPLATTINGEDITOR_API UClass* Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_NoRegister();
GAUSSIANSPLATTINGEDITOR_API UClass* Z_Construct_UClass_UGaussianSplattingStepBase();
GAUSSIANSPLATTINGEDITOR_API UClass* Z_Construct_UClass_UGaussianSplattingStepBase_NoRegister();
GAUSSIANSPLATTINGEDITOR_API UEnum* Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingCameraMode();
GAUSSIANSPLATTINGEDITOR_API UEnum* Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingOutputType();
GAUSSIANSPLATTINGEDITOR_API UEnum* Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingSourceMode();
GAUSSIANSPLATTINGEDITOR_API UEnum* Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingStepStatus();
UPackage* Z_Construct_UPackage__Script_GaussianSplattingEditor();
// End Cross Module References

// Begin Enum EGaussianSplattingSourceMode
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EGaussianSplattingSourceMode;
static UEnum* EGaussianSplattingSourceMode_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EGaussianSplattingSourceMode.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EGaussianSplattingSourceMode.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingSourceMode, (UObject*)Z_Construct_UPackage__Script_GaussianSplattingEditor(), TEXT("EGaussianSplattingSourceMode"));
	}
	return Z_Registration_Info_UEnum_EGaussianSplattingSourceMode.OuterSingleton;
}
template<> GAUSSIANSPLATTINGEDITOR_API UEnum* StaticEnum<EGaussianSplattingSourceMode>()
{
	return EGaussianSplattingSourceMode_StaticEnum();
}
struct Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingSourceMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Custom.Name", "EGaussianSplattingSourceMode::Custom" },
		{ "Locate.Name", "EGaussianSplattingSourceMode::Locate" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
		{ "Select.Name", "EGaussianSplattingSourceMode::Select" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EGaussianSplattingSourceMode::Select", (int64)EGaussianSplattingSourceMode::Select },
		{ "EGaussianSplattingSourceMode::Locate", (int64)EGaussianSplattingSourceMode::Locate },
		{ "EGaussianSplattingSourceMode::Custom", (int64)EGaussianSplattingSourceMode::Custom },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingSourceMode_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_GaussianSplattingEditor,
	nullptr,
	"EGaussianSplattingSourceMode",
	"EGaussianSplattingSourceMode",
	Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingSourceMode_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingSourceMode_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingSourceMode_Statics::Enum_MetaDataParams), Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingSourceMode_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingSourceMode()
{
	if (!Z_Registration_Info_UEnum_EGaussianSplattingSourceMode.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EGaussianSplattingSourceMode.InnerSingleton, Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingSourceMode_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EGaussianSplattingSourceMode.InnerSingleton;
}
// End Enum EGaussianSplattingSourceMode

// Begin Enum EGaussianSplattingCameraMode
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EGaussianSplattingCameraMode;
static UEnum* EGaussianSplattingCameraMode_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EGaussianSplattingCameraMode.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EGaussianSplattingCameraMode.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingCameraMode, (UObject*)Z_Construct_UPackage__Script_GaussianSplattingEditor(), TEXT("EGaussianSplattingCameraMode"));
	}
	return Z_Registration_Info_UEnum_EGaussianSplattingCameraMode.OuterSingleton;
}
template<> GAUSSIANSPLATTINGEDITOR_API UEnum* StaticEnum<EGaussianSplattingCameraMode>()
{
	return EGaussianSplattingCameraMode_StaticEnum();
}
struct Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingCameraMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Hemisphere.Name", "EGaussianSplattingCameraMode::Hemisphere" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
		{ "Sphere.Name", "EGaussianSplattingCameraMode::Sphere" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EGaussianSplattingCameraMode::Hemisphere", (int64)EGaussianSplattingCameraMode::Hemisphere },
		{ "EGaussianSplattingCameraMode::Sphere", (int64)EGaussianSplattingCameraMode::Sphere },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingCameraMode_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_GaussianSplattingEditor,
	nullptr,
	"EGaussianSplattingCameraMode",
	"EGaussianSplattingCameraMode",
	Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingCameraMode_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingCameraMode_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingCameraMode_Statics::Enum_MetaDataParams), Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingCameraMode_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingCameraMode()
{
	if (!Z_Registration_Info_UEnum_EGaussianSplattingCameraMode.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EGaussianSplattingCameraMode.InnerSingleton, Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingCameraMode_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EGaussianSplattingCameraMode.InnerSingleton;
}
// End Enum EGaussianSplattingCameraMode

// Begin Enum EGaussianSplattingStepStatus
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EGaussianSplattingStepStatus;
static UEnum* EGaussianSplattingStepStatus_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EGaussianSplattingStepStatus.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EGaussianSplattingStepStatus.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingStepStatus, (UObject*)Z_Construct_UPackage__Script_GaussianSplattingEditor(), TEXT("EGaussianSplattingStepStatus"));
	}
	return Z_Registration_Info_UEnum_EGaussianSplattingStepStatus.OuterSingleton;
}
template<> GAUSSIANSPLATTINGEDITOR_API UEnum* StaticEnum<EGaussianSplattingStepStatus>()
{
	return EGaussianSplattingStepStatus_StaticEnum();
}
struct Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingStepStatus_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
		{ "None.Name", "EGaussianSplattingStepStatus::None" },
		{ "Outdated.Name", "EGaussianSplattingStepStatus::Outdated" },
		{ "Running.Name", "EGaussianSplattingStepStatus::Running" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EGaussianSplattingStepStatus::None", (int64)EGaussianSplattingStepStatus::None },
		{ "EGaussianSplattingStepStatus::Running", (int64)EGaussianSplattingStepStatus::Running },
		{ "EGaussianSplattingStepStatus::Outdated", (int64)EGaussianSplattingStepStatus::Outdated },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingStepStatus_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_GaussianSplattingEditor,
	nullptr,
	"EGaussianSplattingStepStatus",
	"EGaussianSplattingStepStatus",
	Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingStepStatus_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingStepStatus_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingStepStatus_Statics::Enum_MetaDataParams), Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingStepStatus_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingStepStatus()
{
	if (!Z_Registration_Info_UEnum_EGaussianSplattingStepStatus.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EGaussianSplattingStepStatus.InnerSingleton, Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingStepStatus_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EGaussianSplattingStepStatus.InnerSingleton;
}
// End Enum EGaussianSplattingStepStatus

// Begin Enum EGaussianSplattingOutputType
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EGaussianSplattingOutputType;
static UEnum* EGaussianSplattingOutputType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EGaussianSplattingOutputType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EGaussianSplattingOutputType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingOutputType, (UObject*)Z_Construct_UPackage__Script_GaussianSplattingEditor(), TEXT("EGaussianSplattingOutputType"));
	}
	return Z_Registration_Info_UEnum_EGaussianSplattingOutputType.OuterSingleton;
}
template<> GAUSSIANSPLATTINGEDITOR_API UEnum* StaticEnum<EGaussianSplattingOutputType>()
{
	return EGaussianSplattingOutputType_StaticEnum();
}
struct Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingOutputType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
		{ "Niagara.Name", "EGaussianSplattingOutputType::Niagara" },
		{ "StaticMesh.Name", "EGaussianSplattingOutputType::StaticMesh" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EGaussianSplattingOutputType::Niagara", (int64)EGaussianSplattingOutputType::Niagara },
		{ "EGaussianSplattingOutputType::StaticMesh", (int64)EGaussianSplattingOutputType::StaticMesh },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingOutputType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_GaussianSplattingEditor,
	nullptr,
	"EGaussianSplattingOutputType",
	"EGaussianSplattingOutputType",
	Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingOutputType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingOutputType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingOutputType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingOutputType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingOutputType()
{
	if (!Z_Registration_Info_UEnum_EGaussianSplattingOutputType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EGaussianSplattingOutputType.InnerSingleton, Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingOutputType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EGaussianSplattingOutputType.InnerSingleton;
}
// End Enum EGaussianSplattingOutputType

// Begin Class UGaussianSplattingStepBase
void UGaussianSplattingStepBase::StaticRegisterNativesUGaussianSplattingStepBase()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGaussianSplattingStepBase);
UClass* Z_Construct_UClass_UGaussianSplattingStepBase_NoRegister()
{
	return UGaussianSplattingStepBase::StaticClass();
}
struct Z_Construct_UClass_UGaussianSplattingStepBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "DisplayName", "Gaussian Splatting Editor" },
		{ "IncludePath", "GaussianSplattingStep.h" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGaussianSplattingStepBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UGaussianSplattingStepBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_GaussianSplattingEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingStepBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGaussianSplattingStepBase_Statics::ClassParams = {
	&UGaussianSplattingStepBase::StaticClass,
	"GaussianSplattingEditor",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x000030A2u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingStepBase_Statics::Class_MetaDataParams), Z_Construct_UClass_UGaussianSplattingStepBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGaussianSplattingStepBase()
{
	if (!Z_Registration_Info_UClass_UGaussianSplattingStepBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGaussianSplattingStepBase.OuterSingleton, Z_Construct_UClass_UGaussianSplattingStepBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGaussianSplattingStepBase.OuterSingleton;
}
template<> GAUSSIANSPLATTINGEDITOR_API UClass* StaticClass<UGaussianSplattingStepBase>()
{
	return UGaussianSplattingStepBase::StaticClass();
}
UGaussianSplattingStepBase::UGaussianSplattingStepBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGaussianSplattingStepBase);
UGaussianSplattingStepBase::~UGaussianSplattingStepBase() {}
// End Class UGaussianSplattingStepBase

// Begin Class UGaussianSplattingStep_Capture Function Browse
struct Z_Construct_UFunction_UGaussianSplattingStep_Capture_Browse_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "DisplayPriority", "4" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGaussianSplattingStep_Capture_Browse_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGaussianSplattingStep_Capture, nullptr, "Browse", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGaussianSplattingStep_Capture_Browse_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGaussianSplattingStep_Capture_Browse_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UGaussianSplattingStep_Capture_Browse()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGaussianSplattingStep_Capture_Browse_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGaussianSplattingStep_Capture::execBrowse)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Browse();
	P_NATIVE_END;
}
// End Class UGaussianSplattingStep_Capture Function Browse

// Begin Class UGaussianSplattingStep_Capture Function Capture
struct Z_Construct_UFunction_UGaussianSplattingStep_Capture_Capture_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "DisplayPriority", "1" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGaussianSplattingStep_Capture_Capture_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGaussianSplattingStep_Capture, nullptr, "Capture", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGaussianSplattingStep_Capture_Capture_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGaussianSplattingStep_Capture_Capture_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UGaussianSplattingStep_Capture_Capture()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGaussianSplattingStep_Capture_Capture_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGaussianSplattingStep_Capture::execCapture)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Capture();
	P_NATIVE_END;
}
// End Class UGaussianSplattingStep_Capture Function Capture

// Begin Class UGaussianSplattingStep_Capture Function NextCamera
struct Z_Construct_UFunction_UGaussianSplattingStep_Capture_NextCamera_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "DisplayPriority", "3" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGaussianSplattingStep_Capture_NextCamera_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGaussianSplattingStep_Capture, nullptr, "NextCamera", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGaussianSplattingStep_Capture_NextCamera_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGaussianSplattingStep_Capture_NextCamera_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UGaussianSplattingStep_Capture_NextCamera()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGaussianSplattingStep_Capture_NextCamera_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGaussianSplattingStep_Capture::execNextCamera)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->NextCamera();
	P_NATIVE_END;
}
// End Class UGaussianSplattingStep_Capture Function NextCamera

// Begin Class UGaussianSplattingStep_Capture Function PrevCamera
struct Z_Construct_UFunction_UGaussianSplattingStep_Capture_PrevCamera_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "DisplayPriority", "2" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGaussianSplattingStep_Capture_PrevCamera_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGaussianSplattingStep_Capture, nullptr, "PrevCamera", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGaussianSplattingStep_Capture_PrevCamera_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGaussianSplattingStep_Capture_PrevCamera_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UGaussianSplattingStep_Capture_PrevCamera()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGaussianSplattingStep_Capture_PrevCamera_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGaussianSplattingStep_Capture::execPrevCamera)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PrevCamera();
	P_NATIVE_END;
}
// End Class UGaussianSplattingStep_Capture Function PrevCamera

// Begin Class UGaussianSplattingStep_Capture
void UGaussianSplattingStep_Capture::StaticRegisterNativesUGaussianSplattingStep_Capture()
{
	UClass* Class = UGaussianSplattingStep_Capture::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "Browse", &UGaussianSplattingStep_Capture::execBrowse },
		{ "Capture", &UGaussianSplattingStep_Capture::execCapture },
		{ "NextCamera", &UGaussianSplattingStep_Capture::execNextCamera },
		{ "PrevCamera", &UGaussianSplattingStep_Capture::execPrevCamera },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGaussianSplattingStep_Capture);
UClass* Z_Construct_UClass_UGaussianSplattingStep_Capture_NoRegister()
{
	return UGaussianSplattingStep_Capture::StaticClass();
}
struct Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "DisplayName", "Gaussian Splatting Editor" },
		{ "IncludePath", "GaussianSplattingStep.h" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceMode_MetaData[] = {
		{ "Category", "GaussianSplattingStep_Capture" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SelectionActors_MetaData[] = {
		{ "Category", "GaussianSplattingStep_Capture" },
		{ "EditCondition", "SourceMode == EGaussianSplattingSourceMode::Select" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraMode_MetaData[] = {
		{ "Category", "GaussianSplattingStep_Capture" },
		{ "EditCondition", "SourceMode != EGaussianSplattingSourceMode::Custom" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FrameXY_MetaData[] = {
		{ "Category", "GaussianSplattingStep_Capture" },
		{ "EditCondition", "SourceMode != EGaussianSplattingSourceMode::Custom" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CaptureDistanceScale_MetaData[] = {
		{ "Category", "GaussianSplattingStep_Capture" },
		{ "ClampMin", "0.010000" },
		{ "EditCondition", "SourceMode != EGaussianSplattingSourceMode::Custom" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
		{ "UIMax", "2" },
		{ "UIMin", "0.010000" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LocateActor_MetaData[] = {
		{ "Category", "GaussianSplattingStep_Capture" },
		{ "EditCondition", "SourceMode == EGaussianSplattingSourceMode::Locate" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HiddenActors_MetaData[] = {
		{ "Category", "GaussianSplattingStep_Capture" },
		{ "EditCondition", "SourceMode != EGaussianSplattingSourceMode::Select" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SceneCapture_MetaData[] = {
		{ "Category", "GaussianSplattingStep_Capture" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RenderTarget_MetaData[] = {
		{ "Category", "GaussianSplattingStep_Capture" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RenderTargetResolution_MetaData[] = {
		{ "Category", "GaussianSplattingStep_Capture" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bCaptureDepth_MetaData[] = {
		{ "Category", "GaussianSplattingStep_Capture" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ShowFlagSettings_MetaData[] = {
		{ "Category", "GaussianSplattingStep_Capture" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraActors_MetaData[] = {
		{ "Category", "GaussianSplattingStep_Capture" },
		{ "EditCondition", "SourceMode == EGaussianSplattingSourceMode::Custom" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_SourceMode_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_SourceMode;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SelectionActors_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_SelectionActors;
	static const UECodeGen_Private::FBytePropertyParams NewProp_CameraMode_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_CameraMode;
	static const UECodeGen_Private::FIntPropertyParams NewProp_FrameXY;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CaptureDistanceScale;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LocateActor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HiddenActors_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_HiddenActors;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SceneCapture;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RenderTarget;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RenderTargetResolution;
	static void NewProp_bCaptureDepth_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bCaptureDepth;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ShowFlagSettings_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ShowFlagSettings;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraActors_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_CameraActors;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UGaussianSplattingStep_Capture_Browse, "Browse" }, // 1010693051
		{ &Z_Construct_UFunction_UGaussianSplattingStep_Capture_Capture, "Capture" }, // 2377276357
		{ &Z_Construct_UFunction_UGaussianSplattingStep_Capture_NextCamera, "NextCamera" }, // 3100950669
		{ &Z_Construct_UFunction_UGaussianSplattingStep_Capture_PrevCamera, "PrevCamera" }, // 604532048
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGaussianSplattingStep_Capture>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_SourceMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_SourceMode = { "SourceMode", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_Capture, SourceMode), Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingSourceMode, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceMode_MetaData), NewProp_SourceMode_MetaData) }; // 1421777370
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_SelectionActors_Inner = { "SelectionActors", nullptr, (EPropertyFlags)0x0104000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_SelectionActors = { "SelectionActors", nullptr, (EPropertyFlags)0x0114000000002001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_Capture, SelectionActors), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SelectionActors_MetaData), NewProp_SelectionActors_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_CameraMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_CameraMode = { "CameraMode", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_Capture, CameraMode), Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingCameraMode, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraMode_MetaData), NewProp_CameraMode_MetaData) }; // 3184489191
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_FrameXY = { "FrameXY", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_Capture, FrameXY), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FrameXY_MetaData), NewProp_FrameXY_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_CaptureDistanceScale = { "CaptureDistanceScale", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_Capture, CaptureDistanceScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CaptureDistanceScale_MetaData), NewProp_CaptureDistanceScale_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_LocateActor = { "LocateActor", nullptr, (EPropertyFlags)0x0114000000022001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_Capture, LocateActor), Z_Construct_UClass_ATriggerSphere_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LocateActor_MetaData), NewProp_LocateActor_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_HiddenActors_Inner = { "HiddenActors", nullptr, (EPropertyFlags)0x0104000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_HiddenActors = { "HiddenActors", nullptr, (EPropertyFlags)0x0114000000002001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_Capture, HiddenActors), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HiddenActors_MetaData), NewProp_HiddenActors_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_SceneCapture = { "SceneCapture", nullptr, (EPropertyFlags)0x0114000000022001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_Capture, SceneCapture), Z_Construct_UClass_ASceneCapture2D_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SceneCapture_MetaData), NewProp_SceneCapture_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_RenderTarget = { "RenderTarget", nullptr, (EPropertyFlags)0x0114000000022001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_Capture, RenderTarget), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RenderTarget_MetaData), NewProp_RenderTarget_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_RenderTargetResolution = { "RenderTargetResolution", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_Capture, RenderTargetResolution), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RenderTargetResolution_MetaData), NewProp_RenderTargetResolution_MetaData) };
void Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_bCaptureDepth_SetBit(void* Obj)
{
	((UGaussianSplattingStep_Capture*)Obj)->bCaptureDepth = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_bCaptureDepth = { "bCaptureDepth", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UGaussianSplattingStep_Capture), &Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_bCaptureDepth_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bCaptureDepth_MetaData), NewProp_bCaptureDepth_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_ShowFlagSettings_Inner = { "ShowFlagSettings", nullptr, (EPropertyFlags)0x0000000000004000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FEngineShowFlagsSetting, METADATA_PARAMS(0, nullptr) }; // 3559122429
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_ShowFlagSettings = { "ShowFlagSettings", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_Capture, ShowFlagSettings), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ShowFlagSettings_MetaData), NewProp_ShowFlagSettings_MetaData) }; // 3559122429
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_CameraActors_Inner = { "CameraActors", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_CameraActors = { "CameraActors", nullptr, (EPropertyFlags)0x0010000000002001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_Capture, CameraActors), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraActors_MetaData), NewProp_CameraActors_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_SourceMode_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_SourceMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_SelectionActors_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_SelectionActors,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_CameraMode_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_CameraMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_FrameXY,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_CaptureDistanceScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_LocateActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_HiddenActors_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_HiddenActors,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_SceneCapture,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_RenderTarget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_RenderTargetResolution,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_bCaptureDepth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_ShowFlagSettings_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_ShowFlagSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_CameraActors_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::NewProp_CameraActors,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGaussianSplattingStepBase,
	(UObject* (*)())Z_Construct_UPackage__Script_GaussianSplattingEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::ClassParams = {
	&UGaussianSplattingStep_Capture::StaticClass,
	"GaussianSplattingEditor",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::PropPointers),
	0,
	0x000030A6u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::Class_MetaDataParams), Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGaussianSplattingStep_Capture()
{
	if (!Z_Registration_Info_UClass_UGaussianSplattingStep_Capture.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGaussianSplattingStep_Capture.OuterSingleton, Z_Construct_UClass_UGaussianSplattingStep_Capture_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGaussianSplattingStep_Capture.OuterSingleton;
}
template<> GAUSSIANSPLATTINGEDITOR_API UClass* StaticClass<UGaussianSplattingStep_Capture>()
{
	return UGaussianSplattingStep_Capture::StaticClass();
}
UGaussianSplattingStep_Capture::UGaussianSplattingStep_Capture(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGaussianSplattingStep_Capture);
UGaussianSplattingStep_Capture::~UGaussianSplattingStep_Capture() {}
// End Class UGaussianSplattingStep_Capture

// Begin Class UGaussianSplattingStep_SparseReconstruction Function ColmapEdit
struct Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_ColmapEdit_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "DisplayPriority", "2" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_ColmapEdit_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction, nullptr, "ColmapEdit", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_ColmapEdit_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_ColmapEdit_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_ColmapEdit()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_ColmapEdit_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGaussianSplattingStep_SparseReconstruction::execColmapEdit)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ColmapEdit();
	P_NATIVE_END;
}
// End Class UGaussianSplattingStep_SparseReconstruction Function ColmapEdit

// Begin Class UGaussianSplattingStep_SparseReconstruction Function ColmapView
struct Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_ColmapView_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "DisplayPriority", "3" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_ColmapView_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction, nullptr, "ColmapView", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_ColmapView_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_ColmapView_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_ColmapView()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_ColmapView_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGaussianSplattingStep_SparseReconstruction::execColmapView)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ColmapView();
	P_NATIVE_END;
}
// End Class UGaussianSplattingStep_SparseReconstruction Function ColmapView

// Begin Class UGaussianSplattingStep_SparseReconstruction Function Reconstruction
struct Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_Reconstruction_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "DisplayPriority", "1" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_Reconstruction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction, nullptr, "Reconstruction", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_Reconstruction_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_Reconstruction_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_Reconstruction()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_Reconstruction_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGaussianSplattingStep_SparseReconstruction::execReconstruction)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Reconstruction();
	P_NATIVE_END;
}
// End Class UGaussianSplattingStep_SparseReconstruction Function Reconstruction

// Begin Class UGaussianSplattingStep_SparseReconstruction
void UGaussianSplattingStep_SparseReconstruction::StaticRegisterNativesUGaussianSplattingStep_SparseReconstruction()
{
	UClass* Class = UGaussianSplattingStep_SparseReconstruction::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ColmapEdit", &UGaussianSplattingStep_SparseReconstruction::execColmapEdit },
		{ "ColmapView", &UGaussianSplattingStep_SparseReconstruction::execColmapView },
		{ "Reconstruction", &UGaussianSplattingStep_SparseReconstruction::execReconstruction },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGaussianSplattingStep_SparseReconstruction);
UClass* Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_NoRegister()
{
	return UGaussianSplattingStep_SparseReconstruction::StaticClass();
}
struct Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "DisplayName", "Gaussian Splatting Editor" },
		{ "IncludePath", "GaussianSplattingStep.h" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FeatureExtractorParams_MetaData[] = {
		{ "Category", "Feature Extractor" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxNumFeaturtes_MetaData[] = {
		{ "Category", "Feature Extractor" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FeatureExtractorParamsCustom_MetaData[] = {
		{ "Category", "Feature Extractor" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExhaustiveMatcherParams_MetaData[] = {
		{ "Category", "Exhaustive Matcher" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExhaustiveMatcherParamsCustom_MetaData[] = {
		{ "Category", "Exhaustive Matcher" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MapperParams_MetaData[] = {
		{ "Category", "Mapper" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AbsPoseMinNumInliers_MetaData[] = {
		{ "Category", "Mapper" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MapperParamsCustom_MetaData[] = {
		{ "Category", "Mapper" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ModelAlignerParams_MetaData[] = {
		{ "Category", "Model Aligner" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ModelAlignerParamsCustom_MetaData[] = {
		{ "Category", "Model Aligner" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_FeatureExtractorParams;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxNumFeaturtes;
	static const UECodeGen_Private::FStrPropertyParams NewProp_FeatureExtractorParamsCustom;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ExhaustiveMatcherParams;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ExhaustiveMatcherParamsCustom;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MapperParams;
	static const UECodeGen_Private::FIntPropertyParams NewProp_AbsPoseMinNumInliers;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MapperParamsCustom;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ModelAlignerParams;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ModelAlignerParamsCustom;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_ColmapEdit, "ColmapEdit" }, // 212051745
		{ &Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_ColmapView, "ColmapView" }, // 3732960306
		{ &Z_Construct_UFunction_UGaussianSplattingStep_SparseReconstruction_Reconstruction, "Reconstruction" }, // 3590172945
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGaussianSplattingStep_SparseReconstruction>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_FeatureExtractorParams = { "FeatureExtractorParams", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_SparseReconstruction, FeatureExtractorParams), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FeatureExtractorParams_MetaData), NewProp_FeatureExtractorParams_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_MaxNumFeaturtes = { "MaxNumFeaturtes", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_SparseReconstruction, MaxNumFeaturtes), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxNumFeaturtes_MetaData), NewProp_MaxNumFeaturtes_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_FeatureExtractorParamsCustom = { "FeatureExtractorParamsCustom", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_SparseReconstruction, FeatureExtractorParamsCustom), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FeatureExtractorParamsCustom_MetaData), NewProp_FeatureExtractorParamsCustom_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_ExhaustiveMatcherParams = { "ExhaustiveMatcherParams", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_SparseReconstruction, ExhaustiveMatcherParams), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExhaustiveMatcherParams_MetaData), NewProp_ExhaustiveMatcherParams_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_ExhaustiveMatcherParamsCustom = { "ExhaustiveMatcherParamsCustom", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_SparseReconstruction, ExhaustiveMatcherParamsCustom), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExhaustiveMatcherParamsCustom_MetaData), NewProp_ExhaustiveMatcherParamsCustom_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_MapperParams = { "MapperParams", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_SparseReconstruction, MapperParams), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MapperParams_MetaData), NewProp_MapperParams_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_AbsPoseMinNumInliers = { "AbsPoseMinNumInliers", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_SparseReconstruction, AbsPoseMinNumInliers), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AbsPoseMinNumInliers_MetaData), NewProp_AbsPoseMinNumInliers_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_MapperParamsCustom = { "MapperParamsCustom", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_SparseReconstruction, MapperParamsCustom), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MapperParamsCustom_MetaData), NewProp_MapperParamsCustom_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_ModelAlignerParams = { "ModelAlignerParams", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_SparseReconstruction, ModelAlignerParams), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ModelAlignerParams_MetaData), NewProp_ModelAlignerParams_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_ModelAlignerParamsCustom = { "ModelAlignerParamsCustom", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_SparseReconstruction, ModelAlignerParamsCustom), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ModelAlignerParamsCustom_MetaData), NewProp_ModelAlignerParamsCustom_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_FeatureExtractorParams,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_MaxNumFeaturtes,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_FeatureExtractorParamsCustom,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_ExhaustiveMatcherParams,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_ExhaustiveMatcherParamsCustom,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_MapperParams,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_AbsPoseMinNumInliers,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_MapperParamsCustom,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_ModelAlignerParams,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::NewProp_ModelAlignerParamsCustom,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGaussianSplattingStepBase,
	(UObject* (*)())Z_Construct_UPackage__Script_GaussianSplattingEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::ClassParams = {
	&UGaussianSplattingStep_SparseReconstruction::StaticClass,
	"GaussianSplattingEditor",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::PropPointers),
	0,
	0x000030A6u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::Class_MetaDataParams), Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction()
{
	if (!Z_Registration_Info_UClass_UGaussianSplattingStep_SparseReconstruction.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGaussianSplattingStep_SparseReconstruction.OuterSingleton, Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGaussianSplattingStep_SparseReconstruction.OuterSingleton;
}
template<> GAUSSIANSPLATTINGEDITOR_API UClass* StaticClass<UGaussianSplattingStep_SparseReconstruction>()
{
	return UGaussianSplattingStep_SparseReconstruction::StaticClass();
}
UGaussianSplattingStep_SparseReconstruction::UGaussianSplattingStep_SparseReconstruction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGaussianSplattingStep_SparseReconstruction);
UGaussianSplattingStep_SparseReconstruction::~UGaussianSplattingStep_SparseReconstruction() {}
// End Class UGaussianSplattingStep_SparseReconstruction

// Begin Class UGaussianSplattingStep_GaussianSplatting Function Reload
struct Z_Construct_UFunction_UGaussianSplattingStep_GaussianSplatting_Reload_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "DisplayPriority", "2" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGaussianSplattingStep_GaussianSplatting_Reload_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting, nullptr, "Reload", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGaussianSplattingStep_GaussianSplatting_Reload_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGaussianSplattingStep_GaussianSplatting_Reload_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UGaussianSplattingStep_GaussianSplatting_Reload()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGaussianSplattingStep_GaussianSplatting_Reload_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGaussianSplattingStep_GaussianSplatting::execReload)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Reload();
	P_NATIVE_END;
}
// End Class UGaussianSplattingStep_GaussianSplatting Function Reload

// Begin Class UGaussianSplattingStep_GaussianSplatting Function Train
struct Z_Construct_UFunction_UGaussianSplattingStep_GaussianSplatting_Train_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "DisplayPriority", "1" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGaussianSplattingStep_GaussianSplatting_Train_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting, nullptr, "Train", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGaussianSplattingStep_GaussianSplatting_Train_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGaussianSplattingStep_GaussianSplatting_Train_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UGaussianSplattingStep_GaussianSplatting_Train()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGaussianSplattingStep_GaussianSplatting_Train_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGaussianSplattingStep_GaussianSplatting::execTrain)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Train();
	P_NATIVE_END;
}
// End Class UGaussianSplattingStep_GaussianSplatting Function Train

// Begin Class UGaussianSplattingStep_GaussianSplatting
void UGaussianSplattingStep_GaussianSplatting::StaticRegisterNativesUGaussianSplattingStep_GaussianSplatting()
{
	UClass* Class = UGaussianSplattingStep_GaussianSplatting::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "Reload", &UGaussianSplattingStep_GaussianSplatting::execReload },
		{ "Train", &UGaussianSplattingStep_GaussianSplatting::execTrain },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGaussianSplattingStep_GaussianSplatting);
UClass* Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_NoRegister()
{
	return UGaussianSplattingStep_GaussianSplatting::StaticClass();
}
struct Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "DisplayName", "Gaussian Splatting Editor" },
		{ "IncludePath", "GaussianSplattingStep.h" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GaussianSplattingTrainParams_MetaData[] = {
		{ "Category", "Train" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Resolution_MetaData[] = {
		{ "Category", "Train" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
		{ "UIMax", "8" },
		{ "UIMin", "1" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Iterations_MetaData[] = {
		{ "Category", "Train" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
#if !UE_BUILD_SHIPPING
		{ "Tooltip", "Number of total iterations to train for." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Feature_LR_MetaData[] = {
		{ "Category", "Train" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
#if !UE_BUILD_SHIPPING
		{ "Tooltip", "Spherical harmonics features learning rate." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Opacity_LR_MetaData[] = {
		{ "Category", "Train" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
#if !UE_BUILD_SHIPPING
		{ "Tooltip", "Opacity learning rate." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Scaling_LR_MetaData[] = {
		{ "Category", "Train" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
#if !UE_BUILD_SHIPPING
		{ "Tooltip", "Scaling learning rate." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Rotation_LR_MetaData[] = {
		{ "Category", "Train" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
#if !UE_BUILD_SHIPPING
		{ "Tooltip", "Rotation learning rate." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_LR_MaxSteps_MetaData[] = {
		{ "Category", "Train" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
#if !UE_BUILD_SHIPPING
		{ "Tooltip", "Number of steps (from 0) where position learning rate goes from to." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_LR_Init_MetaData[] = {
		{ "Category", "Train" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
#if !UE_BUILD_SHIPPING
		{ "Tooltip", "Initial 3D position learning rate." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_LR_Final_MetaData[] = {
		{ "Category", "Train" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
#if !UE_BUILD_SHIPPING
		{ "Tooltip", "Final 3D position learning rate." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_LR_DelayMult_MetaData[] = {
		{ "Category", "Train" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
#if !UE_BUILD_SHIPPING
		{ "Tooltip", "Position learning rate multiplier." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DensifyFromIter_MetaData[] = {
		{ "Category", "Train" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
#if !UE_BUILD_SHIPPING
		{ "Tooltip", "Iteration where densification starts." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DensifyUntilIter_MetaData[] = {
		{ "Category", "Train" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
#if !UE_BUILD_SHIPPING
		{ "Tooltip", "Iteration where densification stops." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DensifyGradThreshold_MetaData[] = {
		{ "Category", "Train" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
#if !UE_BUILD_SHIPPING
		{ "Tooltip", "Limit that decides if points should be densified based on 2D position gradient." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DensificationInterval_MetaData[] = {
		{ "Category", "Train" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
#if !UE_BUILD_SHIPPING
		{ "Tooltip", "How frequently to densify." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OpacityResetInterval_MetaData[] = {
		{ "Category", "Train" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
#if !UE_BUILD_SHIPPING
		{ "Tooltip", "How frequently to reset opacity." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Depth_L1_WeightInit_MetaData[] = {
		{ "Category", "Train" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
		{ "UIMax", "1" },
		{ "UIMin", "0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Depth_L1_WeightFinal_MetaData[] = {
		{ "Category", "Train" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
		{ "UIMax", "1" },
		{ "UIMin", "0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LambdaDssim_MetaData[] = {
		{ "Category", "Train" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
#if !UE_BUILD_SHIPPING
		{ "Tooltip", "Influence of SSIM on total loss from 0 to 1." },
#endif
		{ "UIMax", "1" },
		{ "UIMin", "0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PercentDense_MetaData[] = {
		{ "Category", "Train" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
#if !UE_BUILD_SHIPPING
		{ "Tooltip", "Percentage of scene extent (0--1) a point must exceed to be forcibly densified" },
#endif
		{ "UIMax", "1" },
		{ "UIMin", "0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OutputType_MetaData[] = {
		{ "Category", "Output" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bClippingByBound_MetaData[] = {
		{ "Category", "Output" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClippingBound_MetaData[] = {
		{ "Category", "Output" },
		{ "EditCondition", "bClippingByBound" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DistanceOfObservation_MetaData[] = {
		{ "Category", "Output" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinScreenSizeOfObservation_MetaData[] = {
		{ "Category", "Output" },
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlyLoadCache_MetaData[] = {
		{ "ModuleRelativePath", "Private/GaussianSplattingStep.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_GaussianSplattingTrainParams;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Resolution;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Iterations;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Feature_LR;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Opacity_LR;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Scaling_LR;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Rotation_LR;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Position_LR_MaxSteps;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Position_LR_Init;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Position_LR_Final;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Position_LR_DelayMult;
	static const UECodeGen_Private::FIntPropertyParams NewProp_DensifyFromIter;
	static const UECodeGen_Private::FIntPropertyParams NewProp_DensifyUntilIter;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DensifyGradThreshold;
	static const UECodeGen_Private::FIntPropertyParams NewProp_DensificationInterval;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OpacityResetInterval;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Depth_L1_WeightInit;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Depth_L1_WeightFinal;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LambdaDssim;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PercentDense;
	static const UECodeGen_Private::FBytePropertyParams NewProp_OutputType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_OutputType;
	static void NewProp_bClippingByBound_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bClippingByBound;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ClippingBound;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DistanceOfObservation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinScreenSizeOfObservation;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlyLoadCache;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UGaussianSplattingStep_GaussianSplatting_Reload, "Reload" }, // 4018765976
		{ &Z_Construct_UFunction_UGaussianSplattingStep_GaussianSplatting_Train, "Train" }, // 1116314619
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGaussianSplattingStep_GaussianSplatting>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_GaussianSplattingTrainParams = { "GaussianSplattingTrainParams", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, GaussianSplattingTrainParams), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GaussianSplattingTrainParams_MetaData), NewProp_GaussianSplattingTrainParams_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Resolution = { "Resolution", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, Resolution), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Resolution_MetaData), NewProp_Resolution_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Iterations = { "Iterations", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, Iterations), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Iterations_MetaData), NewProp_Iterations_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Feature_LR = { "Feature_LR", nullptr, (EPropertyFlags)0x0010040000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, Feature_LR), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Feature_LR_MetaData), NewProp_Feature_LR_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Opacity_LR = { "Opacity_LR", nullptr, (EPropertyFlags)0x0010040000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, Opacity_LR), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Opacity_LR_MetaData), NewProp_Opacity_LR_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Scaling_LR = { "Scaling_LR", nullptr, (EPropertyFlags)0x0010040000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, Scaling_LR), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Scaling_LR_MetaData), NewProp_Scaling_LR_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Rotation_LR = { "Rotation_LR", nullptr, (EPropertyFlags)0x0010040000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, Rotation_LR), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rotation_LR_MetaData), NewProp_Rotation_LR_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Position_LR_MaxSteps = { "Position_LR_MaxSteps", nullptr, (EPropertyFlags)0x0010040000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, Position_LR_MaxSteps), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_LR_MaxSteps_MetaData), NewProp_Position_LR_MaxSteps_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Position_LR_Init = { "Position_LR_Init", nullptr, (EPropertyFlags)0x0010040000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, Position_LR_Init), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_LR_Init_MetaData), NewProp_Position_LR_Init_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Position_LR_Final = { "Position_LR_Final", nullptr, (EPropertyFlags)0x0010040000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, Position_LR_Final), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_LR_Final_MetaData), NewProp_Position_LR_Final_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Position_LR_DelayMult = { "Position_LR_DelayMult", nullptr, (EPropertyFlags)0x0010040000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, Position_LR_DelayMult), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_LR_DelayMult_MetaData), NewProp_Position_LR_DelayMult_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_DensifyFromIter = { "DensifyFromIter", nullptr, (EPropertyFlags)0x0010040000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, DensifyFromIter), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DensifyFromIter_MetaData), NewProp_DensifyFromIter_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_DensifyUntilIter = { "DensifyUntilIter", nullptr, (EPropertyFlags)0x0010040000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, DensifyUntilIter), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DensifyUntilIter_MetaData), NewProp_DensifyUntilIter_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_DensifyGradThreshold = { "DensifyGradThreshold", nullptr, (EPropertyFlags)0x0010040000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, DensifyGradThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DensifyGradThreshold_MetaData), NewProp_DensifyGradThreshold_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_DensificationInterval = { "DensificationInterval", nullptr, (EPropertyFlags)0x0010040000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, DensificationInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DensificationInterval_MetaData), NewProp_DensificationInterval_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_OpacityResetInterval = { "OpacityResetInterval", nullptr, (EPropertyFlags)0x0010040000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, OpacityResetInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OpacityResetInterval_MetaData), NewProp_OpacityResetInterval_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Depth_L1_WeightInit = { "Depth_L1_WeightInit", nullptr, (EPropertyFlags)0x0010040000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, Depth_L1_WeightInit), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Depth_L1_WeightInit_MetaData), NewProp_Depth_L1_WeightInit_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Depth_L1_WeightFinal = { "Depth_L1_WeightFinal", nullptr, (EPropertyFlags)0x0010040000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, Depth_L1_WeightFinal), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Depth_L1_WeightFinal_MetaData), NewProp_Depth_L1_WeightFinal_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_LambdaDssim = { "LambdaDssim", nullptr, (EPropertyFlags)0x0010040000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, LambdaDssim), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LambdaDssim_MetaData), NewProp_LambdaDssim_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_PercentDense = { "PercentDense", nullptr, (EPropertyFlags)0x0010040000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, PercentDense), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PercentDense_MetaData), NewProp_PercentDense_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_OutputType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_OutputType = { "OutputType", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, OutputType), Z_Construct_UEnum_GaussianSplattingEditor_EGaussianSplattingOutputType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OutputType_MetaData), NewProp_OutputType_MetaData) }; // 4176072421
void Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_bClippingByBound_SetBit(void* Obj)
{
	((UGaussianSplattingStep_GaussianSplatting*)Obj)->bClippingByBound = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_bClippingByBound = { "bClippingByBound", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UGaussianSplattingStep_GaussianSplatting), &Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_bClippingByBound_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bClippingByBound_MetaData), NewProp_bClippingByBound_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_ClippingBound = { "ClippingBound", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, ClippingBound), Z_Construct_UScriptStruct_FBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClippingBound_MetaData), NewProp_ClippingBound_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_DistanceOfObservation = { "DistanceOfObservation", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, DistanceOfObservation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DistanceOfObservation_MetaData), NewProp_DistanceOfObservation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_MinScreenSizeOfObservation = { "MinScreenSizeOfObservation", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, MinScreenSizeOfObservation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinScreenSizeOfObservation_MetaData), NewProp_MinScreenSizeOfObservation_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_PlyLoadCache = { "PlyLoadCache", nullptr, (EPropertyFlags)0x0114000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGaussianSplattingStep_GaussianSplatting, PlyLoadCache), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlyLoadCache_MetaData), NewProp_PlyLoadCache_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_GaussianSplattingTrainParams,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Resolution,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Iterations,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Feature_LR,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Opacity_LR,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Scaling_LR,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Rotation_LR,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Position_LR_MaxSteps,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Position_LR_Init,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Position_LR_Final,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Position_LR_DelayMult,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_DensifyFromIter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_DensifyUntilIter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_DensifyGradThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_DensificationInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_OpacityResetInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Depth_L1_WeightInit,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_Depth_L1_WeightFinal,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_LambdaDssim,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_PercentDense,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_OutputType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_OutputType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_bClippingByBound,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_ClippingBound,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_DistanceOfObservation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_MinScreenSizeOfObservation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::NewProp_PlyLoadCache,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGaussianSplattingStepBase,
	(UObject* (*)())Z_Construct_UPackage__Script_GaussianSplattingEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::ClassParams = {
	&UGaussianSplattingStep_GaussianSplatting::StaticClass,
	"GaussianSplattingEditor",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::PropPointers),
	0,
	0x000030A6u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::Class_MetaDataParams), Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting()
{
	if (!Z_Registration_Info_UClass_UGaussianSplattingStep_GaussianSplatting.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGaussianSplattingStep_GaussianSplatting.OuterSingleton, Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGaussianSplattingStep_GaussianSplatting.OuterSingleton;
}
template<> GAUSSIANSPLATTINGEDITOR_API UClass* StaticClass<UGaussianSplattingStep_GaussianSplatting>()
{
	return UGaussianSplattingStep_GaussianSplatting::StaticClass();
}
UGaussianSplattingStep_GaussianSplatting::UGaussianSplattingStep_GaussianSplatting(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGaussianSplattingStep_GaussianSplatting);
UGaussianSplattingStep_GaussianSplatting::~UGaussianSplattingStep_GaussianSplatting() {}
// End Class UGaussianSplattingStep_GaussianSplatting

// Begin Registration
struct Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Source_GaussianSplattingEditor_Private_GaussianSplattingStep_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EGaussianSplattingSourceMode_StaticEnum, TEXT("EGaussianSplattingSourceMode"), &Z_Registration_Info_UEnum_EGaussianSplattingSourceMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1421777370U) },
		{ EGaussianSplattingCameraMode_StaticEnum, TEXT("EGaussianSplattingCameraMode"), &Z_Registration_Info_UEnum_EGaussianSplattingCameraMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3184489191U) },
		{ EGaussianSplattingStepStatus_StaticEnum, TEXT("EGaussianSplattingStepStatus"), &Z_Registration_Info_UEnum_EGaussianSplattingStepStatus, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3619305800U) },
		{ EGaussianSplattingOutputType_StaticEnum, TEXT("EGaussianSplattingOutputType"), &Z_Registration_Info_UEnum_EGaussianSplattingOutputType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 4176072421U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGaussianSplattingStepBase, UGaussianSplattingStepBase::StaticClass, TEXT("UGaussianSplattingStepBase"), &Z_Registration_Info_UClass_UGaussianSplattingStepBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGaussianSplattingStepBase), 1515013387U) },
		{ Z_Construct_UClass_UGaussianSplattingStep_Capture, UGaussianSplattingStep_Capture::StaticClass, TEXT("UGaussianSplattingStep_Capture"), &Z_Registration_Info_UClass_UGaussianSplattingStep_Capture, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGaussianSplattingStep_Capture), 4009583309U) },
		{ Z_Construct_UClass_UGaussianSplattingStep_SparseReconstruction, UGaussianSplattingStep_SparseReconstruction::StaticClass, TEXT("UGaussianSplattingStep_SparseReconstruction"), &Z_Registration_Info_UClass_UGaussianSplattingStep_SparseReconstruction, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGaussianSplattingStep_SparseReconstruction), 905170506U) },
		{ Z_Construct_UClass_UGaussianSplattingStep_GaussianSplatting, UGaussianSplattingStep_GaussianSplatting::StaticClass, TEXT("UGaussianSplattingStep_GaussianSplatting"), &Z_Registration_Info_UClass_UGaussianSplattingStep_GaussianSplatting, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGaussianSplattingStep_GaussianSplatting), 1315990315U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Source_GaussianSplattingEditor_Private_GaussianSplattingStep_h_3374084490(TEXT("/Script/GaussianSplattingEditor"),
	Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Source_GaussianSplattingEditor_Private_GaussianSplattingStep_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Source_GaussianSplattingEditor_Private_GaussianSplattingStep_h_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Source_GaussianSplattingEditor_Private_GaussianSplattingStep_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Publish_Proj54_Plugins_GaussianSplattingForUnrealEngine_Source_GaussianSplattingEditor_Private_GaussianSplattingStep_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
