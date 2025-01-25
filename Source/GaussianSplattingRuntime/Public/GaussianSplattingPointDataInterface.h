#pragma once

#include "NiagaraDataInterfaceArray.h"
#include "Misc/EngineVersionComparison.h"
#include "GaussianSplattingPointDataInterface.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "Gaussian Splatting Point"))
struct FGaussianSplattingPoint
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector3f Position;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FQuat4f Quat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector3f Scale;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLinearColor Color;

	FGaussianSplattingPoint(FVector3f InPos = FVector3f::ZeroVector, FQuat4f InQuat = FQuat4f::Identity, FVector3f InScale = {1,1,1}, FLinearColor InColor = FLinearColor::Black)
		: Position(InPos)
		, Quat(InQuat)
		, Scale(InScale)
		, Color(InColor)
	{}

	bool operator==(const FGaussianSplattingPoint& Other)const { return Position == Other.Position && Quat == Other.Quat && Scale == Other.Scale && Color == Other.Color; }
	bool operator!=(const FGaussianSplattingPoint& Other)const { return !(*this == Other); }
	bool operator<(const FGaussianSplattingPoint& Other)const { return Position.X < Other.Position.X; }

	friend FORCEINLINE uint32 GetTypeHash(const FGaussianSplattingPoint& ID)
	{
		return HashCombine(HashCombine(HashCombine(GetTypeHash(ID.Position), GetTypeHash(ID.Quat)), GetTypeHash(ID.Scale)), GetTypeHash(ID.Color));
	}
};

struct FNiagaraDataInterfaceProxyGaussianSplattingPoints : public FNiagaraDataInterfaceProxy
{
	FNiagaraDataInterfaceProxyGaussianSplattingPoints(class UNiagaraDataInterfaceGaussianSplattingPoints* InOwner);

	virtual ~FNiagaraDataInterfaceProxyGaussianSplattingPoints();

	void MakeBufferDirty();
	void TryUpdateBuffer();
	void PostDataToGPU();

	virtual int32 PerInstanceDataPassedToRenderThreadSize() const override{ return 0; }

	TObjectPtr<class UNiagaraDataInterfaceGaussianSplattingPoints> Owner = nullptr;
	bool bDirty = false;
	FReadBuffer GaussianPointDataBuffer;
	FCriticalSection BufferLock;
};

UCLASS(EditInlineNew, Category = "Array", meta = (DisplayName = "Gaussian Splatting Points", Experimental), Blueprintable, BlueprintType)
class GAUSSIANSPLATTINGRUNTIME_API UNiagaraDataInterfaceGaussianSplattingPoints: public UNiagaraDataInterface
{	
	GENERATED_UCLASS_BODY()

	BEGIN_SHADER_PARAMETER_STRUCT(FShaderParameters, )
		SHADER_PARAMETER(int,	PointCount)
		SHADER_PARAMETER_SRV(Buffer<float4>, PointDataBuffer)
	END_SHADER_PARAMETER_STRUCT()
public:
	static const FName GetPointDataFunctionName;
	static const FName GetPointCountFunctionName;

	static const FString PointCountName;
	static const FString PointDataBufferName;

	UPROPERTY(BlueprintReadWrite)
	TArray<FGaussianSplattingPoint> PointData;

	void GetPointCount(FVectorVMExternalFunctionContext& Context);

	void GetPointData(FVectorVMExternalFunctionContext& Context);

	virtual void GetVMExternalFunction(const FVMExternalFunctionBindingInfo& BindingInfo, void* InstanceData, FVMExternalFunction& OutFunc) override;

	virtual bool CanExecuteOnTarget(ENiagaraSimTarget Target) const override{ return true; }

#if WITH_EDITORONLY_DATA
	virtual bool AppendCompileHash(FNiagaraCompileHashVisitor* InVisitor) const override;
	virtual bool GetFunctionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, const FNiagaraDataInterfaceGeneratedFunction& FunctionInfo, int FunctionInstanceIndex, FString& OutHLSL) override;
	virtual void GetParameterDefinitionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, FString& OutHLSL) override;
#endif
	virtual void BuildShaderParameters(FNiagaraShaderParametersBuilder& ShaderParametersBuilder) const override;
	virtual void SetShaderParameters(const FNiagaraDataInterfaceSetShaderParametersContext& Context) const override;

	virtual bool Equals(const UNiagaraDataInterface* Other) const override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR

	virtual void PostInitProperties() override;
	virtual void PostLoad() override;

protected:
#if WITH_EDITORONLY_DATA

#if UE_VERSION_NEWER_THAN(5, 4, 0)
	virtual void GetFunctionsInternal(TArray<FNiagaraFunctionSignature>& OutFunctions) const override;
#else
	void GetFunctions(TArray<FNiagaraFunctionSignature>& OutFunctions) override;
#endif

#endif
	virtual bool CopyToInternal(UNiagaraDataInterface* Destination) const override;
};
