#include "GaussianSplattingPointCloudActor.h"
#include "NiagaraFunctionLibrary.h"
#include "GaussianSplattingPointCloudDataInterface.h"

UGaussianSplattingPointCloud* AGaussianSplattingPointCloudActor::GetPointCloud() const
{
	UNiagaraComponent* NiagaraComp = GetNiagaraComponent();
	check(NiagaraComp);
	if (UNiagaraDataInterfaceGaussianSplattingPointCloud* DI = UNiagaraFunctionLibrary::GetDataInterface<UNiagaraDataInterfaceGaussianSplattingPointCloud>(NiagaraComp, "PointCloud")) {
		return DI->GetPointCloud();
	}
	return nullptr;
}
