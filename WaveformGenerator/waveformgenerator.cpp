#include "waveformgenerator.h"

WaveformGenerator::~WaveformGenerator()
{
}

const char* WaveformGenerator::extraParameterName() const
{
	return nullptr;
}

bool WaveformGenerator::hasExtraParameter() const
{
	return false;
}

void WaveformGenerator::setExtraParameter(float p)
{
	_extraParameter = p;
}
