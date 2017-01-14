#include <Arduino.h>
// #include <StandardCplusplus.h>
#include <MIDI.h>
#include <duino-tools.h>
#include <SoftwareSerial.h>
// #include <SPI.h>
#include "FS.h" // SPIFFS at esp8266

// #include <map>
// #include <vector>
#include <string>

#include <Effectrino.h>
#include <ArduinoJson.h>


#define MIDIrxPin 0 // 10
#define MIDItxPin 16 // 9

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
SoftwareSerial MIDISerialPort = SoftwareSerial(MIDIrxPin, MIDItxPin);

// Initialize MIDI input/output
MIDI_CREATE_INSTANCE(SoftwareSerial, MIDISerialPort, MIDI);

// MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI); // pins 18/19

// Separate class for processing module
Module module;

void setup()
{
  Debug.init(115200);
  delay(3000);
  Debug << F("Greeting!") << CRLF;
  Debug.printFreeRam(F("initial"));

  // Debug.benchmarkStart();
  initMIDI();

  if ( !moduleInit() ) {
    Debug << F("Init failed!") << CRLF;
  } else {
    Debug << F("Init done!") << CRLF;
  }

  Debug.printFreeRam(F("after module init"));
  //  Debug.benchmarkStop();
}

bool moduleInit()
{
  // TODO get JSON config
  // char* moduleConfig = this->getConfig();

  Debug.printFreeRam(F("before init from string"));

  if (!initModuleFromFsStream()) {
    return false;
  }

  Debug.printFreeRam(F("after init from string"));

  // Select first effect
  module.selectEffectByIndex(0);

  return true;
}

bool initModuleFromFsStream()
{
  Debug.printFreeRam(F("before SPIFFS reading"));

  if (!SPIFFS.begin()) {
    Debug << F("SPIFFS init failed") << CRLF;
    return false;
  }

  // Serial.println("");
  // Serial.println("Reading SPIFFS root directory");
  //
  // Dir dir = SPIFFS.openDir("/");
  // while (dir.next()) {
  //     Serial.print(dir.fileName() + " is ");
  //     File f = dir.openFile("r");
  //     Serial.println(f.size());
  // }
  Debug.printFreeRam(F("after SPIFFS init"));

  Debug << F("Reading config from SPIFFS root directory") << CRLF;

  File file = SPIFFS.open("/config.json", "r");

  if (!file) {
      Debug << F("file open failed") << CRLF;
      return false;
  }

  Debug.printFreeRam(F("after SPIFFS init"));

  Debug << F("Config file size is ") << file.size() << CRLF;
  // Debug << F("JSON config is") << CRLF << testJSONConfig << CRLF;

  if ( !module.parseJSON(file) ) {
    file.close();
    return false;
  }

  Debug.printFreeRam(F("after parsing config"));

  file.close();
  return true;
}

void downloadConfig()
{
  // TODO
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
  return 0;
//  HardwareAddressDetector hwDetector;

  // TODO set correct pins
//  return hwDetector.get(DEVICE_ADDRESS_PIN1, DEVICE_ADDRESS_PIN2, DEVICE_ADDRESS_PIN3);
}

void loop()
{
  // Debug << F("heartbeat") << CRLF;
  // Debug.printFreeRam();
  delay(1000);
  // Process MIDI stream
  // MIDI.read(); TODO
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
