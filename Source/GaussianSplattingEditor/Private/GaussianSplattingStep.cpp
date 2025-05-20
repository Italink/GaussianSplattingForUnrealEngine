#include "GaussianSplattingStep.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneCaptureComponent2D.h"
#include "LevelEditor.h"
#include "Selection.h"
#include "ImageUtils.h"
#include "Interfaces/IPluginManager.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Framework/Notifications/NotificationManager.h"
#include "IContentBrowserSingleton.h"
#include "ContentBrowserModule.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Components/SphereComponent.h"
#include "Misc/EngineVersionComparison.h"
#include "GaussianSplattingEditorSettings.h"
#include "LevelEditorSubsystem.h"
#include "SLevelViewport.h"
#include "Components/SkyLightComponent.h"
#include "AssetCompilingManager.h"
#include "GaussianSplattingEditorLibrary.h"
#include "LandscapeComponent.h"
#include "LandscapeProxy.h"
#include <string>

DEFINE_LOG_CATEGORY(LogGaussianSplatting);

class FCommandExecuteRunnable final : public FRunnable
{
public:
	UGaussianSplattingStepBase* Step = nullptr;
	FString ExecutePath;
	FString Command;
	bool bShowNotification = true;
	TFunction<void()> FinishedCallback;
	FProcHandle ProcessHandle;
	FCommandExecuteRunnable(UGaussianSplattingStepBase* Step, FString ExecutePath, FString Command, TFunction<void()> FinishedCallback)
		: Step(Step)
		, ExecutePath(ExecutePath)
		, Command(Command) 
		, FinishedCallback(FinishedCallback)
		{
	}

	virtual uint32 Run() override {
		UE_LOG(LogGaussianSplatting, Warning, TEXT("Run Command: %s"), *Command);

		Step->bRequestCancelTask = false;
		int32 ReturnCode = -1;
		void* PipeStdOutRead = nullptr;
		void* PipeStdOutWrite = nullptr;
		verify(FPlatformProcess::CreatePipe(PipeStdOutRead, PipeStdOutWrite));

		void* PipeStdErrRead = nullptr;
		void* PipeStdErrWrite = nullptr;
		verify(FPlatformProcess::CreatePipe(PipeStdErrRead, PipeStdErrWrite));

		ProcessHandle = FPlatformProcess::CreateProc(*ExecutePath, *Command, true, true, true, nullptr, 0, nullptr, PipeStdOutWrite, PipeStdOutRead, PipeStdErrWrite);
		if (ProcessHandle.IsValid()) {
			FPlatformProcess::Sleep(0.01f);
			while (FPlatformProcess::IsProcRunning(ProcessHandle)) {
				TArray<uint8> BinaryData;
				FPlatformProcess::ReadPipeToArray(PipeStdOutRead, BinaryData);
				if (!BinaryData.IsEmpty()) {
					const std::string StdStr(reinterpret_cast<const char*>(BinaryData.GetData()), BinaryData.Num());
					Step->ReceiveMessage(FString(StdStr.c_str()));
				}
				if (Step->bRequestCancelTask) {
					FPlatformProcess::CloseProc(ProcessHandle);
					FPlatformProcess::ClosePipe(PipeStdOutRead, PipeStdOutWrite);
					FPlatformProcess::ClosePipe(PipeStdErrRead, PipeStdErrWrite);
					return 0;
				}
			}
			FPlatformProcess::GetProcReturnCode(ProcessHandle, &ReturnCode);
			if (ReturnCode != 0) {
				TArray<uint8> BinaryData;
				FPlatformProcess::ReadPipeToArray(PipeStdErrRead, BinaryData);
				if (!BinaryData.IsEmpty()) {
					const std::string StdStr(reinterpret_cast<const char*>(BinaryData.GetData()), BinaryData.Num());
					Step->ReceiveMessage(FString(StdStr.c_str()));
				}
			}
			else {
				TArray<uint8> BinaryData;
				FPlatformProcess::ReadPipeToArray(PipeStdOutRead, BinaryData);
				if (!BinaryData.IsEmpty()) {
					const std::string StdStr(reinterpret_cast<const char*>(BinaryData.GetData()), BinaryData.Num());
					Step->ReceiveMessage(FString(StdStr.c_str()));
				}
			}
			FPlatformProcess::CloseProc(ProcessHandle);
		}
		else {
			Step->ReceiveMessage(TEXT("Failed to launch command"));
		}
		FPlatformProcess::ClosePipe(PipeStdOutRead, PipeStdOutWrite);
		FPlatformProcess::ClosePipe(PipeStdErrRead, PipeStdErrWrite);
		ProcessHandle.Reset();
		return 0;
	}

	virtual void Stop() override {
		Step->WorkThread.Reset();
	}

	virtual void Exit() override {
		AsyncTask(ENamedThreads::GameThread, [this]() {
			if (FinishedCallback) {
				FinishedCallback();
			}
		});
	}
};

void UGaussianSplattingStepBase::ExecuteCommand(FString ExecutePath, FString Command, bool bAsync, TFunction<void()> FinishedCallback)
{
	Worker = MakeShared<FCommandExecuteRunnable>(this, ExecutePath, Command, FinishedCallback);
	if (bAsync) {
		WorkThread = TSharedPtr<FRunnableThread>(FRunnableThread::Create(Worker.Get(), TEXT("Gaussian Splatting")));
	}
	else {
		Worker->Run();
		if(FinishedCallback)
			FinishedCallback();
	}
}

void UGaussianSplattingStepBase::ReceiveMessage(const FString& Message)
{
	UE_LOG(LogGaussianSplatting, Log, TEXT("%s"), *Message);
	if (FSlateApplication::IsInitialized()) {
		TArray<FString> Lines;
		Message.ParseIntoArray(Lines, TEXT("\n"));
		LastTaskStatusText = FText::FromString(Lines.Last());
	}
}

void UGaussianSplattingStep_Capture::Activate()
{
	if (!RenderTarget) {
		RenderTarget = NewObject<UTextureRenderTarget2D>();
		RenderTarget->RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA16f;
		RenderTarget->InitAutoFormat(RenderTargetResolution, RenderTargetResolution);
		RenderTarget->UpdateResourceImmediate(true);
	}
	if (!SceneCapture) {
		TArray<AActor*> CaptureActors;
		UGameplayStatics::GetAllActorsOfClass(World, ASceneCapture2D::StaticClass(), CaptureActors);
		for (auto Actor : CaptureActors) {
			if (Actor->Tags.Contains("GaussianSplattingSceneCapture")) {
				SceneCapture = Cast<ASceneCapture2D>(Actor);
				break;
			}
		}
		if (!SceneCapture) {
			SceneCapture = World->SpawnActor<ASceneCapture2D>();
			SceneCapture->SetActorLabel(FString(TEXT("GaussianSplattingSceneCapture")));
			SceneCapture->SetFlags(RF_Transient);
			SceneCapture->Tags.Add("GaussianSplattingSceneCapture");
		}
		USceneCaptureComponent2D* SceneCaptureComp = SceneCapture->GetCaptureComponent2D();
		SceneCaptureComp->TextureTarget = RenderTarget;
		SceneCaptureComp->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
		SceneCaptureComp->CaptureSource = bCaptureFinalColor ? ESceneCaptureSource::SCS_FinalColorHDR : ESceneCaptureSource::SCS_SceneColorHDR;

		if (ShowFlagSettings.IsEmpty()) {
			ShowFlagSettings.Add(FEngineShowFlagsSetting{ TEXT("Atmosphere"), false });
			ShowFlagSettings.Add(FEngineShowFlagsSetting{ TEXT("Fog"), false });
			ShowFlagSettings.Add(FEngineShowFlagsSetting{ TEXT("Cloud"), false });
			ShowFlagSettings.Add(FEngineShowFlagsSetting{ TEXT("Decals"), false });
			ShowFlagSettings.Add(FEngineShowFlagsSetting{ TEXT("DepthOfField"), false });
			ShowFlagSettings.Add(FEngineShowFlagsSetting{ TEXT("VolumetricFog"), false });
			ShowFlagSettings.Add(FEngineShowFlagsSetting{ TEXT("AmbientCubemap"), false });
			ShowFlagSettings.Add(FEngineShowFlagsSetting{ TEXT("DynamicShadows"), true });
			ShowFlagSettings.Add(FEngineShowFlagsSetting{ TEXT("Lighting"), true });
			ShowFlagSettings.Add(FEngineShowFlagsSetting{ TEXT("AmbientOcclusion"), true });
			ShowFlagSettings.Add(FEngineShowFlagsSetting{ TEXT("PostProcessing"), true });
			ShowFlagSettings.Add(FEngineShowFlagsSetting{ TEXT("DistanceFieldAO"), false });
			ShowFlagSettings.Add(FEngineShowFlagsSetting{ TEXT("Translucency"), true });
		}
#if UE_VERSION_NEWER_THAN(5, 5, 0)
		SceneCaptureComp->SetShowFlagSettings(ShowFlagSettings);
#else
		SceneCaptureComp->ShowFlagSettings = ShowFlagSettings;
		FPropertyChangedEvent ChangedEvent(USceneCaptureComponent2D::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(USceneCaptureComponent2D, ShowFlagSettings)));
		SceneCaptureComp->PostEditChangeProperty(ChangedEvent);
#endif
		SceneCaptureComp->PostProcessSettings = PostProcessSettings;
		FPropertyChangedEvent PostChangedEvent(USceneCaptureComponent2D::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(USceneCaptureComponent2D, PostProcessSettings)));
		SceneCaptureComp->PostEditChangeProperty(ChangedEvent);
	}

	if (World->WorldType == EWorldType::Editor && FSlateApplication::IsInitialized()) {
		FLevelEditorModule& LevelEditor = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
		LevelEditor.OnActorSelectionChanged().AddUObject(this, &UGaussianSplattingStep_Capture::OnActorSelectionChanged);
		TArray<UObject*> Objects;
		GEditor->GetSelectedActors()->GetSelectedObjects(Objects);
		OnActorSelectionChanged(Objects, true);
		GEngine->OnComponentTransformChanged().AddUObject(this, &UGaussianSplattingStep_Capture::OnComponentTransformChanged);
	}
	UpdateCameraMatrix();
}

void UGaussianSplattingStep_Capture::Deactivate()
{
	if (SceneCapture) {
		SceneCapture->K2_DestroyActor();
		SceneCapture = nullptr;
	}
	if (LocateActor) {
		LocateActor->K2_DestroyActor();
		LocateActor = nullptr;
	}
	for (auto Actor : CameraActors) {
		Actor->Destroy();
	}
	CameraActors.Reset();
	FLevelEditorModule& LevelEditor = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditor.OnActorSelectionChanged().RemoveAll(this);
	GEngine->OnComponentTransformChanged().RemoveAll(this);
}

void UGaussianSplattingStep_Capture::Capture()
{
	if (OnRequestTaskStart.IsBound()) {
		if (!OnRequestTaskStart.Execute()) {
			return;
		}
	}

	float Radius = FMath::Max<FVector::FReal>(CurrentBounds.BoxExtent.Size(), 10.f);
	USceneCaptureComponent2D* SceneCaptureComp = SceneCapture->GetCaptureComponent2D();
	RenderTarget = SceneCaptureComp->TextureTarget;
	if (SourceMode == EGaussianSplattingSourceMode::Select) {
		TArray<ULandscapeComponent*> LandscapeComponents;
		for (auto Comp : SceneCaptureComp->ShowOnlyComponents) {
			if (auto LandscapeComp = Cast<ULandscapeComponent>(Comp)) {
				LandscapeComponents.Add(LandscapeComp);
			}
		}
		
		TArray<AActor*> ShowOnlyActors;
		UGameplayStatics::GetAllActorsOfClass(World, ASkyLight::StaticClass(), ShowOnlyActors);
		ShowOnlyActors.Append(SelectionActors);

		if (!LandscapeComponents.IsEmpty()) {
			TSet<ALandscapeProxy*> LandscapeProxies;
			Algo::Transform(LandscapeComponents, LandscapeProxies, [](ULandscapeComponent* SourceComponent) { return SourceComponent->GetLandscapeProxy(); });
			ShowOnlyActors.Append(LandscapeProxies.Array());
		}

		SceneCaptureComp->ShowOnlyActors = ShowOnlyActors;
	}

	bool bCaptureEveryFrameCache = SceneCaptureComp->bCaptureEveryFrame;
	SceneCaptureComp->bCaptureEveryFrame = false;
	SceneCaptureComp->bAlwaysPersistRenderingState = true;

	const double HalfFOVRadians = FMath::DegreesToRadians(SceneCaptureComp->FOVAngle / 2.0);
	const double DistanceFromSphere = Radius / FMath::Tan(HalfFOVRadians) * 2 * CaptureDistanceScale;
	const double FocalLength = RenderTarget->SizeX / (2 * FMath::Tan(HalfFOVRadians));
	const FString DatabaseImagesDir = WorkDir / "images";
	const FString DatabaseMasksDir = WorkDir / "masks";
	const FString DatabaseDepthsDir = WorkDir / "depths";
	const FString CameraPosFilePath = WorkDir / "cameras.txt";

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.DirectoryExists(*DatabaseImagesDir)){
		PlatformFile.DeleteDirectoryRecursively(*DatabaseImagesDir);
	}
	if (PlatformFile.DirectoryExists(*DatabaseMasksDir)) {
		PlatformFile.DeleteDirectoryRecursively(*DatabaseMasksDir);
	}
	if (PlatformFile.DirectoryExists(*DatabaseDepthsDir)) {
		PlatformFile.DeleteDirectoryRecursively(*DatabaseDepthsDir);
	}
	if (PlatformFile.DirectoryExists(*CameraPosFilePath)) {
		PlatformFile.DeleteDirectoryRecursively(*CameraPosFilePath);
	}

	UGaussianSplattingEditorLibrary::FakeEngineTick(World, 0.03f, 6);
	TaskProgressPercent = 0.0f;

	FString ImageRefPosFileContent = "";
	for (int i = 0; i < CameraActors.Num(); i++) {
		FString ImageFileName = FString::Printf(TEXT("image%04d.png"), i + 1);
		SceneCaptureComp->SetWorldTransform(CameraActors[i]->GetTransform());
		ETextureRenderTargetFormat RenderTargetFormat = RenderTarget->RenderTargetFormat;
		FTextureRenderTargetResource* RenderTargetResource = RenderTarget->GameThread_GetRenderTargetResource();
		FReadSurfaceDataFlags ReadPixelFlags(RCM_MinMax);
		FIntRect IntRegion(0, 0, RenderTarget->SizeX, RenderTarget->SizeY);
		if (bCaptureDepth) {
			UGaussianSplattingEditorLibrary::FakeEngineTick(World);
			SceneCaptureComp->CaptureSource = ESceneCaptureSource::SCS_SceneDepth;
			SceneCaptureComp->CaptureScene();
			TArray<FLinearColor> DepthColors;
			RenderTargetResource->ReadLinearColorPixels(DepthColors, ReadPixelFlags, IntRegion);
			FImageView DepthView(DepthColors.GetData(), RenderTarget->SizeX, RenderTarget->SizeY);
			float Min = FFloat16::MaxF16Float;
			float Max = 0;
			for (const auto& Color : DepthColors) {
				Min = FMath::Min(Min, Color.R);
				if (Color.R < FFloat16::MaxF16Float) {
					Max = FMath::Max(Max, Color.R);
				}
			}
			float SegmentationThreshold = 0.5;
			float SegmentationRange = 1 - SegmentationThreshold;
			for (auto& Color : DepthColors) {
				float Grayscale = 0.0f;
				if (Color.R < FFloat16::MaxF16Float)
					Grayscale = 1 - SegmentationRange * (Color.R - Min) / (Max - Min);
				Color.R = Grayscale;
			}
			FImage GrayScaleDepthImage;
			GrayScaleDepthImage.Init(DepthView.SizeX, DepthView.SizeY, ERawImageFormat::G16, EGammaSpace::Linear);
			FImageCore::CopyImage(DepthView, GrayScaleDepthImage);
			FImageUtils::SaveImageByExtension(*(DatabaseDepthsDir / ImageFileName), GrayScaleDepthImage);
		}
		TArray<FLinearColor> RawColors;
		TArray<FLinearColor> FinalColors;
		TArray<FLinearColor> MaskColors;

		UGaussianSplattingEditorLibrary::FakeEngineTick(World);
		SceneCaptureComp->CaptureSource = ESceneCaptureSource::SCS_SceneColorHDR;
		SceneCaptureComp->CaptureScene();
		RenderTargetResource->ReadLinearColorPixels(RawColors, ReadPixelFlags, IntRegion);
		if (bCaptureFinalColor) {
			UGaussianSplattingEditorLibrary::FakeEngineTick(World);
			SceneCaptureComp->CaptureSource = ESceneCaptureSource::SCS_FinalColorHDR;
			SceneCaptureComp->CaptureScene();
			RenderTargetResource->ReadLinearColorPixels(FinalColors, ReadPixelFlags, IntRegion);
		}
		else {
			FinalColors = RawColors;
		}
		MaskColors.SetNum(RawColors.Num());
		for (int j = 0; j < RawColors.Num(); j++) {
			const FLinearColor& RawColor = RawColors[j];
			FLinearColor& FinalColor = FinalColors[j];
			FinalColor = UGaussianSplattingEditorLibrary::LinearToSRGB(FinalColor);
			float Alpha = 1.0f - RawColor.A;
			float Mask = Alpha > 0.0f ? 1.0f : 0;
			MaskColors[j] = FLinearColor(Mask, Mask, Mask, 1.0f);
			FinalColor.A = Alpha;
		}

		ReceiveMessage(FString::Printf(TEXT("Capturing %s"), *ImageFileName));
		if (bRequestCancelTask) {
			bRequestCancelTask = false;
			break;
		}
		
		FImageView ImageView(FinalColors.GetData(), RenderTarget->SizeX, RenderTarget->SizeY);
		//FImageUtils::SaveImageByExtension(*(DatabaseImagesDir / ImageFileName), ImageView);
		FImageUtils::SaveImageByExtension(*(DatabaseImagesDir / FString::Printf(TEXT("image%04d.png"), i + 1)), ImageView);

		FImageView MaskView(MaskColors.GetData(), RenderTarget->SizeX, RenderTarget->SizeY);
		FImageUtils::SaveImageByExtension(*(DatabaseMasksDir / ImageFileName), MaskView);

		FVector ColmapPosition = (CameraActors[i]->GetActorLocation() - CurrentBounds.Origin) / 100.0;
		ImageRefPosFileContent += FString::Printf(TEXT("%s %lf %lf %lf\n"),
			*ImageFileName,
			ColmapPosition.X,
			-ColmapPosition.Z,
			-ColmapPosition.Y
		);

		TaskProgressPercent = i /(float) CameraActors.Num();

		UGaussianSplattingEditorLibrary::FakeEngineTick(World);
	}
	if (FFileHelper::SaveStringToFile(ImageRefPosFileContent, *CameraPosFilePath)) {
		UE_LOG(LogGaussianSplatting, Warning, TEXT("Successfully created and wrote to %s"), *CameraPosFilePath);
	}
	else {
		UE_LOG(LogGaussianSplatting, Error, TEXT("Failed to create or write to %s"), *CameraPosFilePath);
	}

	TaskProgressPercent = 0.0f;
	ReceiveMessage(TEXT("Capture Finished !"));

	SceneCaptureComp->bAlwaysPersistRenderingState = true;
	SceneCaptureComp->bCaptureEveryFrame = bCaptureEveryFrameCache;

	OnTaskFinished.Broadcast();
}

void UGaussianSplattingStep_Capture::PrevCamera()
{
	USceneCaptureComponent2D* SceneCaptureComp = SceneCapture->GetCaptureComponent2D();
	SetCurrentCameraIndex(CurrentCameraIndex - 1);
	SceneCaptureComp->SetWorldTransform(CameraActors[CurrentCameraIndex]->GetActorTransform());
}

void UGaussianSplattingStep_Capture::NextCamera()
{
	USceneCaptureComponent2D* SceneCaptureComp = SceneCapture->GetCaptureComponent2D();
	SetCurrentCameraIndex(CurrentCameraIndex + 1);
	SceneCaptureComp->SetWorldTransform(CameraActors[CurrentCameraIndex]->GetActorTransform());
}

void UGaussianSplattingStep_Capture::SetSelectionByComponents(const TArray<UActorComponent*>& InSourceComponents)
{
	if (!SceneCapture || SourceMode != EGaussianSplattingSourceMode::Select)
		return;
	USceneCaptureComponent2D* SceneCaptureComp = SceneCapture->GetCaptureComponent2D();
	FBoxSphereBounds Bounds;
	Bounds.SphereRadius = 0;
	TArray<TWeakObjectPtr<UPrimitiveComponent>> SelectionComponents;
	for (const auto& SourceComponent : InSourceComponents) {
		if (auto PrimitiveComponent = Cast<UPrimitiveComponent>(SourceComponent)) {
			if (Bounds.SphereRadius <= 0) {
				Bounds = PrimitiveComponent->Bounds;
			}
			else {
				Bounds = Bounds + PrimitiveComponent->Bounds;
			}
			SelectionComponents.Add(PrimitiveComponent);
		}
	}
	if (Bounds.SphereRadius == 0)
		return;
	CurrentBounds = Bounds;
	SceneCaptureComp->ShowOnlyComponents = SelectionComponents;
	float Radius = FMath::Max<FVector::FReal>(CurrentBounds.BoxExtent.Size(), 10.f);
	const float HalfFOVRadians = FMath::DegreesToRadians(SceneCaptureComp->FOVAngle / 2.0f);
	CurrentBounds.SphereRadius = Radius / FMath::Tan(HalfFOVRadians) * 2;
	UpdateCameraMatrix();
}

void UGaussianSplattingStep_Capture::OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh)
{
	if (!SceneCapture)
		return;
	USceneCaptureComponent2D* SceneCaptureComp = SceneCapture->GetCaptureComponent2D();
	TArray<TObjectPtr<AActor>> NewActors;
	for (auto Item : NewSelection) {
		AActor* Actor = Cast<AActor>(Item);
		if (Actor == nullptr || Actor->HasAnyFlags(RF_Transient))
			continue;
		bool bHasPrimitive = false;
		for (auto Comp : Actor->GetComponents()) {
			if (Cast<UPrimitiveComponent>(Comp)) {
				bHasPrimitive = true;
			}
		}
		if (bHasPrimitive) {
			NewActors.AddUnique(Actor);
		}
	}
	FBoxSphereBounds Bounds;
	Bounds.SphereRadius = 0;
	for (const auto& Actor : NewActors) {
		if (Actor->Tags.Contains("GaussianSplattingCaptureCamera") || Actor == SceneCapture)
			continue;
		for (auto Comp : Actor->GetComponents()) {
			if (auto PrimitiveComponent = Cast<UPrimitiveComponent>(Comp)) {
				if (Bounds.SphereRadius <= 0) {
					Bounds = PrimitiveComponent->Bounds;
				}
				else {
					Bounds = Bounds + PrimitiveComponent->Bounds;
				}
			}
		}
	}
	if (NewSelection.Num() == 1) {
		AActor* Actor = Cast<AActor>(NewSelection[0]);
		if (Actor && Actor->Tags.Contains("GaussianSplattingCaptureCamera")) {
			CurrentCameraIndex = CameraActors.IndexOfByKey(Actor);
			SceneCaptureComp->SetWorldTransform(CameraActors[FMath::Clamp(CurrentCameraIndex, 0, CameraActors.Num() - 1)]->GetActorTransform());
		}
	}
	if (Bounds.SphereRadius == 0 || SourceMode != EGaussianSplattingSourceMode::Select)
		return;
	CurrentBounds = Bounds;
	SelectionActors = NewActors;
	float Radius = FMath::Max<FVector::FReal>(CurrentBounds.BoxExtent.Size(), 10.f);
	const float HalfFOVRadians = FMath::DegreesToRadians(SceneCaptureComp->FOVAngle / 2.0f);
	CurrentBounds.SphereRadius = Radius / FMath::Tan(HalfFOVRadians) * 2;
	TArray<AActor*> ShowOnlyActors;
	UGameplayStatics::GetAllActorsOfClass(World, ASkyLight::StaticClass(), ShowOnlyActors);
	ShowOnlyActors.Append(SelectionActors);
	SceneCaptureComp->ShowOnlyActors = ShowOnlyActors;

	UpdateCameraMatrix();
}

void UGaussianSplattingStep_Capture::OnComponentTransformChanged(USceneComponent* Component, ETeleportType TeleportType)
{
	if (Component) {
		if (Component->GetOwner() == LocateActor && LocateActor) {
			FBoxSphereBounds Bound;
			Bound.Origin = LocateActor->GetActorLocation();
			USphereComponent* SphereComponent = CastChecked<USphereComponent>(LocateActor->GetRootComponent());
			Bound.SphereRadius = SphereComponent->GetScaledSphereRadius();
			Bound.BoxExtent = FVector(Bound.SphereRadius / FMath::Sqrt(3.0f) );
			CurrentBounds = Bound;
			UpdateCameraMatrix();
		}
		else if ( SelectionActors.Contains(Component->GetOwner())) {
			UpdateCameraMatrix();
		}
	}
}

void UGaussianSplattingStep_Capture::UpdateCameraMatrix()
{
	if(SceneCapture == nullptr || !SceneCapture->IsValidLowLevel())
		return;
	UStaticMesh* CameraMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/EditorMeshes/MatineeCam_SM.MatineeCam_SM"));
	USceneCaptureComponent2D* SceneCaptureComp = SceneCapture->GetCaptureComponent2D();

	if (SourceMode == EGaussianSplattingSourceMode::Locate && !LocateActor) {
		LocateActor = World->SpawnActor<ATriggerSphere>();
		LocateActor->SetFlags(EObjectFlags::RF_Transient);
		LocateActor->SetActorLabel("GaussianSplattingCaptureLocateActor");
		USphereComponent* SphereComponent = CastChecked<USphereComponent>(LocateActor->GetRootComponent());
		SphereComponent->SetSphereRadius(10000);
		FBoxSphereBounds Bound;
		Bound.Origin = LocateActor->GetActorLocation();
		Bound.SphereRadius = SphereComponent->GetScaledSphereRadius();
		Bound.BoxExtent = FVector(Bound.SphereRadius / FMath::Sqrt(3.0f));
		CurrentBounds = Bound;
		if (World->WorldType == EWorldType::Editor && FSlateApplication::IsInitialized()) {
			GEditor->GetSelectedActors()->Modify();
			GEditor->GetSelectedActors()->BeginBatchSelectOperation();
			GEditor->SelectNone(false, true, true);
			GEditor->SelectActor(LocateActor, true, false, true);
			GEditor->MoveViewportCamerasToActor({ LocateActor }, true);
			GEditor->GetSelectedActors()->EndBatchSelectOperation(false);
			GEditor->NoteSelectionChange();
		}
		SceneCaptureComp->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
	}
	else if (SourceMode == EGaussianSplattingSourceMode::Select && LocateActor) {
		LocateActor->Destroy();
		LocateActor = nullptr;
	}
	if (SourceMode == EGaussianSplattingSourceMode::Custom) {
		for (int i = 0; i < CameraActors.Num(); i++) {
			if (CameraActors[i] == nullptr) {
				AStaticMeshActor* MeshActor = World->SpawnActor<AStaticMeshActor>();
				MeshActor->SetMobility(EComponentMobility::Movable);
				MeshActor->AttachToActor(SceneCapture, FAttachmentTransformRules::KeepWorldTransform);
				MeshActor->SetFlags(EObjectFlags::RF_Transient);
				MeshActor->Tags.Add("GaussianSplattingCaptureCamera");
				MeshActor->GetStaticMeshComponent()->SetStaticMesh(CameraMesh);
				CameraActors[i] = MeshActor;
				SetCurrentCameraIndex(i);
			}
		}
	}
	else {
		int DesiredCount = FrameXY * FrameXY;
		if (CameraActors.Num() < DesiredCount) {
			for (int i = CameraActors.Num(); i < DesiredCount; i++) {
				AStaticMeshActor* MeshActor = World->SpawnActor<AStaticMeshActor>();
				MeshActor->SetMobility(EComponentMobility::Movable);
				MeshActor->AttachToActor(SceneCapture, FAttachmentTransformRules::KeepWorldTransform);
				MeshActor->SetFlags(EObjectFlags::RF_Transient);
				MeshActor->Tags.Add("GaussianSplattingCaptureCamera");
				MeshActor->GetStaticMeshComponent()->SetStaticMesh(CameraMesh);
				CameraActors.Add(MeshActor);
			}
		}
		else if (CameraActors.Num() > DesiredCount) {
			for (int i = DesiredCount; i < CameraActors.Num(); i++) {
				CameraActors[i]->Destroy();
			}
			CameraActors.SetNum(DesiredCount);
		}

		FVector Location = CurrentBounds.Origin;
		float DistanceFromSphere = CurrentBounds.SphereRadius * CaptureDistanceScale;

		for (int i = 0; i < FrameXY; i++) {
			for (int j = 0; j < FrameXY; j++) {
				int CameraIndex = i * FrameXY + j;
				AActor* CameraMeshActor = CameraActors[CameraIndex];
				FVector Direction;
				if (CameraMode == EGaussianSplattingCameraMode::Hemisphere) {
					Direction = UGaussianSplattingEditorLibrary::UVtoPyramid(FVector2D(i / (double)(FrameXY - 1), j / (double)(FrameXY - 1)));
					Direction.Normalize();
				}
				else {
					Direction = UGaussianSplattingEditorLibrary::UVtoOctahedron(FVector2D(i / (double)(FrameXY - 1), j / (double)(FrameXY - 1)));
					Direction.Normalize();
				}
				FVector Position = Location + Direction * DistanceFromSphere;
				FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(Position, Location);
				CameraMeshActor->SetActorLocationAndRotation(Position, Rotator);
				CameraMeshActor->SetActorLabel(FString::Printf(TEXT("GaussianSplattingCamera%d[%d_%d]"), CameraIndex + 1, i, j));
			}
		}
	}
	if (!CameraActors.IsEmpty()) {
		SceneCaptureComp->SetWorldTransform(CameraActors[FMath::Clamp(CurrentCameraIndex, 0, CameraActors.Num() - 1)]->GetActorTransform());
	}
	if (SourceMode == EGaussianSplattingSourceMode::Locate || SourceMode == EGaussianSplattingSourceMode::Custom) {
		SceneCaptureComp->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_LegacySceneCapture;
		TArray<AActor*> Actors = HiddenActors;
		Actors.Append(CameraActors);
		SceneCaptureComp->ShowOnlyActors.Reset();
		SceneCaptureComp->HiddenActors = Actors;
	}
	else if (SourceMode == EGaussianSplattingSourceMode::Select) {
		SceneCaptureComp->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
	}
}

void UGaussianSplattingStep_Capture::SetCurrentCameraIndex(int InIndex)
{
	CurrentCameraIndex = InIndex;
	if (CurrentCameraIndex < 0) {
		CurrentCameraIndex = CameraActors.Num() - 1;
	}
	else if (CurrentCameraIndex >= CameraActors.Num() && !CameraActors.IsEmpty()) {
		CurrentCameraIndex = (CurrentCameraIndex + 1) % CameraActors.Num();
	}
	if (CurrentCameraIndex >= 0 && CurrentCameraIndex < CameraActors.Num()) {
		GEditor->GetSelectedActors()->Modify();
		GEditor->GetSelectedActors()->BeginBatchSelectOperation();
		GEditor->SelectNone(false, true, true);
		GEditor->SelectActor(CameraActors[CurrentCameraIndex], true, false, true);
		GEditor->GetSelectedActors()->EndBatchSelectOperation(/*bNotify*/false);
		GEditor->NoteSelectionChange();
	}
}

void UGaussianSplattingStep_Capture::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	const FName PropertyName = PropertyChangedEvent.GetMemberPropertyName();

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UGaussianSplattingStep_Capture, FrameXY)
		|| PropertyName == GET_MEMBER_NAME_CHECKED(UGaussianSplattingStep_Capture, SourceMode)
		|| PropertyName == GET_MEMBER_NAME_CHECKED(UGaussianSplattingStep_Capture, CaptureDistanceScale)
		|| PropertyName == GET_MEMBER_NAME_CHECKED(UGaussianSplattingStep_Capture, CameraMode)
		|| PropertyName == GET_MEMBER_NAME_CHECKED(UGaussianSplattingStep_Capture, HiddenActors)
		) {
		UpdateCameraMatrix();
	}
	else if (SceneCapture && PropertyName == GET_MEMBER_NAME_CHECKED(UGaussianSplattingStep_Capture, ShowFlagSettings)
		) {
		USceneCaptureComponent2D* SceneCaptureComp = SceneCapture->GetCaptureComponent2D();
#if UE_VERSION_NEWER_THAN(5, 5, 0)
		SceneCaptureComp->SetShowFlagSettings(ShowFlagSettings);
#else
		SceneCaptureComp->ShowFlagSettings = ShowFlagSettings;
		FPropertyChangedEvent ChangedEvent(USceneCaptureComponent2D::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(USceneCaptureComponent2D, ShowFlagSettings)));
		SceneCaptureComp->PostEditChangeProperty(ChangedEvent);
#endif
	}
	else if (SceneCapture && (PropertyName == GET_MEMBER_NAME_CHECKED(UGaussianSplattingStep_Capture, PostProcessSettings) || PropertyName == GET_MEMBER_NAME_CHECKED(UGaussianSplattingStep_Capture, bCaptureFinalColor))) {
		USceneCaptureComponent2D* SceneCaptureComp = SceneCapture->GetCaptureComponent2D();
		SceneCaptureComp->PostProcessSettings = PostProcessSettings;
		SceneCaptureComp->CaptureSource = bCaptureFinalColor ? ESceneCaptureSource::SCS_FinalColorHDR : ESceneCaptureSource::SCS_SceneColorHDR;
		FPropertyChangedEvent ChangedEvent(USceneCaptureComponent2D::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(USceneCaptureComponent2D, PostProcessSettings)));
		SceneCaptureComp->PostEditChangeProperty(ChangedEvent);
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(UGaussianSplattingStep_Capture, CameraActors)) {
		if (SourceMode == EGaussianSplattingSourceMode::Custom) {
			if (PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayAdd) {
				for (int i = 0; i < CameraActors.Num(); i++) {
					if (CameraActors[i] == nullptr) {
						AStaticMeshActor* MeshActor = World->SpawnActor<AStaticMeshActor>();
						MeshActor->SetMobility(EComponentMobility::Movable);
						MeshActor->AttachToActor(SceneCapture, FAttachmentTransformRules::KeepWorldTransform);
						MeshActor->SetFlags(EObjectFlags::RF_Transient);
						MeshActor->Tags.Add("GaussianSplattingCaptureCamera");
						MeshActor->SetActorLabel(FString(TEXT("GaussianSplattingCameraCustom")));
						MeshActor->GetStaticMeshComponent()->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/EditorMeshes/MatineeCam_SM.MatineeCam_SM")));
						CameraActors[i] = MeshActor;
						SetCurrentCameraIndex(i);

						FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
						TSharedPtr<ILevelEditor> LevelEditor = LevelEditorModule.GetFirstLevelEditor();
						if (LevelEditor) {
							TSharedPtr<SLevelViewport> ActiveLevelViewport = LevelEditor->GetActiveViewportInterface();
							TSharedPtr<FEditorViewportClient> Client = ActiveLevelViewport->GetViewportClient();
							FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
								Client->Viewport,
								Client->GetScene(),
								Client->EngineShowFlags));
							// SceneView is deleted with the ViewFamily
							FSceneView* SceneView = Client->CalcSceneView(&ViewFamily);
							MeshActor->SetActorLocationAndRotation(SceneView->ViewLocation, SceneView->ViewRotation);
						}

						//ULevelEditorSubsystem* LevelEditorSubsystem = GEditor->GetEditorSubsystem<ULevelEditorSubsystem>();
						//if (LevelEditorSubsystem) {
						//	LevelEditorSubsystem->PilotLevelActor(MeshActor);
						//	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
						//	TSharedPtr<ILevelEditor> LevelEditor = LevelEditorModule.GetFirstLevelEditor();
						//	if (LevelEditor) {
						//		TSharedPtr<SLevelViewport> ActiveLevelViewport = LevelEditor->GetActiveViewportInterface();
						//		if (ActiveLevelViewport && !ActiveLevelViewport->IsLockedCameraViewEnabled()) {
						//			ActiveLevelViewport->ToggleActorPilotCameraView();
						//		}
						//	}
						//}
					}
				}
			}
			else if (PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayClear || PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayRemove) {
				TArray<AActor*> Actors;
				UGameplayStatics::GetAllActorsOfClassWithTag(World, AStaticMeshActor::StaticClass(), "GaussianSplattingCaptureCamera", Actors);
				for (auto Actor : Actors) {
					if (!CameraActors.Contains(Actor)) {
						Actor->Destroy();
					}
				}
			}
		}
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(UGaussianSplattingStep_Capture, RenderTargetResolution)) {
		if (RenderTarget) {
			RenderTarget->ResizeTarget(RenderTargetResolution, RenderTargetResolution);
		}
	}
}

void UGaussianSplattingStep_SparseReconstruction::Activate()
{
	UpdateParams();
}

void UGaussianSplattingStep_SparseReconstruction::Deactivate()
{

}

void UGaussianSplattingStep_SparseReconstruction::Reconstruction()
{
	if (OnRequestTaskStart.IsBound()) {
		if (!OnRequestTaskStart.Execute()) {
			return;
		}
	}
	TaskProgressPercent = 0.5f;
	ReconstructionSparse(true, [this]() {
		TaskProgressPercent = 1.0f;
		OnTaskFinished.Broadcast();
	});
}

void UGaussianSplattingStep_SparseReconstruction::ColmapEdit()
{
	FString Command = FString::Printf(TEXT("%s %s --colmap %s --edit")
		, *GetDefault<UGaussianSplattingEditorSettings>()->GetGaussianSplattingHelperPath()
		, *WorkDir
		, *GetDefault<UGaussianSplattingEditorSettings>()->GetColmapExecutablePath()
	);
	
	ExecuteCommand(GetDefault<UGaussianSplattingEditorSettings>()->GetPythonExecutablePath(), Command, true);
}

void UGaussianSplattingStep_SparseReconstruction::ColmapView()
{
	FString Command = FString::Printf(TEXT("%s %s --colmap %s --view")
		, *GetDefault<UGaussianSplattingEditorSettings>()->GetGaussianSplattingHelperPath()
		, *WorkDir
		, *GetDefault<UGaussianSplattingEditorSettings>()->GetColmapExecutablePath()
	);
	ExecuteCommand(GetDefault<UGaussianSplattingEditorSettings>()->GetPythonExecutablePath(), Command, true);
}

void UGaussianSplattingStep_SparseReconstruction::ReconstructionSparse(bool bAsync, TFunction<void()> FinishedCallback /*= {}*/)
{
	UpdateParams();
	FString Command = FString::Printf(TEXT("%s %s --colmap %s --sparse --extractor=\"%s\" --matcher=\"%s\" --mapper=\"%s\" --aligner=\"%s\" ")
			, *GetDefault<UGaussianSplattingEditorSettings>()->GetGaussianSplattingHelperPath()
			, *WorkDir
			, *GetDefault<UGaussianSplattingEditorSettings>()->GetColmapExecutablePath()
			, *FeatureExtractorParams
			, *ExhaustiveMatcherParams
			, *MapperParams
			, *ModelAlignerParams
		);
	ExecuteCommand(GetDefault<UGaussianSplattingEditorSettings>()->GetPythonExecutablePath(), Command, bAsync, FinishedCallback);
}

void UGaussianSplattingStep_SparseReconstruction::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	const FName PropertyName = PropertyChangedEvent.GetMemberPropertyName();
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UGaussianSplattingStep_SparseReconstruction, MaxNumFeaturtes)
		|| PropertyName.ToString().EndsWith("Custom")
		) {
		UpdateParams();
	}
}

void UGaussianSplattingStep_SparseReconstruction::UpdateParams()
{
	FeatureExtractorParams = FString::Printf(TEXT("%s --SiftExtraction.max_num_features %d")
		, *FeatureExtractorParamsCustom
		, MaxNumFeaturtes
	);

	ExhaustiveMatcherParams = FString::Printf(TEXT("%s")
		, *ExhaustiveMatcherParamsCustom
	);

	MapperParams = FString::Printf(TEXT("%s --Mapper.abs_pose_min_num_inliers %d")
		, *MapperParamsCustom
		, AbsPoseMinNumInliers
	);

	ModelAlignerParams = FString::Printf(TEXT("%s"),
		*ModelAlignerParamsCustom
	);
}

void UGaussianSplattingStep_GaussianSplatting::Activate()
{
	UpdateParams();
}

void UGaussianSplattingStep_GaussianSplatting::Deactivate()
{

}

void UGaussianSplattingStep_GaussianSplatting::Train()
{
	if (OnRequestTaskStart.IsBound()) {
		if (!OnRequestTaskStart.Execute()) {
			return;
		}
	}
	TaskProgressPercent = 0.3f;
	Train(true, [this]() {
		TaskProgressPercent = 0.7f;
		Reload();
		TaskProgressPercent = 1.0f;
		OnTaskFinished.Broadcast();
	});
}

void UGaussianSplattingStep_GaussianSplatting::Train(bool bAsync, TFunction<void()> FinishedCallback /*= {}*/)
{
	UpdateParams();
	
	FString Command = FString::Printf(TEXT("%s %s --gaussian %s --train=\"%s\" ")
			, *GetDefault<UGaussianSplattingEditorSettings>()->GetGaussianSplattingHelperPath()
			, *WorkDir
			, *GetDefault<UGaussianSplattingEditorSettings>()->GetGaussianSplattingRepoDir()
			, *GaussianSplattingTrainParams
		);

	ExecuteCommand(GetDefault<UGaussianSplattingEditorSettings>()->GetPythonExecutablePath(), Command, bAsync, FinishedCallback);
}

FString UGaussianSplattingStep_GaussianSplatting::Clip(FString PlyPath)
{
	FString Command = FString::Printf(TEXT("%s %s --clip --ply \"%s\" --mask_dilation %d --clip_threshold %f")
		, *GetDefault<UGaussianSplattingEditorSettings>()->GetGaussianSplattingHelperPath()
		, *WorkDir
		, *PlyPath
		, MaskDilation
		, ClipThreshold
	);
	ExecuteCommand(GetDefault<UGaussianSplattingEditorSettings>()->GetPythonExecutablePath(), Command, false);

	FString Directory;
	FString Filename;
	FString Extension;
	FPaths::Split(PlyPath, Directory, Filename, Extension);
	return FPaths::Combine(Directory, Filename + "_clipped." + Extension);
}

void UGaussianSplattingStep_GaussianSplatting::Reload()
{
	if (!LocalPackage) {
		LocalPackage = CreatePackage(TEXT("/GaussianSplattingForUnrealEngine/GaussianSplattingEditor"));
	}
	Result = LoadPly(LocalPackage, NAME_None);
	OnPlyLoadFinished.ExecuteIfBound();
}

void UGaussianSplattingStep_GaussianSplatting::Export()
{
	FSaveAssetDialogConfig SaveAssetDialogConfig;
	SaveAssetDialogConfig.DefaultPath = LastSavePath;
	SaveAssetDialogConfig.DefaultAssetName = "PointCloud";
	SaveAssetDialogConfig.AssetClassNames.Add(UGaussianSplattingStep_GaussianSplatting::StaticClass()->GetClassPathName());
	SaveAssetDialogConfig.ExistingAssetPolicy = ESaveAssetDialogExistingAssetPolicy::AllowButWarn;
	SaveAssetDialogConfig.DialogTitleOverride = FText::FromString("Save As");

	const FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	const FString SaveObjectPath = ContentBrowserModule.Get().CreateModalSaveAssetDialog(SaveAssetDialogConfig);
	if (SaveObjectPath.IsEmpty())
	{
		FNotificationInfo NotifyInfo(FText::FromString("Path is empty"));
		NotifyInfo.ExpireDuration = 5.0f;
		FSlateNotificationManager::Get().AddNotification(NotifyInfo);
		return;
	}
	const FString PackagePath = FPackageName::ObjectPathToPackageName(SaveObjectPath);
	const FString AssetName = FPaths::GetBaseFilename(PackagePath, true);
	LastSavePath = PackagePath;
	if (!AssetName.IsEmpty()) {
		UPackage* NewPackage = CreatePackage(*PackagePath);
		UObject* NewAsset = DuplicateObject<UObject>(Result, NewPackage, *AssetName);
		NewAsset->SetFlags(RF_Public | RF_Standalone);
		FAssetRegistryModule::AssetCreated(NewAsset);
		FPackagePath NewPackagePath = FPackagePath::FromPackageNameChecked(NewPackage->GetName());
		FString PackageLocalPath = NewPackagePath.GetLocalFullPath();
		UPackage::SavePackage(NewPackage, NewAsset, RF_Public | RF_Standalone, *PackageLocalPath, GError, nullptr, false, true, SAVE_NoError);
		TArray<UObject*> ObjectsToSync;
		ObjectsToSync.Add(NewAsset);
		GEditor->SyncBrowserToObjects(ObjectsToSync);
		Result = NewAsset;
	}
}

UObject* UGaussianSplattingStep_GaussianSplatting::LoadPly(UObject* Outer, FName AssetName)
{
	UGaussianSplattingPointCloud* Output = nullptr;
	FString PlyPath = FString::Printf(TEXT("%s/output/point_cloud/iteration_%d/point_cloud.ply"), *WorkDir, Iterations);
	if (bClippingByMask) {
		PlyPath = Clip(PlyPath);
	}
	Output = UGaussianSplattingEditorLibrary::LoadSplatPly(PlyPath, Outer, AssetName);
	Output->SetCompressionMethod(CompressionMethod);
	return Output;
}

void UGaussianSplattingStep_GaussianSplatting::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	const FName PropertyName = PropertyChangedEvent.GetMemberPropertyName();
	UpdateParams();
}

void UGaussianSplattingStep_GaussianSplatting::UpdateParams()
{
	GaussianSplattingTrainParams = FString::Printf(TEXT("--resolution %d --iterations %d --save_iterations %d --feature_lr %f --opacity_lr %f --scaling_lr %f --rotation_lr %f --position_lr_max_steps %d --position_lr_init %f --position_lr_final %f --position_lr_delay_mult %f --densify_from_iter %d --densify_until_iter %d --densify_grad_threshold %f --densification_interval %d --opacity_reset_interval %d --depth_l1_weight_init %f --depth_l1_weight_final %f --lambda_dssim %f --percent_dense %f")
		, Resolution
		, Iterations
		, Iterations
		, Feature_LR
		, Opacity_LR
		, Scaling_LR
		, Rotation_LR
		, Position_LR_MaxSteps
		, Position_LR_Init
		, Position_LR_Final
		, Position_LR_DelayMult
		, DensifyFromIter
		, DensifyUntilIter
		, DensifyGradThreshold
		, DensificationInterval
		, OpacityResetInterval
		, Depth_L1_WeightInit
		, Depth_L1_WeightFinal
		, LambdaDssim
		, PercentDense
	);
}
