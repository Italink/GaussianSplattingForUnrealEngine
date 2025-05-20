#pragma once

#include <array>
#include <span>
#include <string>
#include <vector>
#include "GaussianSplattingPointCloud.h"

// https://github.com/nianticlabs/spz
namespace Spz {

// Represents a single inflated gaussian. Each gaussian has 236 bytes. Although the data is easier
// to intepret in this format, it is not more precise than the packed format, since it was inflated.
struct UnpackedGaussian {
  std::array<float, 3> position;  // x, y, z
  std::array<float, 4> rotation;  // x, y, z, w
  std::array<float, 3> scale;     // std::log(scale)
  std::array<float, 3> color;     // rgb sh0 encoding
  float alpha;                    // inverse logistic
};

// Represents a single low precision gaussian. Each gaussian has exactly 64 bytes, even if it does
// not have full spherical harmonics.
struct PackedGaussian {
  std::array<uint8_t, 9> position{};
  std::array<uint8_t, 3> rotation{};
  std::array<uint8_t, 3> scale{};
  std::array<uint8_t, 3> color{};
  uint8_t alpha = 0;
  UnpackedGaussian unpack(bool usesFloat16, int fractionalBits) const;
};

// Represents a full splat with lower precision. Each splat has at most 64 bytes, although splats
// with fewer spherical harmonics degrees will have less. The data is stored non-interleaved.
struct PackedGaussians {
  int numPoints = 0;        // Total number of points (gaussians)
  int fractionalBits = 0;   // Number of bits used for fractional part of fixed-point coords

  std::vector<uint8_t> positions;
  std::vector<uint8_t> scales;
  std::vector<uint8_t> rotations;
  std::vector<uint8_t> alphas;
  std::vector<uint8_t> colors;

  bool usesFloat16() const;
  PackedGaussian at(int i) const;
  UnpackedGaussian unpack(int i) const;
};

using Half = uint16_t;

// Half-precision helpers.
float halfToFloat(Half h);
Half floatToHalf(float f);

GAUSSIANSPLATTINGRUNTIME_API bool compress(
	const TArray<FGaussianSplattingPoint> g,
	int compressionLevel,
	int workers,
	std::vector<uint8_t>& output);

GAUSSIANSPLATTINGRUNTIME_API bool decompress(
	const std::span<const uint8_t> input,
    TArray<FGaussianSplattingPoint>& output);

}  // namespace Spz

