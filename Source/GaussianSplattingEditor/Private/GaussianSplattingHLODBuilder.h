#pragma once

#include "WorldPartition/HLOD/HLODBuilder.h"
#include "GaussianSplattingStep.h"
#include "GaussianSplattingHLODBuilder.generated.h"

UCLASS()
class UGaussianSplattingHLODBuilderSettings : public UHLODBuilderSettings
{
	GENERATED_UCLASS_BODY()

	uint32 GetCRC() const override;

public:
	UPROPERTY(VisibleAnywhere, Instanced, NoClear, meta = (EditInline), Category = "Gaussian Splatting")
	TObjectPtr<UGaussianSplattingStep_Capture> CaptureSettings;

	UPROPERTY(VisibleAnywhere, Instanced, NoClear, meta = (EditInline), Category = "Gaussian Splatting")
	TObjectPtr<UGaussianSplattingStep_SparseReconstruction> SparseReconstructionSettings;

	UPROPERTY(VisibleAnywhere, Instanced, NoClear, meta = (EditInline), Category = "Gaussian Splatting")
	TObjectPtr<UGaussianSplattingStep_GaussianSplatting> GaussianSplattingEditorSettings;
};

UCLASS()
class UGaussianSplattingHLODBuilder : public UHLODBuilder
{
	GENERATED_UCLASS_BODY()
public:
	virtual TSubclassOf<UHLODBuilderSettings> GetSettingsClass() const override;
	virtual TArray<UActorComponent*> Build(const FHLODBuildContext& InHLODBuildContext, const TArray<UActorComponent*>& InSourceComponents) const override;

};
