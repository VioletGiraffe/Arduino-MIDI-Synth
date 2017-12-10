#include <DueTimer.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_SSD1306.h>
#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>

#include <string.h>
#include <MIDI.h>

#include "MidiHandler.h"
#include "FixedPoint.h"
#include "WaveformSin.h"
#include "Generator.h"
#include "QuadratureRotaryEncoder.h"

MIDI_CREATE_DEFAULT_INSTANCE()
CMidiHandler& midiHandler = CMidiHandler::instance();

//#define TFT_CS 10
//#define TFT_DC 8
//#define TFT_RST 0  // you can also connect this to the Arduino reset, in which case, set this #define pin to 0!
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

Adafruit_SSD1306 display;

#define RGB_to_565(R, G, B) static_cast<uint16_t>(((R & 0xF8) << 8) | ((G & 0xFC) << 3) | (B >> 3))

CGenerator soundGen;
constexpr uint32_t samplingRate = 24000;

#define ROT_ENC_PIN_A 11
#define ROT_ENC_PIN_B 12

QuadratureRotaryEncoder encoder(ROT_ENC_PIN_A, ROT_ENC_PIN_B);

void playSound()
{
	dac_write(soundGen.nextSample<CWaveformSin, samplingRate>(1000u));
}

int position = 0;

void setup()
{
	//MIDI.setHandleNoteOn(&CMidiHandler::onNoteOn);
	//MIDI.setHandleNoteOff(&CMidiHandler::onNoteOff);

	MIDI.setHandleNoteOn([](byte channel, byte note, byte velocity) {
		display.setTextSize(3);
		display.fillScreen(RGB_to_565(0, 0, 0));
		display.println("Note on:");
		display.println(channel);
		display.println(note);
		display.println(velocity);
	});

	MIDI.setHandleNoteOff([](byte channel, byte note, byte velocity) {
		display.setTextSize(3);
		display.fillScreen(RGB_to_565(0, 0, 0));
		display.println("Note off:");
		display.println(channel);
		display.println(note);
		display.println(velocity);
	});

	MIDI.begin();
	MIDI.turnThruOff();

	//display.initR(INITR_144GREENTAB); // initialize a ST7735S chip, 1.44" TFT (yellow tab on a chinese clone)
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false); // initialize with the I2C addr 0x3C (for the 128x64); by default, we'll generate the high voltage from the 3.3v line internally

	display.clearDisplay();
	//display.setTextColor(RGB_to_565(0, 127, 255), ST7735_BLACK);
	display.setTextColor(WHITE);

	display.setTextWrap(false);
	display.print("Waiting\nfor\nMIDI\nmessages");
	display.display();

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);

	encoder.setControlledValue(position);
	Timer2.attachInterrupt([]() {encoder.update(); }).setFrequency(2000).start();

	dac_setup();

	Timer3.attachInterrupt(&playSound).setFrequency(samplingRate).start(); // 24 kHz sampling rate
}

void dac_setup()
{
	pmc_enable_periph_clk(DACC_INTERFACE_ID); // start clocking DAC
	DACC->DACC_CR = DACC_CR_SWRST;  // reset DAC

	DACC->DACC_MR =
		0 /* No trigger, else DACC_MR_TRGEN_EN */ | DACC_MR_TRGSEL(0) |
		(0 << DACC_MR_USER_SEL_Pos) |  // select channel 0
		DACC_MR_REFRESH(0x2) |        // Refresh = DAC_CLOCK / (1024 * Fs) (https://cjpnmiscellany.wordpress.com/2015/08/20/settings-for-the-arduino-dac/)
		(24 << DACC_MR_STARTUP_Pos);  // 24 = 1536 cycles which I think is in range 23..45us since DAC clock = 42MHz

	DACC->DACC_IDR = 0xFFFFFFFF; // no interrupts
	DACC->DACC_CHER = DACC_CHER_CH0 << 0; // enable chan0
}

inline void dac_write(int val)
{
	DACC->DACC_CDR = val & 0xFFF;
}

void loop()
{
	MIDI.read();
}
