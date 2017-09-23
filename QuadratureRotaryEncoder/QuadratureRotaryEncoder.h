#pragma once

#include <Bounce2.h>

#include <functional>

class QuadratureRotaryEncoder
{
public:
	enum RotationDirection {CW, CCW};

	QuadratureRotaryEncoder(int pinA, int pinB);

	void setOnRotationListener(const std::function<void (RotationDirection)>& listener);

	// Recommended update interval: 0.5 ms (2 kHz)
	void update();

private:
	Bounce _debouncerA, _debouncerB;
	std::function<void(RotationDirection)> _listener = [](RotationDirection) {};
};