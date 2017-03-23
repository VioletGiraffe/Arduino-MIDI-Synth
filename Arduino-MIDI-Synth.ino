#include <string.h>
#include <MIDI.h>

#include "MidiHandler.h"

MIDI_CREATE_INSTANCE(USARTClass, Serial1, MIDI);
CMidiHandler& midiHandler = CMidiHandler::instance();

void setup()
{
	MIDI.setHandleNoteOn(&CMidiHandler::onNoteOn);
	MIDI.setHandleNoteOff(&CMidiHandler::onNoteOff);
	MIDI.begin();

	Serial1.print("Setup finished.");
}

void loop()
{
	MIDI.read();
}
