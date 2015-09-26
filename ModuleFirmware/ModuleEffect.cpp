// #include <Arduino.h>
// #include <Effectrino.h>
#include "ModuleHardwareMapper.h"
#include "ModuleEffect.h"

// #include <StandardCplusplus.h>
// #include <map>

USING_NAMESPASE_EFFECTRINO

ModuleEffect::ModuleEffect()
{
  this->hwMapper = new ModuleHardwareMapper();
}

void ModuleEffect::initHardware()
{
  // TODO custom hardware initialization after changing effect (make switching, setup parameters, etc)
}

ModuleHardwareMapper* ModuleEffect::getHardwareMapper()
{
  return this->hwMapper;
}
