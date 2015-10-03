#ifndef CONFIG_PARSER_H_
#define CONFIG_PARSER_H_

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <Effectrino.h>
// #include <Debug.h>
#include <ArduinoJson.h>
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
    StaticJsonBuffer<768> jsonBuffer;
    
    ModuleICRegistry& icRegistry;
    ModuleEffectRegistry& fxRegistry;

    bool parseHardware(JsonArray& source);
    bool parseEffects(JsonArray& source);
    bool parseEffectParameters(JsonArray& source, ModuleEffect* fxInstance);

    ModuleIC* moduleICFactory(String codename, const uint8_t SPISpeed, const uint8_t CSPin, const bool inverseCS);
    ModuleEffect* moduleEffectFactory();
    ModuleHardwareMapperItem* moduleHardwareMapperItemFactory();
    ModuleEffectParameterHardwareBinding* moduleEffectParameterHardwareBindingFactory(const JsonArray& data);
};

END_EFFECTRINO_NAMESPACE

#endif
