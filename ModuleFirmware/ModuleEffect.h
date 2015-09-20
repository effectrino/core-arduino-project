#ifndef MODULE_EFFECT_H_
#define MODULE_EFFECT_H_

#include <Arduino.h>
#include <Effectrino.h>

#include <StandardCplusplus.h>
#include <map>

#include "ModuleMIDIMapper.h"

USING_NAMESPASE_EFFECTRINO

BEGIN_EFFECTRINO_NAMESPACE

class ModuleEffect
{
  public:
    // ModuleEffect();
    ModuleMIDIMapper midiMapper;
  protected:

    // Mapper for linking MIDI events to effect parameters
};

END_EFFECTRINO_NAMESPACE

#endif
