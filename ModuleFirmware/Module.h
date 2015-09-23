#ifndef MODULE_H_
#define MODULE_H_

#include <ArduinoJson.h>
#include <Effectrino.h>
#include <duino-tools.h>
// #include <MIDI.h>

#include "ConfigParser.h"
#include "ModuleHardwareMapper.h"
#include "ModuleHardwareMapperItem.h"
#include "ModuleIC.h"
#include "ModuleICFactory.h"
#include "ModuleICRegistry.h"
#include "ModuleEffect.h"
#include "ModuleEffectParameter.h"
#include "ModuleEffectRegistry.h"


USING_NAMESPASE_EFFECTRINO
BEGIN_EFFECTRINO_NAMESPACE

class Module {

  // ArduinoJson jsonObject;
  public:
    bool init();
    bool parseJSON(char* input);

    void noteOnEvent(const byte pitch, const byte velocity);
  	void noteOffEvent(const byte pitch);
  	void ccEvent(const byte control, const byte value);

    void selectEffectByIndex(unsigned char fxIndex);

  protected:
    // Pointer to current effect
    ModuleEffect* currentEffect = (ModuleEffect*)NULL; 

    // Effects instances
    ModuleEffectRegistry fxRegistry;

    // Mapper for module hardware
    ModuleICRegistry icRegistry;

    ModuleHardwareMapper* getHardwareMapper();

};

inline bool Module::init()
{
  // TODO get JSON config
  // char* moduleConfig = this->getConfig();

  #include "TestJSONConfig.h"

  Debug << F("Free RAM after JSON string include") << CRLF;
  Debug.printFreeRam();

  if ( !this->parseJSON(testJSONConfig) )
    return false;

  // Select first effect
  this->selectEffectByIndex(0);

  Debug << F("Free RAM after parsing config") << CRLF;
  Debug.printFreeRam();

  return true;
}

inline bool Module::parseJSON(char* input)
{
  ConfigParser parser(this->icRegistry, this->fxRegistry);

  return parser.process(input);
}

// void Module::parseJSON(const Stream &input)
// {
//   // TODO someday
// }

inline void Module::selectEffectByIndex(unsigned char fxIndex)
{
  ModuleEffect* fx = fxRegistry.getEffectByIndex(fxIndex);

  // Exit if no effect found
  if ( !fx )
    return;

  currentEffect = fx;

  // Custom hardware init after effect selection 
  currentEffect->initHardware();
}

inline void Module::noteOnEvent(const byte pitch, const byte velocity)
{
  // // Exit if no fx selected
  // if ( !this->currentEffect )
  //   return;

  // ModuleHardwareMapperItem* parameter = this->currentEffect->hwMapper.getItemByNote(pitch);

  // if ( !parameter )
  //   return;

  // // TODO process parameter on
}

inline void Module::noteOffEvent(const byte pitch)
{
  // // Exit if no fx selected
  // if ( !this->currentEffect )
  //   return;

  // ModuleHardwareMapperItem* parameter = this->currentEffect->hwMapper.getItemByNote(pitch);

  // if ( !parameter )
  //   return;

  // // TODO process parameter off
}


/**
  * TODO Maybe create ONE MIDI event handler with switch-case operator
  */


inline void Module::ccEvent(const byte control, const byte value)
{
  ModuleHardwareMapper* mapper = this->getHardwareMapper();

  // Exit if no mapper
  if ( !mapper )
    return;

  ModuleHardwareMapperItem* item = mapper->getItemByCC(control);

  // Exit if no item assigned to CC
  if ( !item )
    return;

  // Process hardware bindings
  item->process(icRegistry, value);
}

/**
  * Returns instance of MIDI mapper linked to current effect
  *
  * @return ModuleHardwareMapper*|NULL
  */
inline ModuleHardwareMapper* Module::getHardwareMapper()
{
  if ( !this->currentEffect )
    return (ModuleHardwareMapper*)NULL;

  return this->currentEffect->getHardwareMapper();
}

END_EFFECTRINO_NAMESPACE

#endif
