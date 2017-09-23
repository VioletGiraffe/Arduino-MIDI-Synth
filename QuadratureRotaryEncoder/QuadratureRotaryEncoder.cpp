#include "QuadratureRotaryEncoder.h"

#include <Arduino.h>

QuadratureRotaryEncoder::QuadratureRotaryEncoder(int pinA, int pinB)
{
	pinMode(pinA, INPUT_PULLUP);
	pinMode(pinB, INPUT_PULLUP);

	_debouncerA.attach(pinA);
	_debouncerA.interval(4);

	_debouncerB.attach(pinB);
	_debouncerB.interval(4);
}

void QuadratureRotaryEncoder::update()
{
	_debouncerA.update();
	_debouncerB.update();

	if (_debouncerA.fell())
	{
		_listener(_debouncerB.read() != false ? CW : CCW);
	}
}
