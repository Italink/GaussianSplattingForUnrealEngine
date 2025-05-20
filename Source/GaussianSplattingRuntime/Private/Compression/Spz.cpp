#include "Spz.h"

#include <zlib.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#ifdef ANDROID
#include <android/log.h>
#endif

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace Spz {

	class MemBuf : public std::streambuf {
	public:
		MemBuf(const uint8_t* begin, const uint8_t* end) {
			char* pBegin = const_cast<char*>(reinterpret_cast<const char*>(begin));
			char* pEnd = const_cast<char*>(reinterpret_cast<const char*>(end));
			this->setg(pBegin, pBegin, pEnd);
		}
	};

	namespace {

#ifdef SPZ_ENABLE_LOGS
#ifdef ANDROID
		static constexpr char LOG_TAG[] = "SPZ";
		template <class... Args> static void SpzLog(const char* fmt, Args &&...args) {
			__android_log_print(ANDROID_LOG_INFO, LOG_TAG, fmt,
				std::forward<Args>(args)...);
		}
#else
		template <class... Args> static void SpzLog(const char* fmt, Args &&...args) {
			printf(fmt, std::forward<Args>(args)...);
			printf("\n");
			fflush(stdout);
		}
#endif // ANDROID

		template <class... Args> static void SpzLog(const char* fmt) {
			SpzLog("%s", fmt);
		}
#else
		// No-op versions when logging is disabled
		template <class... Args> static void SpzLog(const char* fmt, Args &&...args) {}

		template <class... Args> static void SpzLog(const char* fmt) {}
#endif // SPZ_ENABLE_LOGS

		// Scale factor for DC color components. To convert to RGB, we should multiply
		// by 0.282, but it can be useful to represent base colors that are out of range
		// if the higher spherical harmonics bands bring them back into range so we
		// multiply by a smaller value.
		constexpr float colorScale = 0.15f;

		int degreeForDim(int dim) {
			if (dim < 3)
				return 0;
			if (dim < 8)
				return 1;
			if (dim < 15)
				return 2;
			return 3;
		}

		int dimForDegree(int degree) {
			switch (degree) {
			case 0:
				return 0;
			case 1:
				return 3;
			case 2:
				return 8;
			case 3:
				return 15;
			default:
				SpzLog("[SPZ: ERROR] Unsupported SH degree: %d\n", degree);
				return 0;
			}
		}

		uint8_t toUint8(float x) {
			return static_cast<uint8_t>(std::clamp(std::round(x), 0.0f, 255.0f));
		}

		// Quantizes to 8 bits, the round to nearest bucket center. 0 always maps to a
		// bucket center.
		uint8_t quantizeSH(float x, int bucketSize) {
			int q = static_cast<int>(std::round(x * 128.0f) + 128.0f);
			q = (q + bucketSize / 2) / bucketSize * bucketSize;
			return static_cast<uint8_t>(std::clamp(q, 0, 255));
		}

		float unquantizeSH(uint8_t x) {
			return (static_cast<float>(x) - 128.0f) / 128.0f;
		}

		float sigmoid(float x) { return 1 / (1 + std::exp(-x)); }

		float invSigmoid(float x) { return std::log(x / (1.0f - x)); }

		template <typename T> size_t countBytes(const std::vector<T>& vec) {
			return vec.size() * sizeof(vec[0]);
		}

#define CHECK(x)                                                               \
  {                                                                            \
    if (!(x)) {                                                                \
      SpzLog("[SPZ: ERROR] Check failed: %s:%d: %s", __FILE__, __LINE__, #x);  \
      return false;                                                            \
    }                                                                          \
  }

#define CHECK_GE(x, y) CHECK((x) >= (y))
#define CHECK_LE(x, y) CHECK((x) <= (y))
#define CHECK_EQ(x, y) CHECK((x) == (y));

		bool checkSizes(const PackedGaussians& packed, int numPoints, bool usesFloat16) {
			CHECK_EQ(packed.positions.size(), numPoints * 3 * (usesFloat16 ? 2 : 3));
			CHECK_EQ(packed.scales.size(), numPoints * 3);
			CHECK_EQ(packed.rotations.size(), numPoints * 3);
			CHECK_EQ(packed.alphas.size(), numPoints);
			CHECK_EQ(packed.colors.size(), numPoints * 3);
			return true;
		}

		constexpr uint8_t FlagAntialiased = 0x1;

		struct PackedGaussiansHeader {
			uint32_t magic = 0x5053474e; // NGSP = Niantic gaussian splat
			uint32_t version = 2;
			uint32_t numPoints = 0;
			uint8_t shDegree = 0;
			uint8_t fractionalBits = 0;
			uint8_t flags = 0;
			uint8_t reserved = 0;
		};

		bool decompressGzippedImpl(
			const uint8_t* compressed, size_t size, int windowSize, std::vector<uint8_t>* out) {
			std::vector<uint8_t> buffer(8192);
			z_stream stream = {};
			stream.next_in = const_cast<Bytef*>(compressed);
			stream.avail_in = size;
			if (inflateInit2(&stream, windowSize) != Z_OK) {
				return false;
			}
			out->clear();
			bool success = false;
			while (true) {
				stream.next_out = buffer.data();
				stream.avail_out = buffer.size();
				int res = inflate(&stream, Z_NO_FLUSH);
				if (res != Z_OK && res != Z_STREAM_END) {
					break;
				}
				out->insert(out->end(), buffer.data(), buffer.data() + buffer.size() - stream.avail_out);
				if (res == Z_STREAM_END) {
					success = true;
					break;
				}
			}
			inflateEnd(&stream);
			return success;
		}
		
		bool decompressGzipped(const uint8_t* compressed, size_t size, std::vector<uint8_t>* out) {
			// Here 16 means enable automatic gzip header detection; consider switching this to 32 to enable
			// both automated gzip and zlib header detection.
			return decompressGzippedImpl(compressed, size, 16 | MAX_WBITS, out);
		}

		bool decompressGzipped(const uint8_t* compressed, size_t size, std::string* out) {
			std::vector<uint8_t> buffer;
			if (!decompressGzipped(compressed, size, &buffer)) {
				return false;
			}
			out->assign(reinterpret_cast<const char*>(buffer.data()), buffer.size());
			return true;
		}

		bool compressGzipped(const uint8_t* data, size_t size, std::vector<uint8_t>* out) {
			std::vector<uint8_t> buffer(8192);
			z_stream stream = {};
			if (
				deflateInit2(&stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 16 + MAX_WBITS, 9, Z_DEFAULT_STRATEGY)
				!= Z_OK) {
				return false;
			}
			out->clear();
			out->reserve(size / 4);
			stream.next_in = const_cast<Bytef*>(reinterpret_cast<const Bytef*>(data));
			stream.avail_in = size;
			bool success = false;
			while (true) {
				stream.next_out = buffer.data();
				stream.avail_out = buffer.size();
				int res = deflate(&stream, Z_FINISH);
				if (res != Z_OK && res != Z_STREAM_END) {
					break;
				}
				out->insert(out->end(), buffer.data(), buffer.data() + buffer.size() - stream.avail_out);
				if (res == Z_STREAM_END) {
					success = true;
					break;
				}
			}
			deflateEnd(&stream);
			return success;
		}
	} // namespace

	PackedGaussians packGaussians(const TArray<FGaussianSplattingPoint>& g) {

		const int numPoints = g.Num();

		// Use 12 bits for the fractional part of coordinates (~0.25 millimeter
		// resolution). In the future we can use different values on a per-splat basis
		// and still be compatible with the decoder.
		PackedGaussians packed = {
			.numPoints = numPoints,
			.fractionalBits = 12,
		};
		packed.positions.resize(numPoints * 3 * 3);
		packed.scales.resize(numPoints * 3);
		packed.rotations.resize(numPoints * 3);
		packed.alphas.resize(numPoints);
		packed.colors.resize(numPoints * 3);

		// Store coordinates as 24-bit fixed point values.
		const float scale = (1 << packed.fractionalBits);
		for (size_t i = 0; i < numPoints; i++) {
			const FVector3f& UEPosition = g[i].Position;
			for (size_t j = 0; j < 3; j++) {
				const int32_t fixed32 =
					static_cast<int32_t>(std::round(UEPosition[j] / 100.0f * scale));
				packed.positions[i * 9 + j * 3 + 0] = fixed32 & 0xff;
				packed.positions[i * 9 + j * 3 + 1] = (fixed32 >> 8) & 0xff;
				packed.positions[i * 9 + j * 3 + 2] = (fixed32 >> 16) & 0xff;
			}
		}

		for (size_t i = 0; i < numPoints ; i++) {
			const FVector3f& UEScale = g[i].Scale;
			for (size_t j = 0; j < 3; j++) {
				packed.scales[i * 3 + j] = toUint8((FMath::Loge(UEScale[j] / 100.0f) + 10.0f) * 16.0f);
			}
		}

		for (size_t i = 0; i < numPoints; i++) {
			// Normalize the quaternion, make w positive, then store xyz. w can be
			// derived from xyz. NOTE: These are already in xyzw order.
			FQuat4f Quat = g[i].Quat;
			Quat.Normalize();
			FVector4 Q(Quat.X, Quat.Y, Quat.Z, Quat.W);
			Q = Q * (Q[3] < 0 ? -127.5f : 127.5f);
			Q = Q + FVector4(127.5f, 127.5f, 127.5f, 127.5f);

			packed.rotations[i * 3 + 0] = toUint8(Q[0]);
			packed.rotations[i * 3 + 1] = toUint8(Q[1]);
			packed.rotations[i * 3 + 2] = toUint8(Q[2]);
		}

		for (size_t i = 0; i < numPoints; i++) {
			const FVector4f& Color = g[i].Color;
			packed.alphas[i] = toUint8(sigmoid(Color.W) * 255.0f);
			packed.colors[i * 3 + 0] = toUint8(Color[0] * (colorScale * 255.0f) + (0.5f * 255.0f));
			packed.colors[i * 3 + 1] = toUint8(Color[1] * (colorScale * 255.0f) + (0.5f * 255.0f));
			packed.colors[i * 3 + 2] = toUint8(Color[2] * (colorScale * 255.0f) + (0.5f * 255.0f));
		}
		return packed;
	}

	UnpackedGaussian PackedGaussian::unpack(bool usesFloat16,
		int fractionalBits) const {
		UnpackedGaussian result;
		if (usesFloat16) {
			// Decode legacy float16 format. We can remove this at some point as it was
			// never released.
			const auto* halfData = reinterpret_cast<const Half*>(position.data());
			for (size_t i = 0; i < 3; i++) {
				result.position[i] = halfToFloat(halfData[i]);
			}
		}
		else {
			// Decode 24-bit fixed point coordinates
			float fixedScale = 1.0 / (1 << fractionalBits);
			for (size_t i = 0; i < 3; i++) {
				int32_t fixed32 = position[i * 3 + 0];
				fixed32 |= position[i * 3 + 1] << 8;
				fixed32 |= position[i * 3 + 2] << 16;
				fixed32 |= (fixed32 & 0x800000) ? 0xff000000 : 0; // sign extension
				result.position[i] = static_cast<float>(fixed32) * fixedScale;
			}
		}

		for (size_t i = 0; i < 3; i++) {
			result.scale[i] = (scale[i]  / 16.0f - 10.0f);
		}

		const uint8_t* r = &rotation[0];
		FVector3f xyz = {
			static_cast<float>(r[0]),
			static_cast<float>(r[1]),
			static_cast<float>(r[2])
		};
		xyz = xyz / 127.5f + FVector3f(-1, -1, -1);

		result.rotation[0] = xyz.X;
		result.rotation[1] = xyz.Y;
		result.rotation[2] = xyz.Z;

		// Compute the real component - we know the quaternion is normalized and w is
		// non-negative
		result.rotation[3] = std::sqrt(std::max(0.0f, 1.0f - xyz.SquaredLength()));

		result.alpha = invSigmoid(alpha / 255.0f);

		for (size_t i = 0; i < 3; i++) {
			result.color[i] = ((color[i] / 255.0f) - 0.5f) / colorScale;
		}

		return result;
	}

	PackedGaussian PackedGaussians::at(int i) const {
		PackedGaussian result;
		int positionBits = usesFloat16() ? 6 : 9;
		int start3 = i * 3;
		const auto* p = &positions[i * positionBits];
		std::copy(p, p + positionBits, result.position.data());
		std::copy(&scales[start3], &scales[start3 + 3], result.scale.data());
		std::copy(&rotations[start3], &rotations[start3 + 3], result.rotation.data());
		std::copy(&colors[start3], &colors[start3 + 3], result.color.data());
		result.alpha = alphas[i];

		return result;
	}

	UnpackedGaussian PackedGaussians::unpack(int i) const {
		return at(i).unpack(usesFloat16(), fractionalBits);
	}

	bool PackedGaussians::usesFloat16() const {
		return positions.size() == numPoints * 3 * 2;
	}

	TArray<FGaussianSplattingPoint> unpackGaussians(const PackedGaussians& packed) {
		const int numPoints = packed.numPoints;

		const bool usesFloat16 = packed.usesFloat16();
		if (!checkSizes(packed, numPoints, usesFloat16)) {
			return {};
		}

		TArray<FGaussianSplattingPoint> result;
		result.SetNum(numPoints);

		if (usesFloat16) {
			// Decode legacy float16 format. We can remove this at some point as it was
			// never released.
			const auto* halfData =
				reinterpret_cast<const Half*>(packed.positions.data());
			for (size_t i = 0; i < numPoints; i++) {
				for (size_t j = 0; j < 3; j++) {
					result[i].Position[j] = halfToFloat(halfData[i * 3 + j]);
				}
			}
		}
		else {
			// Decode 24-bit fixed point coordinates
			float scale = 1.0 / (1 << packed.fractionalBits);
			for (size_t i = 0; i < numPoints; i++) {
				for (size_t j = 0; j < 3; j++) {
					int32_t fixed32 = packed.positions[i * 9 + j * 3 + 0];
					fixed32 |= packed.positions[i * 9 + j * 3 + 1] << 8;
					fixed32 |= packed.positions[i * 9 + j * 3 + 2] << 16;
					fixed32 |= (fixed32 & 0x800000) ? 0xff000000 : 0; // sign extension
					result[i].Position[j] = static_cast<float>(fixed32) * scale * 100.0f;
				}
			}
		}

		for (size_t i = 0; i < numPoints; i++) {
			for (size_t j = 0; j < 3; j++) {
				result[i].Scale[j] = 100.0f * FMath::Exp(packed.scales[i * 3 + j] / 16.0f - 10.0f);
			}
		}

		for (size_t i = 0; i < numPoints; i++) {
			const uint8_t* r = &packed.rotations[i * 3];

			FVector3f xyz = {
				static_cast<float>(r[0]),
				static_cast<float>(r[1]),
				static_cast<float>(r[2])
			};
			xyz = xyz / 127.5f + FVector3f(-1, -1, -1);

			result[i].Quat.X = xyz.X;
			result[i].Quat.Y = xyz.Y;
			result[i].Quat.Z = xyz.Z;
			result[i].Quat.W = std::sqrt(std::max(0.0f, 1.0f - xyz.SquaredLength()));
		}

		for (size_t i = 0; i < numPoints; i++) {
			result[i].Color.A = invSigmoid(packed.alphas[i] / 255.0f);
			result[i].Color.R = ((packed.colors[i * 3 + 0] / 255.0f) - 0.5f) / colorScale;
			result[i].Color.G = ((packed.colors[i * 3 + 1] / 255.0f) - 0.5f) / colorScale;
			result[i].Color.B = ((packed.colors[i * 3 + 2] / 255.0f) - 0.5f) / colorScale;
		}

		return result;
	}

	void serializePackedGaussians(const PackedGaussians& packed,
		std::ostream& out) {
		PackedGaussiansHeader header = {
			.numPoints = static_cast<uint32_t>(packed.numPoints),
			.fractionalBits = static_cast<uint8_t>(packed.fractionalBits),
			.flags = static_cast<uint8_t>(0),
		};
		out.write(reinterpret_cast<const char*>(&header), sizeof(header));
		out.write(reinterpret_cast<const char*>(packed.positions.data()),
			countBytes(packed.positions));
		out.write(reinterpret_cast<const char*>(packed.alphas.data()),
			countBytes(packed.alphas));
		out.write(reinterpret_cast<const char*>(packed.colors.data()),
			countBytes(packed.colors));
		out.write(reinterpret_cast<const char*>(packed.scales.data()),
			countBytes(packed.scales));
		out.write(reinterpret_cast<const char*>(packed.rotations.data()),
			countBytes(packed.rotations));
	}

	PackedGaussians deserializePackedGaussians(std::istream& in) {
		constexpr int maxPointsToRead = 10000000;

		PackedGaussiansHeader header;
		in.read(reinterpret_cast<char*>(&header), sizeof(header));
		if (!in || header.magic != PackedGaussiansHeader().magic) {
			SpzLog("[SPZ ERROR] deserializePackedGaussians: header not found");
			return {};
		}
		if (header.version < 1 || header.version > 2) {
			SpzLog("[SPZ ERROR] deserializePackedGaussians: version not supported: %d",
				header.version);
			return {};
		}
		if (header.numPoints > maxPointsToRead) {
			SpzLog("[SPZ ERROR] deserializePackedGaussians: Too many points: %d",
				header.numPoints);
			return {};
		}
		if (header.shDegree > 3) {
			SpzLog("[SPZ ERROR] deserializePackedGaussians: Unsupported SH degree: %d",
				header.shDegree);
			return {};
		}
		const int numPoints = header.numPoints;
		const int shDim = dimForDegree(header.shDegree);
		const bool usesFloat16 = header.version == 1;
		PackedGaussians result = { .numPoints = numPoints,
								  .fractionalBits = header.fractionalBits};
		result.positions.resize(numPoints * 3 * (usesFloat16 ? 2 : 3));
		result.scales.resize(numPoints * 3);
		result.rotations.resize(numPoints * 3);
		result.alphas.resize(numPoints);
		result.colors.resize(numPoints * 3);
		in.read(reinterpret_cast<char*>(result.positions.data()),
			countBytes(result.positions));
		in.read(reinterpret_cast<char*>(result.alphas.data()),
			countBytes(result.alphas));
		in.read(reinterpret_cast<char*>(result.colors.data()),
			countBytes(result.colors));
		in.read(reinterpret_cast<char*>(result.scales.data()),
			countBytes(result.scales));
		in.read(reinterpret_cast<char*>(result.rotations.data()),
			countBytes(result.rotations));
		if (!in) {
			SpzLog("[SPZ ERROR] deserializePackedGaussians: read error");
			return {};
		}
		return result;
	}

	float halfToFloat(Half h) {
		auto sgn = ((h >> 15) & 0x1);
		auto exponent = ((h >> 10) & 0x1f);
		auto mantissa = h & 0x3ff;

		float signMul = sgn == 1 ? -1.0 : 1.0;
		if (exponent == 0) {
			// Subnormal numbers (no exponent, 0 in the mantissa decimal).
			return signMul * std::pow(2.0f, -14.0f) * static_cast<float>(mantissa) / 1024.0f;
		}

		if (exponent == 31) {
			// Infinity or NaN
			if (mantissa != 0) {
				return std::numeric_limits<float>::quiet_NaN();
			}
			else {
				return signMul * std::numeric_limits<float>::infinity();
			}
		}

		// non-zero exponent implies 1 in the mantissa decimal.
		return signMul * std::pow(2.0f, static_cast<float>(exponent) - 15.0f)
			* (1.0f + static_cast<float>(mantissa) / 1024.0f);
	}

	Half floatToHalf(float f) {
		auto f32 = BitCast<uint32_t>(f);
		int sign = (f32 >> 31) & 0x01;        // 1 bit   -> 1 bit
		int exponent = ((f32 >> 23) & 0xff);  // 8 bits  -> 5 bits
		int mantissa = f32 & 0x7fffff;        // 23 bits -> 10 bits

		// Handle inf and nan from float.
		if (exponent == 0xFF) {
			if (mantissa == 0) {
				return (sign << 15) | 0x7C00; // Inf
			}

			return (sign << 15) | 0x7C01;  // Nan
		}

		// If the exponent is greater than the range of half, return +/- Inf.
		int centeredExp = exponent - 127;
		if (centeredExp > 15) {
			return (sign << 15) | 0x7C00;
		}

		// Normal numbers. centeredExp = [-15, 15]
		if (centeredExp > -15) {
			return (sign << 15) | ((centeredExp + 15) << 10) | (mantissa >> 13);
		}

		// Subnormal numbers.
		int fullMantissa = 0x800000 | mantissa;
		int shift = -(centeredExp + 14);  // Shift is in [-1 to -113]
		int newMantissa = fullMantissa >> shift;
		return (sign << 15) | (newMantissa >> 13);
	}


	bool compress(const TArray<FGaussianSplattingPoint> g, int compressionLevel,
		int workers, std::vector<uint8_t>& output) {
		if (g.Num() == 0) {
			SpzLog("[SPZ: ERROR] Parsed TArray<FGaussianSplattingPoint> is empty.");
			return false;
		}

		PackedGaussians packed = packGaussians(g);

		std::stringstream ss;
		serializePackedGaussians(packed, ss);
		const std::string uncompressed = ss.str();

		if (!compressGzipped(reinterpret_cast<const uint8_t*>(uncompressed.data()), uncompressed.size(), &output)) {
			SpzLog("[SPZ: ERROR] Zstd compression failed.");
			return false;
		}

		return true;
	}

	bool decompress(const std::span<const uint8_t> input, TArray<FGaussianSplattingPoint>& output) {
		std::vector<uint8_t> decompressed;
		if (!decompressGzipped(input.data(), input.size(), &decompressed) ||
			decompressed.empty()) {
			return false;
		}

		MemBuf memBuffer(decompressed.data(),
			decompressed.data() + decompressed.size());
		std::istream stream(&memBuffer);
		PackedGaussians packed = deserializePackedGaussians(stream);

		if (packed.numPoints == 0 && packed.positions.empty()) {
			return false;
		}

		output = unpackGaussians(packed);

		return true;
	}
} // namespace Spz
