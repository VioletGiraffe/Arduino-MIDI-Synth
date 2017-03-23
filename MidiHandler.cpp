#include "MidiHandler.h"

CMidiHandler& CMidiHandler::instance()
{
	return singletonInstance<CMidiHandler>();
}

void CMidiHandler::processNoteOn(byte inChannel, byte inNote, byte inVelocity)
{

}

void CMidiHandler::processNoteOff(byte inChannel, byte inNote, byte inVelocity)
{

}

