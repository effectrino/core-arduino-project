#include <Arduino.h>
#include <Wire.h>
#include <Effectrino.h>

use namespace EFFECTRINO_NAMESPACE;

// AudioMatrixProtocol * AMP = new AudioMatrixProtocol(Wire);

// Setup Matrix Protocol
AudioMatrixProtocol AMP(Wire);

const byte PORTD_MASK = B01111100;
const byte PORTC_MASK = B00001111;
const byte PORTB_MASK = B00000111;

const int CS1_PIN = 2;
const int CS2_PIN = 3;
const int DATA_PIN = 4;
const int STROBE_PIN = 5;
const int RESET_PIN = 6;


void setup()
{
	// Start serial for output
	Serial.begin(9600);

	// Wait for seril init
	while(!Serial) {}

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
	// Allow multiple messages at once
	while(Wire.available())
	{
		receiveMessage();
	}
}

/**
	*	Process single message
	*/
void receiveMessage()
{
	AudioMatrixMessage * msg = AMP.receiveMessage();

	if ( !msg ) {
		Serial.println("Incorrect message received");
		return;
	}

	Serial.println("Message received, command = " + msg->getCommand());

	if ( msg->isReset() )
	{
		// TODO Reset whole matrix
		resetMatrix();
	}
	else if ( msg->isOn() )
	{
		// Enable one crosspoint switch
		setPoint(msg->getX(), msg->getY(), true);
	}
	else if ( msg->isOff() )
	{
		// Disable one crosspoint switch
		setPoint(msg->getX(), msg->getY(), false);
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
	Serial.println("Resetting matrix");

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
}
