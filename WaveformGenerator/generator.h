#pragma once

#include <vector>

class Generator
{
public:
	static std::vector<float> generateSine(const uint32_t numSamples, float amplitude = 1.0f, bool signedSamples = false);
};
