#pragma once

#include <cstdint>
#include <vector>

class Generator
{
public:
	static std::vector<float> generateSine(const uint32_t numSamples, float amplitude = 1.0f, bool signedSamples = false);
	static std::vector<float> generateSquare(const uint32_t numSamples, float amplitude = 1.0f, bool signedSamples = false);
	static std::vector<float> generateTriangle(const uint32_t numSamples, float amplitude = 1.0f, bool signedSamples = false);
};
