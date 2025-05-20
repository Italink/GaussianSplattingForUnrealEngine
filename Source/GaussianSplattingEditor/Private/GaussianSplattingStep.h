#pragma once

#include "Components/DirectionalLightComponent.h"
#include "Engine/SceneCapture2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "HAL/RunnableThread.h"
#include "Components/SceneCaptureComponent.h"
#include "Engine/TriggerSphere.h"
#include "NiagaraSystem.h"
#include "Engine/SkyLight.h"
#include "Engine/Scene.h"
#include "GaussianSplattingPointCloud.h"
#include "GaussianSplattingStep.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogGaussianSplatting, Log, All);

DECLARE_DELEGATE_RetVal(bool, FOnRequestTaskStart)

UENUM()
enum class EGaussianSplattingSourceMode : uint8
{
	Select,
	Locate,
	Custom,
};

UENUM()
enum class EGaussianSplattingCameraMode : uint8
{
	Hemisphere,
	Sphere,
};


UENUM()
enum class EGaussianSplattingOutputType: uint8
{
	Niagara,
	StaticMesh
};

UCLASS(EditInlineNew, CollapseCategories, config = GaussianSplattingEditor, defaultconfig, meta = (DisplayName = "Gaussian Splatting Editor"))
class UGaussianSplattingStepBase: public UObject {
	GENERATED_BODY()
public:
	virtual void Activate(){}

	virtual void Deactivate(){}

	void SetWorld(UWorld* InWorld) { World = InWorld; }

	virtual UWorld* GetWorld() const override { return World; }

	void SetWorkDir(FString InWorkDir){ WorkDir = InWorkDir; };

	void ExecuteCommand(FString ExecutePath, FString Command, bool bAsync = true, TFunction<void()> FinishedCallback = {});

	virtual void ReceiveMessage(const FString& Message);

	TObjectPtr<UWorld> World;

	FString WorkDir;

	TSharedPtr<FRunnable> Worker;

	TSharedPtr<FRunnableThread> WorkThread;

	float TaskProgressPercent = 0.0f;
	FText LastTaskStatusText = FText::FromString("");
	bool bRequestCancelTask = false;

	FOnRequestTaskStart OnRequestTaskStart;
	FSimpleMulticastDelegate OnTaskFinished;
};

UCLASS(EditInlineNew, CollapseCategories, config = GaussianSplattingEditor, defaultconfig, meta = (DisplayName = "Gaussian Splatting Editor"))
class UGaussianSplattingStep_Capture: public UGaussianSplattingStepBase {
	GENERATED_BODY()
public:
	void Activate() override;

	void Deactivate() override;

	UFUNCTION(CallInEditor, meta = (DisplayPriority = 1))
	void Capture();

	UFUNCTION(CallInEditor, meta = (DisplayPriority = 2))
	void PrevCamera();

	UFUNCTION(CallInEditor, meta = (DisplayPriority = 3))
	void NextCamera();

	void SetSelectionByComponents(const TArray<UActorComponent*>& InSourceComponents);

	void OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);

	void OnComponentTransformChanged(USceneComponent* Component, ETeleportType TeleportType);

	void UpdateCameraMatrix();

	void SetCurrentCameraIndex(int InIndex);

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
public:
	UPROPERTY(EditAnywhere, Config, Category = "Gaussian Splatting")
	EGaussianSplattingSourceMode SourceMode = EGaussianSplattingSourceMode::Select;

	UPROPERTY(EditAnywhere, Transient, meta = (EditCondition = "SourceMode == EGaussianSplattingSourceMode::Select", EditConditionHides), Category = "Gaussian Splatting")
	TArray<TObjectPtr<AActor>> SelectionActors;

	UPROPERTY(EditAnywhere, Config, meta = (EditCondition = "SourceMode != EGaussianSplattingSourceMode::Custom", EditConditionHides), Category = "Gaussian Splatting")
	EGaussianSplattingCameraMode CameraMode = EGaussianSplattingCameraMode::Hemisphere;

	UPROPERTY(EditAnywhere, Config, meta = (EditCondition = "SourceMode != EGaussianSplattingSourceMode::Custom", EditConditionHides), Category = "Gaussian Splatting")
	int FrameXY = 10;
	
	UPROPERTY(EditAnywhere, Config, meta = (UIMin = 0.01, ClampMin = 0.01, UIMax = 2), meta = (EditCondition = "SourceMode != EGaussianSplattingSourceMode::Custom", EditConditionHides), Category = "Gaussian Splatting")
	float CaptureDistanceScale = 0.6f;

	UPROPERTY(VisibleAnywhere, Transient, meta = (EditCondition = "SourceMode == EGaussianSplattingSourceMode::Locate", EditConditionHides), Category = "Gaussian Splatting")
	TObjectPtr<ATriggerSphere> LocateActor;

	UPROPERTY(EditAnywhere, Transient, meta = (EditCondition = "SourceMode != EGaussianSplattingSourceMode::Select", EditConditionHides), Category = "Gaussian Splatting")
	TArray<TObjectPtr<AActor>> HiddenActors;

	UPROPERTY(VisibleAnywhere, Transient, Category = "Gaussian Splatting")
	TObjectPtr<ASceneCapture2D> SceneCapture;

	UPROPERTY(VisibleAnywhere, Transient, Category = "Gaussian Splatting")
	TObjectPtr<UTextureRenderTarget2D> RenderTarget;

	UPROPERTY(EditAnywhere, Config, Category = "Gaussian Splatting")
	int RenderTargetResolution = 1024;

	UPROPERTY(EditAnywhere, Config, Category = "Gaussian Splatting")
	bool bCaptureFinalColor = false;

	UPROPERTY(EditAnywhere, Config, Category = "Gaussian Splatting")
	bool bCaptureDepth = true;

	UPROPERTY(EditAnywhere, Config, Category = "Gaussian Splatting")
	TArray<FEngineShowFlagsSetting> ShowFlagSettings;

	UPROPERTY(EditAnywhere, Config, Category = "Gaussian Splatting")
	struct FPostProcessSettings PostProcessSettings;

	UPROPERTY(EditAnywhere, Transient, meta = (EditCondition = "SourceMode == EGaussianSplattingSourceMode::Custom", EditConditionHides), Category = "Gaussian Splatting")
	TArray<AActor*> CameraActors;

	FBoxSphereBounds CurrentBounds;

	int CurrentCameraIndex = 0;
};

UCLASS(EditInlineNew, CollapseCategories, config = GaussianSplattingEditor, defaultconfig, meta = (DisplayName = "Gaussian Splatting Editor"))
class UGaussianSplattingStep_SparseReconstruction: public UGaussianSplattingStepBase {
	GENERATED_BODY()
public:
	void Activate() override;

	void Deactivate() override;

	UFUNCTION(CallInEditor, meta = (DisplayPriority = 1))
	void Reconstruction();

	UFUNCTION(CallInEditor, meta = (DisplayPriority = 2))
	void ColmapEdit();

	UFUNCTION(CallInEditor, meta = (DisplayPriority = 3))
	void ColmapView();

	void ReconstructionSparse(bool bAsync, TFunction<void()> FinishedCallback = {});

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	void UpdateParams();
public:
	UPROPERTY(VisibleAnywhere, Category = "Feature Extractor")
	FString FeatureExtractorParams;

	UPROPERTY(EditAnywhere, Config, Category = "Feature Extractor")
	int MaxNumFeaturtes = 8192;

	UPROPERTY(EditAnywhere, Config, Category = "Feature Extractor")
	FString FeatureExtractorParamsCustom;

	UPROPERTY(VisibleAnywhere, Category = "Exhaustive Matcher")
	FString ExhaustiveMatcherParams;

	UPROPERTY(EditAnywhere, Config, Category = "Exhaustive Matcher")
	FString ExhaustiveMatcherParamsCustom;

	UPROPERTY(VisibleAnywhere, Category = "Mapper")
	FString MapperParams;

	UPROPERTY(EditAnywhere, Config, Category = "Mapper")
	int AbsPoseMinNumInliers = 1;

	UPROPERTY(EditAnywhere, Config, Category = "Mapper")
	FString MapperParamsCustom;

	UPROPERTY(VisibleAnywhere, Category = "Model Aligner")
	FString ModelAlignerParams;

	UPROPERTY(EditAnywhere, Config, Category = "Model Aligner")
	FString ModelAlignerParamsCustom;
};

UCLASS(EditInlineNew, CollapseCategories, config = GaussianSplattingEditor, defaultconfig, meta = (DisplayName = "Gaussian Splatting Editor"))
class UGaussianSplattingStep_GaussianSplatting : public UGaussianSplattingStepBase {
	GENERATED_BODY()
public:
	void Activate() override;

	void Deactivate() override;

	UFUNCTION(CallInEditor, meta = (DisplayPriority = 1))
	void Train();

	void Train(bool bAsync, TFunction<void()> FinishedCallback = {});

	FString Clip(FString PlyPath);

	UFUNCTION(CallInEditor, meta = (DisplayPriority = 2))
	void Reload();

	UFUNCTION(CallInEditor, meta = (DisplayPriority = 3))
	void Export();

	UObject* LoadPly(UObject* Outer, FName AssetName);

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	void UpdateParams();
public:
	UPROPERTY(VisibleAnywhere, Transient, Category = "Output")
	TObjectPtr<UObject> Result;

	UPROPERTY()
	TObjectPtr<UPackage> LocalPackage;

	UPROPERTY(Config)
	FString LastSavePath;

	UPROPERTY(VisibleAnywhere, Category="Train")
	FString GaussianSplattingTrainParams;

	UPROPERTY(EditAnywhere, Config, Category = "Train", meta = (UIMin = 1, ClampMin = 1, UIMax = 8))
	int Resolution = 1;

	UPROPERTY(EditAnywhere, Config, Category = "Train", meta = (Tooltip = "Number of total iterations to train for."))
	int Iterations = 7000;

	UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = "Train", meta = (Tooltip = "Spherical harmonics features learning rate."))
	float Feature_LR = 0.0025f;

	UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = "Train", meta = (Tooltip = "Opacity learning rate."))
	float Opacity_LR = 0.05f;

	UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = "Train", meta = (Tooltip = "Scaling learning rate."))
	float Scaling_LR = 0.005f;

	UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = "Train", meta = (Tooltip = "Rotation learning rate."))
	float Rotation_LR = 0.001f;

	UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = "Train", meta = (Tooltip = "Number of steps (from 0) where position learning rate goes from to."))
	int Position_LR_MaxSteps = 30000;

	UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = "Train", meta = (Tooltip = "Initial 3D position learning rate."))
	float Position_LR_Init = 0.00016f;
	
	UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = "Train", meta = (Tooltip = "Final 3D position learning rate."))
	float Position_LR_Final = 0.0000016f;

	UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = "Train", meta = (Tooltip = "Position learning rate multiplier."))
	float Position_LR_DelayMult = 0.01f;

	UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = "Train", meta = (Tooltip = "Iteration where densification starts."))
	int DensifyFromIter = 500;

	UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = "Train", meta = (Tooltip = "Iteration where densification stops."))
	int DensifyUntilIter = 15000;
	
	UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = "Train", meta = (Tooltip = "Limit that decides if points should be densified based on 2D position gradient."))
	float DensifyGradThreshold = 0.0002f;

	UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = "Train", meta = (Tooltip = "How frequently to densify."))
	int DensificationInterval = 100;

	UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = "Train", meta = (Tooltip = "How frequently to reset opacity."))
	int OpacityResetInterval = 3000;

	UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = "Train", meta = (UIMin = 0, ClampMin = 0, UIMax = 1))
	float Depth_L1_WeightInit = 1.0f;

	UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = "Train", meta = (UIMin = 0, ClampMin = 0, UIMax = 1))
	float Depth_L1_WeightFinal = 0.01f;

	UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = "Train", meta = (UIMin = 0, ClampMin = 0, UIMax = 1, Tooltip = "Influence of SSIM on total loss from 0 to 1."))
	float LambdaDssim = 0.2f;

	UPROPERTY(EditAnywhere, Config, AdvancedDisplay, Category = "Train", meta = (UIMin = 0, ClampMin = 0, UIMax = 1, Tooltip = "Percentage of scene extent (0--1) a point must exceed to be forcibly densified"))
	float PercentDense = 0.01f;

	UPROPERTY(EditAnywhere, Config, Category = "Load")
	EGaussianSplattingCompressionMethod CompressionMethod = EGaussianSplattingCompressionMethod::Zlib;

	UPROPERTY(EditAnywhere, Config, Category = "Load")
	bool bClippingByMask = false;

	UPROPERTY(EditAnywhere, Config, meta = (EditCondition = "bClippingByMask", EditConditionHides, UIMin = 1, ClampMin = 0, UIMax = 20), Category = "Load")
	int MaskDilation = 5;

	UPROPERTY(EditAnywhere, Config, meta = (EditCondition = "bClippingByMask", EditConditionHides, UIMin = 1, ClampMin = 0.01, UIMax = 1), Category = "Load")
	float ClipThreshold = 0.8;

	UPROPERTY(EditAnywhere, Config, Category = "Load")
	float DistanceOfObservation = 0.0f;

	UPROPERTY(EditAnywhere, Config, Category = "Load")
	float MinScreenSizeOfObservation = 0.01f;

	FSimpleDelegate OnPlyLoadFinished;
};