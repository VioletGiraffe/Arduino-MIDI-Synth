#include <Adafruit_ST7735.h>
#include <gfxfont.h>
#include <Adafruit_GFX.h>

#include <string.h>
#include <MIDI.h>

#include "MidiHandler.h"
#include "FixedPoint.h"

MIDI_CREATE_DEFAULT_INSTANCE();
CMidiHandler& midiHandler = CMidiHandler::instance();

#define TFT_CS 10
#define TFT_DC 8
#define TFT_RST 0  // you can also connect this to the Arduino reset, in which case, set this #define pin to 0!
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

#define RGB_to_565(R, G, B) static_cast<uint16_t>(((R & 0xF8) << 8) | ((G & 0xFC) << 3) | (B >> 3))

void setup()
{
	Serial.begin(115200);
	MIDI.setHandleNoteOn(&CMidiHandler::onNoteOn);
	MIDI.setHandleNoteOff(&CMidiHandler::onNoteOff);
	MIDI.begin();

	tft.initR(INITR_144GREENTAB); // initialize a ST7735S chip, 1.44" TFT, black tab
	tft.fillScreen(ST7735_BLACK);
	tft.setTextWrap(false);

	tft.setTextColor(RGB_to_565(255, 0, 10), ST7735_BLACK);
	tft.println("Hello Due");

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);

	Serial.println("Setup finished.");
}

void loop()
{
	MIDI.read();
}
