#include <Arduino.h>
#include <MIDI.h>

#include <SoftwareSerial.h>

#define MIDIrxPin 10
#define MIDItxPin 9

// TODO
#define DEVICE_ADDRESS_PIN0 2
#define DEVICE_ADDRESS_PIN1 3
#define DEVICE_ADDRESS_PIN2 4

use namespace EFFECTRINO_NAMESPACE;

// Set up a new serial port for MIDI
SoftwareSerial MIDISerialPort = SoftwareSerial(MIDIrxPin, MIDItxPin);

// Initialize MIDI input/output
MIDI_CREATE_INSTANCE(SoftwareSerial, MIDISerialPort, MIDI);

void setup()
{
  Serial.begin(9600);

  // Wait for serial init
  while(!Serial) {}

	// Define pin modes for MIDI tx, rx:
  pinMode(MIDIrxPin, INPUT);
  pinMode(MIDItxPin, OUTPUT);

	// Callbacks
	MIDI.setHandleNoteOn(handleNoteOn); 
	MIDI.setHandleNoteOff(handleNoteOff); 
	MIDI.setHandleControlChange(handleControlChange);
	
	// Listening to all channels
	MIDI.begin(getDeviceChannel());

	// Disable MIDI Thru
	MIDI.turnThruOff();
}

/**
  * TODO Get device channel from hardware switch
  */
int getDeviceChannel()
{
  // TODO Read PORT and mask it with B00000111
  return 7;
}

void loop()
{
	// Empty
	delay(100);
}

// TODO
void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  Serial.println("NoteOn "); //"channel: " + 
  Serial.println(channel, DEC); //"channel: " + 
  Serial.println(pitch, DEC); //", note pitch: " + 
  Serial.println(velocity, DEC); //", velocity: " + 

}

// TODO
void handleNoteOff(byte channel, byte pitch, byte velocity)
{
    Serial.println("NoteOff"); //"channel: " + 
    Serial.println(channel, DEC); //"channel: " + 
    Serial.println(pitch, DEC); //", note pitch: " + 
    Serial.println(velocity, DEC); //", velocity: " + 

    // Do something when the note is released.
    // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.
}

void handleControlChange(byte channel, byte number, byte value)
{
  Serial.println("ControlChange"); 
  Serial.println(channel, DEC); 
  Serial.println(number, DEC); 
  Serial.println(value, DEC);

}