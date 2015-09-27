#include <Arduino.h>

static const int SDI_PIN 	= 2; 	// PB2 / TINY pin 7 (SCK)
static const int CLK_PIN 	= 1; 	// PB1 / TINY pin 6 (MISO)
static const int LE_PIN 	= 3;	// PB3 / TINY pin 2 (PCINT3)

void setup()
{
	pinMode(SDI_PIN, OUTPUT);
	pinMode(CLK_PIN, OUTPUT);
	pinMode(LE_PIN, OUTPUT);

	digitalWrite(SDI_PIN, LOW);
	digitalWrite(CLK_PIN, LOW);
	digitalWrite(LE_PIN, LOW);
}

void loop()
{
	int value = 1;

	for(int i=0; i<16 ; i++)
	{
//		sendValue(0);
    // delayMicroseconds(100);

		sendValue(value);
    // delay(20);
    // delayMicroseconds(50);
    value = value << 1;
	}
}

void sendValue(int value)
{
	shiftOut(SDI_PIN, CLK_PIN, MSBFIRST, byte(value >> 8));
	shiftOut(SDI_PIN, CLK_PIN, MSBFIRST, byte(value));

	digitalWrite(LE_PIN, HIGH);
	digitalWrite(LE_PIN, LOW);
}
