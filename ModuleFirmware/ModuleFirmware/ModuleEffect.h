#ifndef MODULE_EFFECT_H_
#define MODULE_EFFECT_H_

#include <Arduino.h>
// #include <StandardCplusplus.h>
#include <Effectrino.h>

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
    ModuleHardwareMapper* hwMapper;
};

END_EFFECTRINO_NAMESPACE

#endif
