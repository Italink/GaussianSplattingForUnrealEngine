#pragma once

#include "Engine/Texture2D.h"
#include "NiagaraSystem.h"
#include "GaussianSplattingPointDataInterface.h"


namespace GaussianSplattingUtils{

	FLinearColor SRGBToLinear(const FLinearColor& Color);

	FLinearColor LinearToSRGB(const FLinearColor& Color);

	FVector UVtoPyramid(FVector2D UV);

	FVector UVtoOctahedron(FVector2D uv);

	UTexture2D* CreateFloat16TextureFromData(UObject* Outer, FString Name, uint32 Width, uint32 Height, TArray<FFloat16> Data);

	UStaticMesh* LoadSplatPlyAsStaticMesh(FString FileName, UObject* Outer, FName AssetName = NAME_None, FBox ClipBound = FBox(), float DistanceOfObservation = 0, float MinScreenSizeOfObservation = 0.01);

	UNiagaraSystem* LoadSplatPlyAsParticles(FString FileName, UObject* Outer, FName AssetName = NAME_None, FBox ClipBound = FBox(), float DistanceOfObservation = 0, float MinScreenSizeOfObservation = 0.01, int FeatureLevel = 1024);

	bool IsVaildGaussianPoint(const FGaussianSplattingPoint& Point, FBox ClipBound, float DistanceOfObservation, float MinScreenSizeOfObservation);
};