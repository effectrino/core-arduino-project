
// #include <Arduino.h>
#include <Wire.h>
#include <MIDI.h>
#include <SoftwareSerial.h>

#include "Effectrino.h"

#define MIDIrxPin 10
#define MIDItxPin 11


USING_NAMESPACE_MIDI

// TODO Move to EEPROM config
const byte MIDIInputChannel = 10;
const bool MIDIThru = true;
const bool MIDIDirectControl = true;

// TODO EEPROM global effects register (for reserving MIDI notes and CC for every effect)

// TODO MIDI config (MIDI IN channel + MIDI Thru + allow direct access + MIDI mapping options)

// TODO current patch (MIDI notes mapping + effects list + effects stack)

// Current effects stack instance
EffectsStack stack;

// Set up a new serial port for MIDI
SoftwareSerial MIDISerialPort = SoftwareSerial(MIDIrxPin, MIDItxPin);

// Initialize MIDI input/output
MIDI_CREATE_INSTANCE(SoftwareSerial, MIDISerialPort, MIDI);


void setup()
{
    Serial.begin(9600);

	// Define pin modes for MIDI tx, rx:
  	pinMode(MIDIrxPin, INPUT);
  	pinMode(MIDItxPin, OUTPUT);

	// Init serial port	
	// MIDISerialPort.begin(31250);

	// Callbacks
	MIDI.setHandleNoteOn(handleCoreNoteOn); 
	MIDI.setHandleNoteOff(handleCoreNoteOff); 
    MIDI.setHandleControlChange(handleCoreControlChange); 
	
	// Listening to all channels
	MIDI.begin(MIDI_CHANNEL_OMNI);

	// TODO Configure MIDI Thru
    MIDI.setThruFilterMode(MIDI_NAMESPACE::Off);
}

void loop()
{
    // Call MIDI.read the fastest you can for real-time performance.
    MIDI.read();
}


// TODO
void handleCoreNoteOn(byte channel, byte pitch, byte velocity)
{
    // Do whatever you want when a note is pressed.
    // Try to keep your callbacks short (no delays ect)
    // otherwise it would slow down the loop() and have a bad impact
    // on real-time performance.

    Serial.println("NoteOn "); //"channel: " + 
    Serial.println(channel, DEC); //"channel: " + 
    Serial.println(pitch, DEC); //", note pitch: " + 
    Serial.println(velocity, DEC); //", velocity: " + 
    
    // TODO Get channel from system MIDI config
    if ( channel == MIDIInputChannel )
    {
    	// TODO Process core mapping

		// if ( stack.find(pitch) )
		// {

		// }

		// read midi config and get effect index
		// get slot number
		// 

    }
    // If direct modules control enabled
    else if ( MIDIDirectControl )
    {
    	// Process mapping messages to modules
    }
}

// TODO
void handleCoreNoteOff(byte channel, byte pitch, byte velocity)
{
    Serial.println("NoteOff"); //"channel: " + 
    Serial.println(channel, DEC); //"channel: " + 
    Serial.println(pitch, DEC); //", note pitch: " + 
    Serial.println(velocity, DEC); //", velocity: " + 

    // Do something when the note is released.
    // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.
}

void handleCoreControlChange(byte channel, byte number, byte value)
{
  Serial.println("ControlChange"); 
  Serial.println(channel, DEC); 
  Serial.println(number, DEC); 
  Serial.println(value, DEC);

}