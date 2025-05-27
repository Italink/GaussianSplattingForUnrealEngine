#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "NiagaraSystem.h"
#include "GaussianSplattingPointCloudDataInterface.h"
#include "GaussianSplattingEditorLibrary.generated.h"

USTRUCT(BlueprintType)
struct FGaussianSplattingPointCloudMetaInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gaussian Splatting")
	FVector Location = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gaussian Splatting")
	FVector BoxExtent = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gaussian Splatting")
	TSet<FString> SourceAssets;
};

USTRUCT(BlueprintType)
struct FGaussianSplattingPointCloudsImportSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Gaussian Splatting")
	TObjectPtr<UWorld> World;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gaussian Splatting")
	FString SearchDir;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gaussian Splatting")
	FString SaveContentDir;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gaussian Splatting")
	TSoftObjectPtr<UNiagaraSystem> TemplateSystem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gaussian Splatting")
	bool bUseStandaloneNiagraSystem = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gaussian Splatting")
	bool bRepartition = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition = bRepartition), Category = "Gaussian Splatting")
	FString PartitionBaseName = "Cell";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition = bRepartition), Category = "Gaussian Splatting")
	int32 CellSize = 25600;
};

UCLASS()
class GAUSSIANSPLATTINGEDITOR_API UGaussianSplattingEditorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Gaussian Splatting")
	static UGaussianSplattingPointCloud* LoadSplatPly(FString FileName, UObject* Outer, FName AssetName = NAME_None);

	UFUNCTION(BlueprintCallable, Category = "Gaussian Splatting")
	static UNiagaraSystem* CreateNiagaraSystemFromPointCloud(UGaussianSplattingPointCloud* PointCloud, UObject* Outer, FName AssetName = NAME_None, UNiagaraSystem* Template = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Gaussian Splatting")
	static void SetupPointCloudToNiagaraComponent(UGaussianSplattingPointCloud* PointCloud, UNiagaraComponent* NiagaraComponent, UNiagaraSystem* NiagaraSystem = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Gaussian Splatting")
	static UStaticMesh* CreateStaticMeshFromPointCloud(UGaussianSplattingPointCloud* PointCloud, UObject* Outer, FName AssetName = NAME_None);

	static UTexture2D* CreateFloat16TextureFromData(UObject* Outer, FString Name, uint32 Width, uint32 Height, TArray<FFloat16> Data);

	static void FakeEngineTick(UWorld* InWorld, float InDelta = 0.03f, int InCount = 1);

	static FLinearColor SRGBToLinear(const FLinearColor& Color);

	static FLinearColor LinearToSRGB(const FLinearColor& Color);

	static FVector2D GetTangledUV(int FrameXY, int Index);

	static FVector UVtoPyramid(FVector2D UV);

	static FVector UVtoOctahedron(FVector2D uv);

	UFUNCTION(BlueprintCallable, Category = "Gaussian Splatting")
	static void ImportPointClouds(
		UWorld* World,
		FString SearchDir,
		FString SaveContentDir,
		UNiagaraSystem* TemplateSystem = nullptr,
		bool bUseStandaloneNiagraSystem = false
	);

	UFUNCTION(BlueprintCallable, Category = "Gaussian Splatting")
	static void RepartitionPointClouds(
		UWorld* World,
		FString PartitionBaseName = "Cell",
		int32 CellSize = 51200,
		UNiagaraSystem* TemplateSystem = nullptr,
		bool bUseStandaloneNiagraSystem = false
	);
};
