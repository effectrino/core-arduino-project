#include <Arduino.h>
#include <MIDI.h>
#include <duino-tools.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include <StandardCplusplus.h>
#include <Effectrino.h>


#define MIDIrxPin 10
#define MIDItxPin 9

// TODO
#define DEVICE_ADDRESS_PIN1 14
#define DEVICE_ADDRESS_PIN2 15
#define DEVICE_ADDRESS_PIN3 16

#include "ModuleEffect.h"
#include "ModuleEffectParameter.h"
#include "ModuleICRegistry.h"
#include "ConfigParser.h"
#include "Module.h"

USING_NAMESPASE_EFFECTRINO

// Set up a new serial port for MIDI
SoftwareSerial MIDISerialPort = SoftwareSerial(MIDIrxPin, MIDItxPin);

// Initialize MIDI input/output
MIDI_CREATE_INSTANCE(SoftwareSerial, MIDISerialPort, midi);

// Separate class for processing module
Module module;

void setup()
{
  initDebug(true);
  
  initMIDI();

  if ( !module.init() )
  {
    Debug << "Init failed!" << CRLF;
  }
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
	
  // Listening to module MIDI channel (1-based)
  MIDI.begin(getDeviceChannel() + 1);

  // Disable MIDI Thru for bidirectional communication
  MIDI.turnThruOff();
}

/**
  * Get device channel from hardware switch
  */
char getDeviceChannel()
{
  HardwareAddressDetector hwDetector;

  // TODO set correct pins
  return hwDetector.get(DEVICE_ADDRESS_PIN1, DEVICE_ADDRESS_PIN2, DEVICE_ADDRESS_PIN3);
}

void loop()
{
  // Process MIDI stream
  midi.read();
}

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  Debug << F("NoteOn ") << channel << F(", ") << pitch << F(", ") << velocity << CRLF;
  module.noteOnEvent(pitch, velocity);
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  Debug << F("NoteOff ") << channel << F(", ") << pitch << CRLF; 
  module.noteOffEvent(pitch);
}

void handleControlChange(byte channel, byte number, byte value)
{
  Debug << F("ControlChange event: ch=") << channel << F(", num=") << number << F(", val=") << value << CRLF;
  module.ccEvent(number, value);
}

// TODO SysEx event handler

// void replyWithConfigSysEx()
// {
//   // Reserve space
//   char buffer[512];

//   hwMapper.makeConfig(buffer);
// }
