#include "GaussianSplattingPointCloudDataInterface.h"
#include "NiagaraCompileHashVisitor.h"
#include "NiagaraShaderParametersBuilder.h"
#include "NiagaraSystemInstance.h"
#include "NiagaraRenderer.h"

#define LOCTEXT_NAMESPACE "GaussianSplatting"

static TAutoConsoleVariable<float> CVarGaussianSplattingScreenSizeBias(
	TEXT("r.GaussianSplatting.ScreenSizeBias"),
	0.0f,
	TEXT(""),
	ECVF_RenderThreadSafe | ECVF_Scalability);

static TAutoConsoleVariable<float> CVarGaussianSplattingMaxFeatureSize(
	TEXT("r.GaussianSplatting.MaxFeatureSize"),
	0.0f,
	TEXT(""),
	ECVF_RenderThreadSafe | ECVF_Scalability);

static TAutoConsoleVariable<float> CVarGaussianSplattingScreenSizeScale(
	TEXT("r.GaussianSplatting.ScreenSizeScale"),
	1.0f,
	TEXT(""),
	ECVF_RenderThreadSafe | ECVF_Scalability);

FNiagaraDataInterfaceProxyGaussianSplattingPointCloud::FNiagaraDataInterfaceProxyGaussianSplattingPointCloud(class UNiagaraDataInterfaceGaussianSplattingPointCloud* InOwner)
	: Owner(InOwner)
{

}

FNiagaraDataInterfaceProxyGaussianSplattingPointCloud::~FNiagaraDataInterfaceProxyGaussianSplattingPointCloud()
{

}

void FNiagaraDataInterfaceProxyGaussianSplattingPointCloud::MakeBufferDirty()
{
	bDirty = true;
}

void FNiagaraDataInterfaceProxyGaussianSplattingPointCloud::TryUpdateBuffer()
{
	if (PointCloud != Owner->PointCloud) {
		PointCloud = Owner->PointCloud;
		if (PointCloud) {
			PointCloud->OnPointsChanged.AddLambda([this]() {
				bDirty = true;
			});
		}
		bDirty = true;
	}
	if (bDirty) {
		PostDataToGPU();
		bDirty = false;
	}
}

void FNiagaraDataInterfaceProxyGaussianSplattingPointCloud::PostDataToGPU()
{
	if (Owner == nullptr || Owner->PointCloud == nullptr) {
		return;
	}
	const TArray<FGaussianSplattingPoint>& Points = Owner->PointCloud->GetPoints();
	TArray<FVector4f> PointData;
	PointData.SetNum(Points.Num() * 4);
	for (int i = 0; i < Points.Num(); i++) {
		const FGaussianSplattingPoint& Point = Points[i];
		PointData[i * 4] = Point.Position;
		PointData[i * 4 + 1] = FVector4f(Point.Quat.X, Point.Quat.Y, Point.Quat.Z, Point.Quat.W);
		PointData[i * 4 + 2] = Point.Scale;
		PointData[i * 4 + 3] = Point.Color;
	}

	ENQUEUE_RENDER_COMMAND(FUpdateSpectrumBuffer)(
		[this, PointData](FRHICommandListImmediate& RHICmdList)
		{
			const int32 NumBytesInBuffer = sizeof(FVector4f) * PointData.Num();

			if (NumBytesInBuffer != GaussianPointDataBuffer.NumBytes){
				if (GaussianPointDataBuffer.NumBytes > 0)
					GaussianPointDataBuffer.Release();
				if (NumBytesInBuffer > 0)
					GaussianPointDataBuffer.Initialize(RHICmdList, TEXT("FNiagaraDataInterfaceProxySpectrum_PositionBuffer"), sizeof(FVector4f), PointData.Num(), EPixelFormat::PF_A32B32G32R32F, BUF_Static);
			}

			if (GaussianPointDataBuffer.NumBytes > 0){
				float* BufferData = static_cast<float*>(RHICmdList.LockBuffer(GaussianPointDataBuffer.Buffer, 0, NumBytesInBuffer, EResourceLockMode::RLM_WriteOnly));
				FScopeLock ScopeLock(&BufferLock);
				FPlatformMemory::Memcpy(BufferData, PointData.GetData(), NumBytesInBuffer);
				RHICmdList.UnlockBuffer(GaussianPointDataBuffer.Buffer);
			}
		});
}

UNiagaraDataInterfaceGaussianSplattingPointCloud::UNiagaraDataInterfaceGaussianSplattingPointCloud(FObjectInitializer const& ObjectInitializer)
	: Super(ObjectInitializer)

{
	if (!HasAnyFlags(RF_ClassDefaultObject)){
		Proxy = MakeUnique<FNiagaraDataInterfaceProxyGaussianSplattingPointCloud>(this);
	}
}

#if WITH_EDITORONLY_DATA

#if UE_VERSION_NEWER_THAN(5, 4, 0)
void UNiagaraDataInterfaceGaussianSplattingPointCloud::GetFunctionsInternal(TArray<FNiagaraFunctionSignature>& OutFunctions) const
{
	Super::GetFunctionsInternal(OutFunctions);

#else
void UNiagaraDataInterfaceGaussianSplattingPointCloud::GetFunctions(TArray<FNiagaraFunctionSignature>& OutFunctions) 
{
	Super::GetFunctions(OutFunctions);
#endif
	{
		FNiagaraFunctionSignature GetPointDataSignature;
		GetPointDataSignature.Name = GetPointDataFunctionName;
		GetPointDataSignature.Inputs.Add(FNiagaraVariable(GetClass(), TEXT("GaussianSplattingPointCloud")));
		GetPointDataSignature.Inputs.Add(FNiagaraVariable(FNiagaraTypeDefinition::GetIntDef(), TEXT("Index")));
		GetPointDataSignature.Outputs.Add(FNiagaraVariable(FNiagaraTypeDefinition::GetVec3Def(), TEXT("Position")));
		GetPointDataSignature.Outputs.Add(FNiagaraVariable(FNiagaraTypeDefinition::GetVec4Def(), TEXT("Quat")));
		GetPointDataSignature.Outputs.Add(FNiagaraVariable(FNiagaraTypeDefinition::GetVec3Def(), TEXT("Scale")));
		GetPointDataSignature.Outputs.Add(FNiagaraVariable(FNiagaraTypeDefinition::GetColorDef(), TEXT("Color")));
		GetPointDataSignature.bMemberFunction = true;
		GetPointDataSignature.bRequiresContext = false;
		OutFunctions.Add(GetPointDataSignature);
	}
	{
		FNiagaraFunctionSignature GetPointCountSignature;
		GetPointCountSignature.Name = GetPointCountFunctionName;
		GetPointCountSignature.Inputs.Add(FNiagaraVariable(GetClass(), TEXT("GaussianSplattingPointCloud")));
		GetPointCountSignature.Outputs.Add(FNiagaraVariable(FNiagaraTypeDefinition::GetIntDef(), TEXT("PointCount")));
		GetPointCountSignature.bMemberFunction = true;
		GetPointCountSignature.bRequiresContext = false;
		OutFunctions.Add(GetPointCountSignature);
	}
}

#endif

DEFINE_NDI_DIRECT_FUNC_BINDER(UNiagaraDataInterfaceGaussianSplattingPointCloud, GetPointCount);
DEFINE_NDI_DIRECT_FUNC_BINDER(UNiagaraDataInterfaceGaussianSplattingPointCloud, GetPointData);

void UNiagaraDataInterfaceGaussianSplattingPointCloud::SetPointCloud(UGaussianSplattingPointCloud* InPointCloud)
{
	PointCloud = InPointCloud;
	if (auto DIProxy = GetProxyAs<FNiagaraDataInterfaceProxyGaussianSplattingPointCloud>()) {
		DIProxy->MakeBufferDirty();
	}
}

UGaussianSplattingPointCloud* UNiagaraDataInterfaceGaussianSplattingPointCloud::GetPointCloud() const
{
	return PointCloud;
}

void UNiagaraDataInterfaceGaussianSplattingPointCloud::GetPointCount(FVectorVMExternalFunctionContext& Context)
{
	VectorVM::FExternalFuncRegisterHandler<int32> OutPointCount(Context);

	for (int32 InstanceIdx = 0; InstanceIdx < Context.GetNumInstances(); ++InstanceIdx)
	{
		*OutPointCount.GetDestAndAdvance() = PointCloud->GetPoints().Num();
	}
}

void UNiagaraDataInterfaceGaussianSplattingPointCloud::GetPointData(FVectorVMExternalFunctionContext& Context)
{
	VectorVM::FExternalFuncInputHandler<int32> InIndex(Context);
	VectorVM::FExternalFuncRegisterHandler<float> PosX(Context);
	VectorVM::FExternalFuncRegisterHandler<float> PosY(Context);
	VectorVM::FExternalFuncRegisterHandler<float> PosZ(Context);

	VectorVM::FExternalFuncRegisterHandler<float> QuatX(Context);
	VectorVM::FExternalFuncRegisterHandler<float> QuatY(Context);
	VectorVM::FExternalFuncRegisterHandler<float> QuatZ(Context);
	VectorVM::FExternalFuncRegisterHandler<float> QuatW(Context);

	VectorVM::FExternalFuncRegisterHandler<float> ScaleX(Context);
	VectorVM::FExternalFuncRegisterHandler<float> ScaleY(Context);
	VectorVM::FExternalFuncRegisterHandler<float> ScaleZ(Context);

	VectorVM::FExternalFuncRegisterHandler<float> ColorR(Context);
	VectorVM::FExternalFuncRegisterHandler<float> ColorG(Context);
	VectorVM::FExternalFuncRegisterHandler<float> ColorB(Context);
	VectorVM::FExternalFuncRegisterHandler<float> ColorA(Context);

	auto Points = PointCloud->GetPoints();
	for (int32 InstanceIdx = 0; InstanceIdx < Context.GetNumInstances(); ++InstanceIdx){
		int32 Index = InIndex.Get();
		FGaussianSplattingPoint& Point = Points[Index];
		*PosX.GetDest() = Point.Position.X;
		*PosX.GetDest() = Point.Position.X;
		*PosX.GetDest() = Point.Position.X;

		*QuatX.GetDest() = Point.Quat.X;
		*QuatY.GetDest() = Point.Quat.Y;
		*QuatZ.GetDest() = Point.Quat.Z;
		*QuatZ.GetDest() = Point.Quat.Z;

		*ScaleX.GetDest() = Point.Scale.X;
		*ScaleY.GetDest() = Point.Scale.Y;
		*ScaleZ.GetDest() = Point.Scale.Z;

		*ColorR.GetDest() = Point.Color.R;
		*ColorG.GetDest() = Point.Color.G;
		*ColorB.GetDest() = Point.Color.B;
		*ColorA.GetDest() = Point.Color.A;

		InIndex.Advance();

		PosX.Advance();
		PosY.Advance();
		PosZ.Advance();

		QuatX.Advance();
		QuatY.Advance();
		QuatZ.Advance();
		QuatZ.Advance();

		ScaleX.Advance();
		ScaleY.Advance();
		ScaleZ.Advance();

		ColorR.Advance();
		ColorG.Advance();
		ColorB.Advance();
		ColorA.Advance();
	}
}

void UNiagaraDataInterfaceGaussianSplattingPointCloud::GetVMExternalFunction(const FVMExternalFunctionBindingInfo& BindingInfo, void* InstanceData, FVMExternalFunction& OutFunc)
{
	if (BindingInfo.Name == GetPointDataFunctionName){
		NDI_FUNC_BINDER(UNiagaraDataInterfaceGaussianSplattingPointCloud, GetPointData)::Bind(this, OutFunc);
	}
	else if (BindingInfo.Name == GetPointCountFunctionName){
		NDI_FUNC_BINDER(UNiagaraDataInterfaceGaussianSplattingPointCloud, GetPointCount)::Bind(this, OutFunc);
	}
	else{
		ensureMsgf(false, TEXT("Error! Function defined for this class but not bound."));
	}
}

#if WITH_EDITORONLY_DATA
bool UNiagaraDataInterfaceGaussianSplattingPointCloud::AppendCompileHash(FNiagaraCompileHashVisitor* InVisitor) const
{
	bool bSuccess = Super::AppendCompileHash(InVisitor);
	bSuccess &= InVisitor->UpdateShaderParameters<FShaderParameters>();
	return bSuccess;
}

bool UNiagaraDataInterfaceGaussianSplattingPointCloud::GetFunctionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, const FNiagaraDataInterfaceGeneratedFunction& FunctionInfo, int FunctionInstanceIndex, FString& OutHLSL)
{
	bool ParentRet = Super::GetFunctionHLSL(ParamInfo, FunctionInfo, FunctionInstanceIndex, OutHLSL);
	if (ParentRet)
	{
		return true;
	}
	else if (FunctionInfo.DefinitionName == GetPointDataFunctionName)
	{
		static const TCHAR* FormatBounds = TEXT(R"(
			void {FunctionName}(int In_PointIndex, out float3 Out_Position, out float4 Out_Quat, out float3 Out_Scale, out float4 Out_Color)
			{
				int PointIndex = In_PointIndex < {PointCount} ? In_PointIndex : {PointCount} - 1;
				Out_Position = {PointDataBuffer}.Load(PointIndex * 4 ).xyz;
				Out_Quat = {PointDataBuffer}.Load(PointIndex * 4 + 1);
				Out_Scale = {PointDataBuffer}.Load(PointIndex * 4 + 2).xyz;
				Out_Color = {PointDataBuffer}.Load(PointIndex * 4 + 3);
			}
		)");

		TMap<FString, FStringFormatArg> ArgsBounds = {
			{TEXT("FunctionName"), FStringFormatArg(FunctionInfo.InstanceName)},
			{TEXT("PointCount"), FStringFormatArg(ParamInfo.DataInterfaceHLSLSymbol + PointCountName)},
			{TEXT("PointDataBuffer"), FStringFormatArg(ParamInfo.DataInterfaceHLSLSymbol + PointDataBufferName)},
		};
		OutHLSL += FString::Format(FormatBounds, ArgsBounds);
		return true;
	}
	else if (FunctionInfo.DefinitionName == GetPointCountFunctionName)
	{
		static const TCHAR* FormatBounds = TEXT(R"(
			void {FunctionName}(out int Out_Val)
			{
				Out_Val = {PointCount};
			}
		)");
		TMap<FString, FStringFormatArg> ArgsBounds = {
			{TEXT("FunctionName"), FStringFormatArg(FunctionInfo.InstanceName)},
			{TEXT("PointCount"), FStringFormatArg(ParamInfo.DataInterfaceHLSLSymbol + PointCountName)},
		};
		OutHLSL += FString::Format(FormatBounds, ArgsBounds);
		return true;
	}
	else
	{
		return false;
	}
}

void UNiagaraDataInterfaceGaussianSplattingPointCloud::GetParameterDefinitionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, FString& OutHLSL)
{
	Super::GetParameterDefinitionHLSL(ParamInfo, OutHLSL);

	static const TCHAR* FormatDeclarations = TEXT(R"(		
		int {PointCountName};
		Buffer<float4> {PointDataBufferName};
	)");

	TMap<FString, FStringFormatArg> ArgsDeclarations = {
		{TEXT("PointCountName"), FStringFormatArg(ParamInfo.DataInterfaceHLSLSymbol + PointCountName)},
		{TEXT("PointDataBufferName"), FStringFormatArg(ParamInfo.DataInterfaceHLSLSymbol + PointDataBufferName)},
	};
	OutHLSL += FString::Format(FormatDeclarations, ArgsDeclarations);
}
#endif

void UNiagaraDataInterfaceGaussianSplattingPointCloud::BuildShaderParameters(FNiagaraShaderParametersBuilder& ShaderParametersBuilder) const
{
	ShaderParametersBuilder.AddNestedStruct<FShaderParameters>();
}

void UNiagaraDataInterfaceGaussianSplattingPointCloud::SetShaderParameters(const FNiagaraDataInterfaceSetShaderParametersContext& Context) const
{
	FNiagaraDataInterfaceProxyGaussianSplattingPointCloud& DIProxy = Context.GetProxy<FNiagaraDataInterfaceProxyGaussianSplattingPointCloud>();
	DIProxy.TryUpdateBuffer();
	UNiagaraDataInterfaceGaussianSplattingPointCloud* Current = DIProxy.Owner;
	FShaderParameters* ShaderParameters = Context.GetParameterNestedStruct<FShaderParameters>();
	ShaderParameters->PointCount = Current->PointCloud ? Current->PointCloud->GetPoints().Num() : 0;
	ShaderParameters->PointDataBuffer = FNiagaraRenderer::GetSrvOrDefaultFloat4(DIProxy.GaussianPointDataBuffer.SRV);
}

bool UNiagaraDataInterfaceGaussianSplattingPointCloud::Equals(const UNiagaraDataInterface* Other) const
{
	bool bIsEqual = Super::Equals(Other);
	const UNiagaraDataInterfaceGaussianSplattingPointCloud* OtherPointCloud = CastChecked<const UNiagaraDataInterfaceGaussianSplattingPointCloud>(Other);
	return OtherPointCloud->PointCloud == PointCloud;
}

#if WITH_EDITOR
void UNiagaraDataInterfaceGaussianSplattingPointCloud::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	static const FName PointCloudFName = GET_MEMBER_NAME_CHECKED(UNiagaraDataInterfaceGaussianSplattingPointCloud, PointCloud);

	if (!HasAnyFlags(RF_ClassDefaultObject)){
		if (PropertyChangedEvent.GetMemberPropertyName() == PointCloudFName) {
			GetProxyAs<FNiagaraDataInterfaceProxyGaussianSplattingPointCloud>()->MakeBufferDirty();
		}
	}
}
#endif //WITH_EDITOR

void UNiagaraDataInterfaceGaussianSplattingPointCloud::PostInitProperties()
{
	Super::PostInitProperties();

	if (HasAnyFlags(RF_ClassDefaultObject)){
		ENiagaraTypeRegistryFlags Flags = ENiagaraTypeRegistryFlags::AllowAnyVariable | ENiagaraTypeRegistryFlags::AllowParameter;
		FNiagaraTypeRegistry::Register(FNiagaraTypeDefinition(GetClass()), Flags);
	}
	else {
		GetProxyAs<FNiagaraDataInterfaceProxyGaussianSplattingPointCloud>()->MakeBufferDirty();
	}
}

void UNiagaraDataInterfaceGaussianSplattingPointCloud::PostLoad()
{
	Super::PostLoad();
}

bool UNiagaraDataInterfaceGaussianSplattingPointCloud::CopyToInternal(UNiagaraDataInterface* Destination) const
{
	if (!Super::CopyToInternal(Destination)){
		return false;
	}

	UNiagaraDataInterfaceGaussianSplattingPointCloud* CastedDestination = Cast<UNiagaraDataInterfaceGaussianSplattingPointCloud>(Destination);
	if (CastedDestination){
		CastedDestination->PointCloud = PointCloud;
	}
	return true;
}


// Global VM function names, also used by the shaders code generation methods.
const FName UNiagaraDataInterfaceGaussianSplattingPointCloud::GetPointDataFunctionName("GetPointData");
const FName UNiagaraDataInterfaceGaussianSplattingPointCloud::GetPointCountFunctionName("GetPointCount");

// Global variable prefixes, used in HLSL parameter declarations.
const FString UNiagaraDataInterfaceGaussianSplattingPointCloud::PointCountName(TEXT("_PointCount"));
const FString UNiagaraDataInterfaceGaussianSplattingPointCloud::PointDataBufferName(TEXT("_PointDataBuffer"));

#undef LOCTEXT_NAMESPACE
