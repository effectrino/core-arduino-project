//#include <Effectrino.h>
#include "Module.h"

#include "ConfigParser.h"
//#include "ModuleHardwareMapper.h"
//#include "ModuleHardwareMapperItem.h"
//// #include "ModuleIC.h"
//// #include "ModuleICFactory.h"
//#include "ModuleICRegistry.h"
//#include "ModuleEffect.h"
//// #include "ModuleEffectParameter.h"
//#include "ModuleEffectRegistry.h"

USING_NAMESPASE_EFFECTRINO

// bool Module::init()
// {
//   // TODO get JSON config
//   // char* moduleConfig = this->getConfig();
//
//   Debug << F("[before init from string] ");
//   Debug.printFreeRam();
//
//   if (!this->initFromString())
//   {
//     return false;
//   }
// 
//   Debug << F("[after init from string] ");
//   Debug.printFreeRam();
//
//   // Select first effect
//   this->selectEffectByIndex(0);
//
//   return true;
// }


bool Module::parseJSON(char* input)
{
  ConfigParser parser(this->icRegistry, this->fxRegistry);

  return parser.process(input);
}

bool Module::parseJSON(Stream& input)
{
  ConfigParser parser(this->icRegistry, this->fxRegistry);

  return parser.process(input);
}

void Module::selectEffectByIndex(unsigned char fxIndex)
{
  ModuleEffect* fx = fxRegistry.getEffectByIndex(fxIndex);

  // Exit if no effect found
  if ( !fx )
    return;

  currentEffect = fx;

  // Custom hardware init after effect selection
  currentEffect->initHardware();
}

void Module::noteOnEvent(const byte pitch, const byte velocity)
{
  // // Exit if no fx selected
  // if ( !this->currentEffect )
  //   return;

  // ModuleHardwareMapperItem* parameter = this->currentEffect->hwMapper.getItemByNote(pitch);

  // if ( !parameter )
  //   return;

  // // TODO process parameter on
}

void Module::noteOffEvent(const byte pitch)
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


void Module::ccEvent(const byte control, const byte value)
{
  ModuleHardwareMapper* mapper = this->getHardwareMapper();

  // Exit if no mapper
  if ( !mapper )
  {
    Debug << F("No mapper found or no effect selected") << CRLF;
    return;
  }

  ModuleHardwareMapperItem* item = mapper->getItemByCC(control);

  // Exit if no item assigned to CC
  if ( !item )
  {
    Debug << F("No mapper item assigned to CC ") << control << CRLF;
    return;
  }

  // Process hardware bindings
  item->process(icRegistry, value);
}

/**
  * Returns instance of MIDI mapper linked to current effect
  *
  * @return ModuleHardwareMapper*|NULL
  */
ModuleHardwareMapper* Module::getHardwareMapper()
{
  if ( !this->currentEffect )
    return (ModuleHardwareMapper*)NULL;

  return this->currentEffect->getHardwareMapper();
}
