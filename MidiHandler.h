#pragma once

#include "SingletonHelper.h"

#include <Arduino.h>

#include <set>

class CMidiHandler
{
public:
	static CMidiHandler& instance();

	inline static void onNoteOn(byte inChannel, byte inNote, byte inVelocity)
	{
		instance().processNoteOn(inChannel, inNote, inVelocity);
	}

	inline static void onNoteOff(byte inChannel, byte inNote, byte inVelocity)
	{
		instance().processNoteOff(inChannel, inNote, inVelocity);
	}

private:
	void processNoteOn(byte inChannel, byte inNote, byte inVelocity);
	void processNoteOff(byte inChannel, byte inNote, byte inVelocity);
};

