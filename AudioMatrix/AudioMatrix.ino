#include <Arduino.h>
#include <Wire.h>
#include <Effectrino.h>
#include <tools.h>

#include <AudioMatrixProtocol.h>
#include <AudioMatrixMessage.h>

// Fake dependencies (for hacking build process)
#include <MIDI.h>
#include <SoftwareSerial.h>


USING_NAMESPASE_EFFECTRINO


// Setup Matrix Protocol
AudioMatrixProtocol AMP(Wire);

const byte PORTD_MASK = B01111100;
const byte PORTC_MASK = B00001111;
const byte PORTB_MASK = B00000111;

const int CS1_PIN = 3;
const int CS2_PIN = 2;
const int DATA_PIN = 4;
const int STROBE_PIN = 5;
const int RESET_PIN = 6;

const int LED_PIN = 13;

void setup()
{
	// For debugging
	initConsole();

	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);

	// Setup I2C bus
	Wire.onReceive(receiveEvent); 		// Register event
	Wire.begin(AMP.getI2CAddress());	// Join i2c bus

	// Enable ports output
	DDRD |= PORTD_MASK;
	DDRC |= PORTC_MASK;
	DDRB |= PORTB_MASK;

	// Drop all address pins to LOW
	resetAddressPins();

	// Drop all CS`es to LOW
	digitalWrite(CS1_PIN, LOW);
	digitalWrite(CS2_PIN, LOW);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int eventLength)
{
	digitalWrite(LED_PIN, HIGH);

	// Console << "\r\n\r\nI2C receive event\r\n";

	// Allow multiple messages at once
	while(Wire.available())
	{
		receiveMessage();
	}

	digitalWrite(LED_PIN, LOW);
}

/**
	*	Process single message
	*/
void receiveMessage()
{
	AudioMatrixMessage msg = AMP.receiveMessage();

	if ( !msg ) {
		// Console << "Incorrect message received" << "\r\n";
		return;
	}

	// Console << "CMD = " << msg.getCommand() << "\r\n";

	if ( msg.isReset() )
	{
		// Reset whole matrix
		resetMatrix();
	}
	else if ( msg.isOn() )
	{
		// Enable one crosspoint switch
		setPoint(msg.getX(), msg.getY(), true);
	}
	else if ( msg.isOff() )
	{
		// Disable one crosspoint switch
		setPoint(msg.getX(), msg.getY(), false);
	}
}

void resetAddressPins()
{
	// Drop all address lines to 0 (x and y)
	PORTC &= ~PORTC_MASK;
	PORTB &= ~PORTB_MASK;
}

/**
	*	Setting/resetting one crosspoint switch
	*/
void setPoint(int x, int y, bool value)
{
	resetAddressPins();

	// Set proper values to ports
	PORTC |= ( x & PORTC_MASK );
	PORTB |= ( y & PORTB_MASK );

	// Set proper CS (detect from y-value)
	int CS_PIN = ( y <= 7 ) ? CS1_PIN : CS2_PIN; 
	digitalWrite(CS_PIN, HIGH);

	// Strobe data 
	digitalWrite(DATA_PIN, value ? HIGH : LOW);
	digitalWrite(STROBE_PIN, HIGH);
	digitalWrite(STROBE_PIN, LOW);

	// Drop CS to LOW
	digitalWrite(CS_PIN, LOW);
}

/**
  *	Switch off all crosspoints
  */
void resetMatrix()
{
	// Console << "Resetting matrix";

	digitalWrite(RESET_PIN, HIGH);
	digitalWrite(RESET_PIN, LOW);
}

/**
  *	Main loop
  */
void loop()
{
	// Empty waiting loop
	delay(100);

	// TEST CASE
	// testCaseOne(4);
	// testCaseFour();
	// testCaseTwo();

}

void testCaseOne(const int width)
{
	digitalWrite(LED_PIN, HIGH);

	resetMatrix();

	for(int y=0; y<width; y++)
	{
		for(int x=0; x<width; x++)
		{
			setPoint(x, y, true);
			delay(100);
			// setPoint(x, y, false);
		}

			// resetMatrix();
	}

	digitalWrite(LED_PIN, LOW);

	delay(1000);
}



void testCaseTwo()
{
	digitalWrite(LED_PIN, HIGH);

	resetMatrix();

	for(int x=0; x<16; x++)
	{
			setPoint(x, x, true);
			delay(150);
			// resetMatrix();
	}

	digitalWrite(LED_PIN, LOW);

	delay(1000);
}

void testCaseThree()
{
	digitalWrite(LED_PIN, HIGH);

	resetMatrix();

	for(int y=15; y>=0; y--)
	{
		for(int x=15; x>=0; x--)
		{
			setPoint(x, y, true);
			delay(100);
			// setPoint(x, y, false);
		}

			// resetMatrix();
	}

	digitalWrite(LED_PIN, LOW);

	delay(1000);
}

void testCaseFour()
{
	digitalWrite(LED_PIN, HIGH);

	resetMatrix();

	setPoint(0, 0, true);

	setPoint(0, 2, true);

	setPoint(2, 0, true);

	digitalWrite(LED_PIN, LOW);

	delay(2000);
}
