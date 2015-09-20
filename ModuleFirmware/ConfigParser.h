#ifndef CONFIG_PARSER_H_
#define CONFIG_PARSER_H_

#include <Arduino.h>
#include <Effectrino.h>
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
    ModuleIC* moduleICFactory(String codename, const byte SPISpeed, const byte CSPin, const bool inverseCS);
};

ConfigParser::ConfigParser(ModuleICRegistry& icR, ModuleEffectRegistry& fxR) : icRegistry(icR), fxRegistry(fxR) {}

inline boolean ConfigParser::process(char* input)
{
  const char hardwareKey[] = "hw";
  const char effectsKey[] = "effects";

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

inline boolean ConfigParser::parseHardware(JsonArray& source)
{
  const char partNumberKey[] = "pn";
  const char spiSpeedKey[] = "speed";
  const char csPinKey[] = "cs";
  const char inverseCSKey[] = "invCS";

  char icIndex = 0;

  for (JsonArray::iterator it = source.begin(); it != source.end(); ++it)
  {
    JsonObject& icSource = *it; //.as<JsonObject&>

    if ( icSource == JsonObject::invalid() )
      return false;

    if ( !icSource.containsKey(partNumberKey) )
      return false;

    if ( !icSource.containsKey(spiSpeedKey) )
      return false;

    if ( !icSource.containsKey(csPinKey) )
      return false;

    if ( !icSource.containsKey(inverseCSKey) )
      return false;

    // Part number
    String pn = icSource[partNumberKey];

    // SPI speed, MHz
    const unsigned char spiSpeed = icSource[spiSpeedKey].as<unsigned char>();

    // CS pin
    const unsigned char csPin = icSource[csPinKey].as<unsigned char>();

    // Inverse CS
    const unsigned char inverseCS = icSource[inverseCSKey].as<bool>();

    // Check all data
    if ( !pn || !spiSpeed || !csPin )
      return false;

    // Create IC instance
    ModuleIC* icInstance = this->moduleICFactory(pn, spiSpeed, csPin, inverseCS);

    // TODO Add channels data if exists

    // Add IC instance to registry
    icRegistry.setICByIndex(icIndex, icInstance);

    icIndex++;
  }

  return true;
}

inline boolean ConfigParser::parseEffects(JsonArray& source)
{
    // TODO Parse parameters

      // TODO Parse hardware bindings

  return true;
}

inline ModuleIC* ConfigParser::moduleICFactory(String codename, const byte SPISpeed, const byte CSPin, const bool inverseCS)
{
  return ModuleICFactory::create(codename, SPISpeed, CSPin, inverseCS);
}

END_EFFECTRINO_NAMESPACE

#endif
