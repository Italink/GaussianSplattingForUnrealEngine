#pragma once

#include "NiagaraDataInterfaceArray.h"
#include "Misc/EngineVersionComparison.h"
#include "GaussianSplattingPointCloud.h"
#include "GaussianSplattingPointCloudDataInterface.generated.h"

struct FNiagaraDataInterfaceProxyGaussianSplattingPointCloud : public FNiagaraDataInterfaceProxy
{
	FNiagaraDataInterfaceProxyGaussianSplattingPointCloud(class UNiagaraDataInterfaceGaussianSplattingPointCloud* InOwner);

	virtual ~FNiagaraDataInterfaceProxyGaussianSplattingPointCloud();

	void MakeBufferDirty();
	void TryUpdateBuffer();
	void PostDataToGPU();

	virtual int32 PerInstanceDataPassedToRenderThreadSize() const override{ return 0; }

	TObjectPtr<class UNiagaraDataInterfaceGaussianSplattingPointCloud> Owner = nullptr;
	TObjectPtr<class UGaussianSplattingPointCloud> PointCloud;
	bool bDirty = false;
	FReadBuffer GaussianPointDataBuffer;
	FCriticalSection BufferLock;
};

UCLASS(EditInlineNew, Category = "Array", meta = (DisplayName = "Gaussian Splatting Point Cloud", Experimental), Blueprintable, BlueprintType)
class GAUSSIANSPLATTINGRUNTIME_API UNiagaraDataInterfaceGaussianSplattingPointCloud: public UNiagaraDataInterface
{	
	GENERATED_UCLASS_BODY()

	BEGIN_SHADER_PARAMETER_STRUCT(FShaderParameters, )
		SHADER_PARAMETER(int,	PointCount)
		SHADER_PARAMETER_SRV(Buffer<float4>, PointDataBuffer)
	END_SHADER_PARAMETER_STRUCT()
public:
	void SetPointCloud(UGaussianSplattingPointCloud* InPointCloud);
	UGaussianSplattingPointCloud* GetPointCloud() const;
	void GetPointCount(FVectorVMExternalFunctionContext& Context);
	void GetPointData(FVectorVMExternalFunctionContext& Context);

protected:
	friend struct FNiagaraDataInterfaceProxyGaussianSplattingPointCloud;

	static const FName GetPointDataFunctionName;
	static const FName GetPointCountFunctionName;

	static const FString PointCountName;
	static const FString PointDataBufferName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gaussian Splatting")
	TObjectPtr<UGaussianSplattingPointCloud> PointCloud;

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
