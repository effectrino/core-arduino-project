#ifndef MODULE_EFFECT_H_
#define MODULE_EFFECT_H_

#include <Arduino.h>
#include <Effectrino.h>

#include <StandardCplusplus.h>
#include <map>

#include "ModuleHardwareMapper.h"

USING_NAMESPASE_EFFECTRINO

BEGIN_EFFECTRINO_NAMESPACE

class ModuleEffect
{
  public:
    ModuleEffect();
    void initHardware();
    ModuleHardwareMapper* getHardwareMapper();

  protected:  
    // Mapper for linking MIDI events to effect parameters
    ModuleHardwareMapper* hwMapper; // = new ModuleHardwareMapper();
};

ModuleEffect::ModuleEffect()
{
  this->hwMapper = new ModuleHardwareMapper();
}

void ModuleEffect::initHardware()
{
  // TODO custom hardware initialization after changing effect (make switching, setup parameters, etc)
}

inline ModuleHardwareMapper* ModuleEffect::getHardwareMapper()
{
  return this->hwMapper;
}


END_EFFECTRINO_NAMESPACE

#endif
