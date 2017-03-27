#include "MidiHandler.h"

CMidiHandler& CMidiHandler::instance()
{
	return singletonInstance<CMidiHandler>();
}

void CMidiHandler::processNoteOn(byte inChannel, byte inNote, byte inVelocity)
{
  digitalWrite(LED_BUILTIN, HIGH);
}

void CMidiHandler::processNoteOff(byte inChannel, byte inNote, byte inVelocity)
{
  digitalWrite(LED_BUILTIN, LOW);
}

