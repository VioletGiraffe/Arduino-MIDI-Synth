#pragma once

#include <cstddef>
#include <cstdint>

class CWaveformSin
{
public:
	size_t numSamples() const;
	inline uint16_t operator[](size_t index) const
	{
		return wavetable[index];
	}

private:
	static const uint16_t wavetable[];
};

