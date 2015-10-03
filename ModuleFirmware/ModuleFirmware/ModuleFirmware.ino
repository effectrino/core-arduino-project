#include <Arduino.h>
#include <StandardCplusplus.h>
#include <MIDI.h>
#include <duino-tools.h>
//#include <SoftwareSerial.h>
#include <SPI.h>

#include <map>
#include <vector>

#include <Effectrino.h>
#include <ArduinoJson.h>


//#define MIDIrxPin 10
//#define MIDItxPin 9

// TODO
#define DEVICE_ADDRESS_PIN1 10
#define DEVICE_ADDRESS_PIN2 11
#define DEVICE_ADDRESS_PIN3 12

#include "ModuleHardwareMapperItem.h"
#include "ModuleHardwareMapper.h"
#include "ModuleEffect.h"
#include "ModuleEffectParameter.h"
#include "ModuleICRegistry.h"
#include "ConfigParser.h"
#include "Module.h"

USING_NAMESPASE_EFFECTRINO

// Set up a new serial port for MIDI
//SoftwareSerial MIDISerialPort = SoftwareSerial(MIDIrxPin, MIDItxPin);

// Initialize MIDI input/output
//MIDI_CREATE_INSTANCE(SoftwareSerial, MIDISerialPort, MIDI);

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI); // pins 18/19

// Separate class for processing module
Module module;

void setup()
{
  Debug.init(115200);
  Debug.printFreeRam();

//  Debug.benchmarkStart();
  initMIDI();

//  Debug.printFreeRam();

  if ( !module.init() )
  {
    Debug << F("Init failed!") << CRLF;
  }
  else
  {
    Debug << F("Init done!") << CRLF;
  }

//  Debug.benchmarkStop();  

  Debug.printFreeRam();
}

void initMIDI()
{
//  // Define pin modes for MIDI tx, rx:
//  pinMode(MIDIrxPin, INPUT);
//  pinMode(MIDItxPin, OUTPUT);

  // Callbacks
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandleControlChange(handleControlChange);

  // Get device channel
  uint8_t hwAddress = getDeviceChannel();
  
  Debug << F("Hardware address is ") << hwAddress << CRLF;

  // Listening to module MIDI channel (1-based)
  MIDI.begin(hwAddress + 1);

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
  MIDI.read();
}

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  Debug << F("NoteOn: ch=") << channel << F(", note=") << pitch << F(", vel=") << velocity << CRLF;
  module.noteOnEvent(pitch, velocity);
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  Debug << F("NoteOff: ch=") << channel << F(", note=") << pitch << CRLF; 
  module.noteOffEvent(pitch);
}

void handleControlChange(byte channel, byte number, byte value)
{
  Debug << F("CC: ch=") << channel << F(", n=") << number << F(", v=") << value << CRLF;

//  Debug.benchmarkStart();
  module.ccEvent(number, value);
//  Debug.benchmarkStop();
}

// TODO SysEx event handler

// void replyWithConfigSysEx()
// {
//   // Reserve space
//   char buffer[512];
// }
