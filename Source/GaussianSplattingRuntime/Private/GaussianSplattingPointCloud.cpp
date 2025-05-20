#include "GaussianSplattingPointCloud.h"
#include "Compression/Spz.h"
#include <zlib.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

const float SH_0 = 0.28209479177387814f;

FGaussianSplattingPoint::FGaussianSplattingPoint(FVector3f InPos /*= FVector3f::ZeroVector*/, FQuat4f InQuat /*= FQuat4f::Identity*/, FVector3f InScale /*= {1,1,1}*/, FLinearColor InColor /*= FLinearColor::Black*/) : Position(InPos)
, Quat(InQuat)
, Scale(InScale)
, Color(InColor)
{

}

bool FGaussianSplattingPoint::operator<(const FGaussianSplattingPoint& Other) const
{
	return Position.X < Other.Position.X;
}

bool FGaussianSplattingPoint::operator!=(const FGaussianSplattingPoint& Other) const
{
	return !(*this == Other);
}

bool FGaussianSplattingPoint::operator==(const FGaussianSplattingPoint& Other) const
{
	return Position == Other.Position && Quat == Other.Quat && Scale == Other.Scale && Color == Other.Color;
}

UGaussianSplattingPointCloud::UGaussianSplattingPointCloud(FObjectInitializer const& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FRichCurve UGaussianSplattingPointCloud::CalcFeatureCurve()
{
	FRichCurve Curve;
	int Step = FMath::Max(Points.Num() / FeatureLevel, 1u);
	for (int i = 0; i < Points.Num(); i += Step) {
		auto KeyHandle = Curve.AddKey(4 * Points[i].Scale.Length(), i);
		Curve.SetKeyInterpMode(KeyHandle, ERichCurveInterpMode::RCIM_Constant);
	}
	return Curve;
}

FBox UGaussianSplattingPointCloud::CalcBounds()
{
	FBox Bounds;
	Bounds.Min = FVector(FLT_MAX);
	Bounds.Max = FVector(FLT_MIN);

	for (const auto& Point : Points) {
		Bounds.Max = FVector::Max(Bounds.Max, FVector(Point.Position));
		Bounds.Min = FVector::Min(Bounds.Min, FVector(Point.Position));
	}
	return Bounds.ExpandBy(FVector(Points[0].Scale.Length()));
}

void UGaussianSplattingPointCloud::SetPoints(const TArray<FGaussianSplattingPoint>& InPoints, bool bReorder /*= true*/)
{
	Points = InPoints;
	if (bReorder) {
		Algo::Sort(Points, [](const FGaussianSplattingPoint& ItemA, const FGaussianSplattingPoint& ItemB) {
			return ItemA.Scale.Length() > ItemB.Scale.Length();
		});
	}
	OnPointsChanged.Broadcast();
}

const TArray<FGaussianSplattingPoint>& UGaussianSplattingPointCloud::GetPoints() const
{
	return Points;
}

int32 UGaussianSplattingPointCloud::GetPointCount() const
{
	return Points.Num();
}

FLinearColor SRGBToLinear(const FLinearColor& Color)
{
	auto SRGBToLinearFloat = [](const float Color) -> float
		{
			return (Color <= 0.04045f) ? Color / 12.92f : FMath::Pow((Color + 0.055f) / 1.055f, 2.4f);
		};

	return FLinearColor(
		SRGBToLinearFloat(Color.R)
		, SRGBToLinearFloat(Color.G)
		, SRGBToLinearFloat(Color.B)
		, Color.A
	);
}

TArray<FGaussianSplattingPoint> ParseSplatFromStream(std::istream& in)
{
	TArray<FGaussianSplattingPoint> Result;
	if (!in.good()) {
		UE_LOG(LogTemp, Warning, TEXT("Unable to read from input stream."));
		return Result;
	}

	std::string line;
	std::getline(in, line);
	if (line != "ply") {
		UE_LOG(LogTemp, Warning, TEXT("Input data is not a .ply file."));
		return Result;
	}

	std::getline(in, line);
	if (line != "format binary_little_endian 1.0") {
		UE_LOG(LogTemp, Warning, TEXT("Unsupported .ply format."));
		return Result;
	}

	std::getline(in, line);
	if (line.find("element vertex ") != 0) {
		UE_LOG(LogTemp, Warning, TEXT("Missing vertex count."));
		return Result;
	}

	int numPoints = std::stoi(line.substr(std::strlen("element vertex ")));

	if (numPoints <= 0 || numPoints > 10 * 1024 * 1024) {
		UE_LOG(LogTemp, Warning, TEXT("Invalid vertex count: %d"), numPoints);
		return Result;
	}

	UE_LOG(LogTemp, Log, TEXT("Loading %d points"), numPoints);
	std::unordered_map<std::string, int> fields; // name -> index
	for (int i = 0;; i++) {
		if (!std::getline(in, line)) {
			UE_LOG(LogTemp, Warning, TEXT("Unexpected end of header."));
			return Result;
		}

		if (line == "end_header")
			break;

		if (line.find("property float ") != 0) {
			UE_LOG(LogTemp, Warning, TEXT("Unsupported property data type"));
			return Result;
		}
		std::string name = line.substr(std::strlen("property float "));
		fields[name] = i;
	}

	// Returns the index for a given field name, ensuring the name exists.
	const auto index = [&fields](const std::string& name) {
		const auto& itr = fields.find(name);
		if (itr == fields.end()) {
			UE_LOG(LogTemp, Warning, TEXT("Missing field"));
			return -1;
		}
		return itr->second;
		};

	const std::vector<int> positionIdx = { index("x"), index("y"), index("z") };
	const std::vector<int> scaleIdx = { index("scale_0"), index("scale_1"),
									   index("scale_2") };
	const std::vector<int> rotIdx = { index("rot_1"), index("rot_2"),
									 index("rot_3"), index("rot_0") };
	const std::vector<int> alphaIdx = { index("opacity") };
	const std::vector<int> colorIdx = { index("f_dc_0"), index("f_dc_1"),
									   index("f_dc_2") };

	// Check that only valid indices were returned.
	auto checkIndices = [&](const std::vector<int>& idxVec) -> bool {
		for (auto idx : idxVec) {
			if (idx < 0) {
				return false;
			}
		}
		return true;
		};

	if (!checkIndices(positionIdx) || !checkIndices(scaleIdx) ||
		!checkIndices(rotIdx) || !checkIndices(alphaIdx) ||
		!checkIndices(colorIdx)) {
		return Result;
	}

	// Spherical harmonics are optional and variable in size (depending on degree)
	std::vector<int> shIdx;
	for (int i = 0; i < 45; i++) {
		const auto& itr = fields.find("f_rest_" + std::to_string(i));
		if (itr == fields.end())
			break;
		shIdx.push_back(itr->second);
	}
	const int shDim = static_cast<int>(shIdx.size() / 3);

	// If spherical harmonics fields are present, ensure they are complete
	if (shIdx.size() % 3 != 0) {
		UE_LOG(LogTemp, Warning, TEXT("Incomplete spherical harmonics fields."));
		return Result;
	}

	std::vector<float> values;
	values.resize(numPoints * fields.size());

	in.read(reinterpret_cast<char*>(values.data()),
		values.size() * sizeof(float));
	if (!in.good()) {
		UE_LOG(LogTemp, Warning, TEXT("Unable to load data from input stream."));
		return Result;
	}

	Result.SetNum(numPoints);

	for (size_t i = 0; i < static_cast<size_t>(numPoints); i++) {
		size_t vertexOffset = i * fields.size();
		FGaussianSplattingPoint& Point = Result[i];

		// Position
		FVector3f Position = FVector3f(
			values[vertexOffset + positionIdx[0]],
			values[vertexOffset + positionIdx[1]],
			values[vertexOffset + positionIdx[2]]
		);
		Point.Position = 100 * FVector3f(Position.X, -Position.Z, -Position.Y);

		// Scale
		FVector3f Scale = FVector3f(
			FMath::Exp(values[vertexOffset + scaleIdx[0]]),
			FMath::Exp(values[vertexOffset + scaleIdx[1]]),
			FMath::Exp(values[vertexOffset + scaleIdx[2]])
		);
		Point.Scale = 100 * FVector3f(Scale.X, Scale.Z, Scale.Y);

		// Rotation
		FQuat4f Quat = FQuat4f(
			values[vertexOffset + rotIdx[0]],
			values[vertexOffset + rotIdx[1]],
			values[vertexOffset + rotIdx[2]],
			values[vertexOffset + rotIdx[3]]
		);
		Quat.Normalize();

		Point.Quat = FQuat4f(Quat.X, -Quat.Z, -Quat.Y, Quat.W);

		// Color
		FLinearColor Color = FLinearColor(
			SH_0 * values[vertexOffset + colorIdx[0]] + 0.5f,
			SH_0 * values[vertexOffset + colorIdx[1]] + 0.5f,
			SH_0 * values[vertexOffset + colorIdx[2]] + 0.5f,
			1.0f / (1.0f + FMath::Exp(-values[vertexOffset + alphaIdx[0]]))
		);
		Point.Color = SRGBToLinear(Color);
	}
	return Result;
}

void UGaussianSplattingPointCloud::LoadFromFile(FString InFilePath)
{
	Points = LoadPointsFromFile(InFilePath);
}

TArray<FGaussianSplattingPoint> UGaussianSplattingPointCloud::LoadPointsFromFile(FString InFilePath)
{
	std::ifstream IStream(TCHAR_TO_UTF8(*InFilePath), std::ios::binary);
	if (!IStream.is_open()) {
		UE_LOG(LogTemp, Warning, TEXT("Unable to open: %s"), *InFilePath);
		return {};
	}
	return ParseSplatFromStream(IStream);
}

void UGaussianSplattingPointCloud::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
	if (GetCompressionMethod() == EGaussianSplattingCompressionMethod::None) {
		Ar << Points;
	}
	else if(GetCompressionMethod() == EGaussianSplattingCompressionMethod::Zlib){
		if (Ar.IsLoading()) {
			std::vector<uint8_t> CompressedData;
			int CompressedDataSize = 0;
			Ar << CompressedDataSize;
			CompressedData.resize(CompressedDataSize);
			Ar.Serialize(CompressedData.data(), CompressedData.size() * sizeof(uint8_t));
			Spz::decompress(CompressedData, Points);
		}
		else if (Ar.IsSaving()) {
			std::vector<uint8_t> CompressedData;
			Spz::compress(Points, 3, 1, CompressedData);
			int CompressedDataSize = CompressedData.size();
			Ar << CompressedDataSize;
			Ar.Serialize(CompressedData.data(), CompressedData.size() * sizeof(uint8_t));
		}
	}
}
