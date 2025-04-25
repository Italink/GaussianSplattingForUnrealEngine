#pragma once

#include "NiagaraActor.h"
#include "GaussianSplattingPointCloud.h"
#include "GaussianSplattingPointCloudActor.generated.h"


UCLASS(CollapseCategories)
class GAUSSIANSPLATTINGRUNTIME_API AGaussianSplattingPointCloudActor : public ANiagaraActor {
	GENERATED_BODY()
public:
	UGaussianSplattingPointCloud* GetPointCloud() const;
};

