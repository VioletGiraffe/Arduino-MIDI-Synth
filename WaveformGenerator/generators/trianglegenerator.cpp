#include "trianglegenerator.h"

std::vector<float> TriangleGenerator::generate(const uint32_t numSamples, float amplitude, bool signedSamples)
{
	std::vector<float> samples;
	samples.reserve(numSamples);

	const float tip = _extraParameter;
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

const char* TriangleGenerator::name() const
{
	return "Triangle";
}

bool TriangleGenerator::hasExtraParameter() const
{
	return true;
}

const char* TriangleGenerator::extraParameterName() const
{
	return "Tip";
}
