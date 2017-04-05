#pragma once

#include "FixedPoint.h"

#include <cstdint>

using Fp10bits = FixedPoint<uint32_t, 10>;

class CGenerator
{
public:
	CGenerator();

	template <class Waveform>
	uint16_t nextSample(const Waveform& waveform)
	{
		static const Fp10bits increment = 25ul; // 24000 / 600 * 25 = 1 kHz
		_phaseAccumulator += increment;
		if (_phaseAccumulator >= waveform.numSamples())
			_phaseAccumulator -= waveform.numSamples();

		return waveform[_phaseAccumulator.toInt()];
	}

private:
	Fp10bits _phaseAccumulator = 0ul;
};

