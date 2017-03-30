#include "generator.h"

#include <cmath>

std::vector<float> Generator::generateSine(const uint32_t numSamples, float amplitude, bool signedSamples)
{
	std::vector<float> samples;
	samples.reserve(numSamples);

	const float step = 3.14159265358979323846f * 2.0f / (float)numSamples;
	for (uint32_t i = 0; i < numSamples; ++i)
	{
		float sample = amplitude * sin(i * step);
		if (!signedSamples)
			sample += amplitude;

		samples.push_back(sample);
	}

	return samples;
}

std::vector<float> Generator::generateSquare(const uint32_t numSamples, float amplitude, bool signedSamples)
{
	std::vector<float> samples(numSamples, signedSamples ? -amplitude : 0.0f);

	const float dutyCycle = 0.5f;
	for (uint32_t i = 0, n = static_cast<uint32_t>(numSamples * dutyCycle + 0.5f); i < n; ++i)
		samples[i] = signedSamples ? amplitude : amplitude * 2.0f;

	return samples;
}

std::vector<float> Generator::generateTriangle(const uint32_t numSamples, float amplitude, bool signedSamples)
{
	std::vector<float> samples;
	samples.reserve(numSamples);

	const float tip = 0.2f;
	const float startY = signedSamples ? -amplitude : 0, tipY = signedSamples ? amplitude : amplitude * 2.0f;
	const auto tipX = static_cast<uint32_t>(numSamples * tip + 0.5f);
	const float kRising = (tipY - startY) / tipX, kFalling = (startY - tipY) / (numSamples - tipX);
	const float bRising = signedSamples ? -amplitude : 0.0f;
	const float bFalling = startY - kFalling * numSamples;
	for (uint32_t x = 0; x < numSamples; ++x)
	{
		// y = kx + b
		if (x < tipX)
			samples.push_back(kRising * x + bRising);
		else
			samples.push_back(kFalling * x + bFalling);
	}

	return samples;
}
