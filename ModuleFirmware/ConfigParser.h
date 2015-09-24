#ifndef CONFIG_PARSER_H_
#define CONFIG_PARSER_H_

#include <Arduino.h>
#include <Effectrino.h>
#include <Debug.h>
#include <duino-tools.h>

#include "ModuleIC.h"
#include "ModuleICFactory.h"
#include "ModuleICRegistry.h"
#include "ModuleEffect.h"
//#include "ModuleEffectFactory.h"
#include "ModuleEffectRegistry.h"

USING_NAMESPASE_EFFECTRINO

BEGIN_EFFECTRINO_NAMESPACE

class ConfigParser
{
  public:
    ConfigParser(ModuleICRegistry& icR, ModuleEffectRegistry& fxR);
    boolean process(char* input);

  protected:
    ModuleICRegistry& icRegistry;
    ModuleEffectRegistry& fxRegistry;

    boolean parseHardware(JsonArray& source);
    boolean parseEffects(JsonArray& source);
    boolean parseEffectParameters(JsonArray& source, ModuleEffect* fxInstance);

    ModuleIC* moduleICFactory(String codename, const byte SPISpeed, const byte CSPin, const bool inverseCS);
    ModuleEffect* moduleEffectFactory();
    ModuleHardwareMapperItem* moduleHardwareMapperItemFactory();
    ModuleEffectParameterHardwareBinding* moduleEffectParameterHardwareBindingFactory(const JsonArray& data);

};

ConfigParser::ConfigParser(ModuleICRegistry& icR, ModuleEffectRegistry& fxR) : icRegistry(icR), fxRegistry(fxR) {}

inline boolean ConfigParser::process(char* input)
{
  const char* hardwareKey = "hw";
  const char* effectsKey = "fx";

  DynamicJsonBuffer jsonBuffer;

  JsonObject& root = jsonBuffer.parseObject(input);

  if ( !root.success() )
 {
    Debug << F("Root parsing failed!") << CRLF;
    return false;
  }

  // Parse hardware list
  if ( !root.containsKey(hardwareKey) || !this->parseHardware(root[hardwareKey]) )
  {
    Debug << F("Hardware section is incorrect!") << CRLF;
    return false;
  }

  // Parse effects list
  if ( !root.containsKey(effectsKey) || !this->parseEffects(root[effectsKey]) )
  {
    Debug << F("Effects sections is incorrect!") << CRLF;
    return false;
  }

  return true;
}

/**
  * Parse hardware JSON array
  */
inline boolean ConfigParser::parseHardware(JsonArray& source)
{
  const char* partNumberKey = "pn";
  const char* spiSpeedKey = "speed";
  const char* csPinKey = "cs";
  const char* inverseCSKey = "invCS";
  const char* channelsKey = "channels";

  char icIndex = 0;

  for (JsonArray::iterator it = source.begin(); it != source.end(); ++it)
  {
    JsonObject& icSource = *it; //.as<JsonObject&>

    if ( icSource == JsonObject::invalid() )
    {
      Debug << F("Invalid hardware IC JSON!") << CRLF;
      return false;
    }

    if ( !icSource.containsKey(partNumberKey) )
    {
      Debug << F("No IC ") << partNumberKey << F(" key!") << CRLF;
      return false;
    }

    if ( !icSource.containsKey(spiSpeedKey) )
    {
      Debug << F("No IC ") << spiSpeedKey << F(" key!") << CRLF;
      return false;
    }

    if ( !icSource.containsKey(csPinKey) )
    {
      Debug << F("No IC ") << csPinKey << F(" key!") << CRLF;
      return false;
    }

//    if ( !icSource.containsKey(inverseCSKey) )
//    {
//      Debug << F("No IC ") << inverseCSKey << F(" key!") << CRLF;
//      return false;
//    }

    // Part number
    String pn = icSource[partNumberKey];

    // SPI speed, MHz
    const unsigned char spiSpeed = icSource[spiSpeedKey].as<unsigned char>();

    // CS pin
    const unsigned char csPin = icSource[csPinKey].as<unsigned char>();

    // Inverse CS
    const unsigned char inverseCS = icSource[inverseCSKey].as<bool>();

    // Check IC PN
    if ( !pn )
    {
      Debug << F("Invalid part number defined!") << CRLF;
      return false;
    }

    // Check SPI speed and SPI-related parameters (they must be NULL for internal modules like PWM and DAC)
    if ( spiSpeed )
    {
      // Check CS pin number
      if ( !csPin )
      {
        Debug << F("Invalid IC CS pin defined!") << CRLF;
        return false;
      }
    }

    // Create IC instance
    ModuleIC* icInstance = this->moduleICFactory(pn, spiSpeed, csPin, inverseCS);

    if ( !icSource.containsKey(channelsKey) )
    {
      // TODO Add channels data
    }

    // Add IC instance to registry
    icRegistry.setICByIndex(icIndex, icInstance);

    icIndex++;
  }

  return true;
}

/**
  * Parse effects JSON array
  */
inline boolean ConfigParser::parseEffects(JsonArray& source)
{
//  const char* labelKey = "label";
  const char* paramsKey = "params";

  char fxIndex = 0;

  // Iterate over effects
  for (JsonArray::iterator it = source.begin(); it != source.end(); ++it)
  {
    JsonObject& fxSource = *it; //.as<JsonObject&>

    if ( fxSource == JsonObject::invalid() )
    {
      Debug << F("Invalid effect definition JSON!") << CRLF;
      return false;
    }

//    if ( !fxSource.containsKey(labelKey) )
//    {
//      Debug << F("No effect [") << labelKey << F("] key!") << CRLF;
//      return false;
//    }

    if ( !fxSource.containsKey(paramsKey) )
    {
      Debug << F("No effect [") << paramsKey << F("] key!") << CRLF;
      return false;
    }

//    // Label
//    String label = fxSource[labelKey];

    // Create effect instance
    ModuleEffect* fxInstance = this->moduleEffectFactory();

    // Parse parameters
    this->parseEffectParameters(fxSource[paramsKey].as<JsonArray&>(), fxInstance);

    // Add effect instance to registry
    fxRegistry.setEffectByIndex(fxIndex, fxInstance);

    fxIndex++;
  }

  return true;
}

/**
  * Parse effect parameters JSON array
  */
inline boolean ConfigParser::parseEffectParameters(JsonArray& source, ModuleEffect* fxInstance)
{
  // const char* paramLabelKey = "label";
  const char* paramMIDIKey = "midi";
  const char* paramHardwareKey = "hw";
  const char* paramMIDIEventTypeKey = "type";
  const char* paramMIDIEventDataKey = "data";

  // Get current effect mapper object
  ModuleHardwareMapper* hwMapper = fxInstance->getHardwareMapper();

  if ( source == JsonArray::invalid() )
  {
    Debug << F("Effect parameters definition is invalid!") << CRLF;
    return false;
  }

  // Iterate over parameters
  for (JsonArray::iterator it = source.begin(); it != source.end(); ++it)
  {
    JsonObject& paramSource = *it; //.as<JsonObject&>

    if ( paramSource == JsonObject::invalid() )
    {
      Debug << F("Invalid effect definition JSON!") << CRLF;
      return false;
    }

//    if ( !paramSource.containsKey(paramLabelKey) )
//    {
//      Debug << F("No effect parameter [") << paramLabelKey << F("] key!") << CRLF;
//      return false;
//    }

    if ( !paramSource.containsKey(paramMIDIKey) )
    {
      Debug << F("No effect parameter [") << paramMIDIKey << F("] key!") << CRLF;
      return false;
    }

    if ( !paramSource.containsKey(paramHardwareKey) )
    {
      Debug << F("No effect parameter [") << paramHardwareKey << F("] key!") << CRLF;
      return false;
    }

    JsonArray& midiBinds = paramSource[paramMIDIKey].asArray();
    JsonArray& hwBinds = paramSource[paramHardwareKey].asArray();

    if ( midiBinds == JsonArray::invalid() )
    {
      Debug << F("Invalid effect parameter MIDI bindings list!") << CRLF;
      return false;
    }

    if ( hwBinds == JsonArray::invalid() )
    {
      Debug << F("Invalid effect parameter hardware bindings list!") << CRLF;
      return false;
    }

    ModuleHardwareMapperItem* mapperItem = this->moduleHardwareMapperItemFactory();

    // Iterate over hardware bindings
    for (JsonArray::iterator hwIt = hwBinds.begin(); hwIt != hwBinds.end(); ++hwIt)
    {
      JsonArray& hwBindSource = hwIt->asArray(); //.as<JsonObject&>

      if ( hwBindSource == JsonArray::invalid() )
      {
        Debug << F("Invalid effect parameter hardware binding data!") << CRLF;
        return false;
      }

      // Create binding instance
      ModuleEffectParameterHardwareBinding* binding = this->moduleEffectParameterHardwareBindingFactory(hwBindSource);

      // Add binding instance to mapper item
      mapperItem->addBinding(binding);
    }

    // Parse MIDI bindings
    for (JsonArray::iterator midiIt = midiBinds.begin(); midiIt != midiBinds.end(); ++midiIt)
    {
      JsonObject& midiSource = *midiIt; //.as<JsonObject&>

      if ( !midiSource.containsKey(paramMIDIEventTypeKey) )
      {
        Debug << F("No effect parameter MIDI binding [") << paramMIDIEventTypeKey << F("] key!") << CRLF;
        return false;
      }

      if ( !midiSource.containsKey(paramMIDIEventDataKey) )
      {
        Debug << F("No effect parameter MIDI binding [") << paramMIDIEventDataKey << F("] key!") << CRLF;
        return false;
      }

      // MIDI event type
      const char* midiEventType = midiSource[paramMIDIEventTypeKey].asString();

      // MIDI event data
      const uint32_t midiEventData = midiSource[paramMIDIEventDataKey].as<uint32_t>();

      if ( !midiEventType )
      {
        Debug << F("Invalid effect parameter MIDI binding type!") << CRLF;
        return false;
      }

      if ( !midiEventData )
      {
        Debug << F("Invalid effect parameter MIDI binding data!") << CRLF;
        return false;
      }

      if (strcmp(midiEventType, "CC") == 0)
      {
        Debug << F("Binding mapperItem to MIDI CC ") << midiEventData << CRLF;
        hwMapper->setItemByCC(midiEventData, mapperItem);
      }
      else if (strcmp(midiEventType, "NoteOn") == 0 || strcmp(midiEventType, "NoteOff") == 0)
      {
        Debug << F("Binding mapperItem to MIDI Note ") << midiEventData << CRLF;
        hwMapper->setItemByNote(midiEventData, mapperItem);
      }
      else
      {
        Debug << F("Unknown effect MIDI binding`s event type: ") << midiEventType << CRLF;
        return false;
      }
    }
  }



//    // SPI speed, MHz
//    const unsigned char spiSpeed = icSource[spiSpeedKey].as<unsigned char>();
//
//    // CS pin
//    const unsigned char csPin = icSource[csPinKey].as<unsigned char>();
//
//    // Inverse CS
//    const unsigned char inverseCS = icSource[inverseCSKey].as<bool>();
//
//    // Check IC PN
//    if ( !pn )
//    {
//      Debug << F("Invalid part number defined!") << CRLF;
//      return false;
//    }
//
//    // Check SPI speed
//    if ( !spiSpeed )
//    {
//      Debug << F("Invalid IC SPI speed defined!") << CRLF;
//      return false;
//    }
//    
//    // Check CS pin number
//    if ( !csPin )
//    {
//      Debug << F("Invalid IC CS pin defined!") << CRLF;
//      return false;
//    }

  return true;
}

inline ModuleIC* ConfigParser::moduleICFactory(String codename, const byte SPISpeed, const byte CSPin, const bool inverseCS)
{
  return ModuleICFactory::create(codename, SPISpeed, CSPin, inverseCS);
}

inline ModuleEffect* ConfigParser::moduleEffectFactory()
{
  return new ModuleEffect();
}

inline ModuleHardwareMapperItem* ConfigParser::moduleHardwareMapperItemFactory()
{
  return new ModuleHardwareMapperItem();
}

inline ModuleEffectParameterHardwareBinding* ConfigParser::moduleEffectParameterHardwareBindingFactory(const JsonArray& data)
{
  // TODO
  return new ModuleEffectParameterHardwareBinding(data[0], data[1]);
}

END_EFFECTRINO_NAMESPACE

#endif
