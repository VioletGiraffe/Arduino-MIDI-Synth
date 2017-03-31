#include "waveformgenerator.h"

WaveformGenerator::~WaveformGenerator()
{
}

const char* WaveformGenerator::extraParameterName() const
{
	return nullptr;
}

float WaveformGenerator::extraParameter() const
{
	return _extraParameter;
}

bool WaveformGenerator::hasExtraParameter() const
{
	return false;
}

void WaveformGenerator::setExtraParameter(float p)
{
	_extraParameter = p;
}
