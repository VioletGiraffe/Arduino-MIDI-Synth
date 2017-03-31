#include "squaregenerator.h"

std::vector<float> SquareGenerator::generate(const uint32_t numSamples, float amplitude, bool signedSamples)
{
	std::vector<float> samples(numSamples, signedSamples ? -amplitude : 0.0f);

	const float dutyCycle = 0.5f;
	for (uint32_t i = 0, n = static_cast<uint32_t>(numSamples * dutyCycle + 0.5f); i < n; ++i)
		samples[i] = signedSamples ? amplitude : amplitude * 2.0f;

	return samples;
}

const char* SquareGenerator::name() const
{
	return "Square";
}
