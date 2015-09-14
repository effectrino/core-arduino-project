#include <Arduino.h>
#include <MIDI.h>
#include <duino-tools.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Effectrino.h>

#define MIDIrxPin 10
#define MIDItxPin 9

#include "ModuleIC.h"
#include "ModuleICFactory.h"

// TODO
#define DEVICE_ADDRESS_PIN0 2
#define DEVICE_ADDRESS_PIN1 3
#define DEVICE_ADDRESS_PIN2 4

USING_NAMESPASE_EFFECTRINO

// Set up a new serial port for MIDI
SoftwareSerial MIDISerialPort = SoftwareSerial(MIDIrxPin, MIDItxPin);

// Initialize MIDI input/output
MIDI_CREATE_INSTANCE(SoftwareSerial, MIDISerialPort, MIDI);

const byte potCSPin = 2;
const bool potCSInverse = true;
const byte potSpeed = 10;

ModuleIC * ad8403 = ModuleICFactory::create("AD8403", potSpeed, potCSPin, potCSInverse);

void setup()
{
  initDebug(true);
  
  initMIDI();
}

void initMIDI()
{
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

  // TODO remove  
  ad8403->setChannelValue(0, 255);
  delay(100);
  ad8403->setChannelValue(0, 0);
  delay(100);
}

// TODO
void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  Debug << "NoteOn " << channel << ", " << pitch << ", " << velocity; 
//  Serial.println("NoteOn "); //"channel: " + 
//  Serial.println(channel, DEC); //"channel: " + 
//  Serial.println(pitch, DEC); //", note pitch: " + 
//  Serial.println(velocity, DEC); //", velocity: " + 
}

// TODO
void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  Debug << "NoteOff " << channel << ", " << pitch << ", " << velocity; 
//    Serial.println("NoteOff"); //"channel: " + 
//    Serial.println(channel, DEC); //"channel: " + 
//    Serial.println(pitch, DEC); //", note pitch: " + 
//    Serial.println(velocity, DEC); //", velocity: " + 

    // Do something when the note is released.
    // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.
}

void handleControlChange(byte channel, byte number, byte value)
{
  Debug << "ControlChange " << channel << ", " << number << ", " << value; 

//  Serial.println("ControlChange"); 
//  Serial.println(channel, DEC); 
//  Serial.println(number, DEC); 
//  Serial.println(value, DEC);
}

//ModuleIC * moduleICFactory(String codename, const byte SPISpeed, const byte CSPin, const bool inverseCS = 0)
//{
//  return ModuleICFactory::create(codename, SPISpeed, CSPin, inverseCS);
//}

