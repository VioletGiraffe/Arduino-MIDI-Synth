#pragma once

#include <cstdint>
#include <vector>

class WaveformGenerator
{
public:
	virtual ~WaveformGenerator();

	virtual std::vector<float> generate(const uint32_t numSamples, float amplitude = 1.0f, bool signedSamples = false) = 0;
	virtual const char* name() const = 0;

	virtual bool hasExtraParameter() const;
	virtual const char* extraParameterName() const;

	float extraParameter() const;
	void setExtraParameter(float p);

protected:
	float _extraParameter = 0.1f;
};
