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

#include "ModuleProcessor.h"
#include "EffectParameter.h"
#include "ModuleICRegistry.h"
#include "ConfigParser.h"

// Hardware drivers list
//#include "ICs.h"

// TODO
#define DEVICE_ADDRESS_PIN0 2
#define DEVICE_ADDRESS_PIN1 3
#define DEVICE_ADDRESS_PIN2 4

USING_NAMESPASE_EFFECTRINO

// Set up a new serial port for MIDI
SoftwareSerial MIDISerialPort = SoftwareSerial(MIDIrxPin, MIDItxPin);

// Initialize MIDI input/output
MIDI_CREATE_INSTANCE(SoftwareSerial, MIDISerialPort, MIDI);

// const byte potCSPin = 2;
// const bool potCSInverse = true;
// const byte potSpeed = 10;

// TODO remove
// ModuleIC * ad8403 = ModuleICFactory::create("AD8403", potSpeed, potCSPin, potCSInverse);

// Separate class for processing module
ModuleProcessor moduleProcessor;

void setup()
{
  initDebug(true);
  
  initMIDI();

  if ( !moduleProcessor.init() )
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
	
  // Listening to module channel
  MIDI.begin(getDeviceChannel());

  // Disable MIDI Thru for bidirectional communication
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
  // ad8403->setChannelValue(0, 255);
  // delay(100);
  // ad8403->setChannelValue(0, 0);
  // delay(100);
}

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  // Debug << "NoteOn " << channel << ", " << pitch << ", " << velocity;
  moduleProcessor.noteOnEvent(pitch, velocity);
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  // Debug << "NoteOff " << channel << ", " << pitch << ", " << velocity; 
  moduleProcessor.noteOffEvent(pitch);
}

void handleControlChange(byte channel, byte number, byte value)
{
  // Debug << "ControlChange " << channel << ", " << number << ", " << value;
  moduleProcessor.ccEvent(number, value);
}

// TODO SysEx event handler

// void replyWithConfigSysEx()
// {
//   // Reserve space
//   char buffer[512];

//   midiMapper.makeConfig(buffer);
// }

//ModuleIC * moduleICFactory(String codename, const byte SPISpeed, const byte CSPin, const bool inverseCS = 0)
//{
//  return ModuleICFactory::create(codename, SPISpeed, CSPin, inverseCS);
//}
