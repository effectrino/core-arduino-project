#ifndef MIDIMAPPER_CC_MAP_H_
#define MIDIMAPPER_CC_MAP_H_

#include <Arduino.h>
#include <Effectrino.h>

#include "EffectParameter.h"

USING_NAMESPASE_EFFECTRINO

BEGIN_EFFECTRINO_NAMESPACE

class MIDIMapperCCMap
{
  public:
    MIDIMapperCCMap();
    void bindEffectParameter(byte index, EffectParameter * parameter);

  protected:
    EffectParameter * parameters[127];
};

MIDIMapperCCMap::MIDIMapperCCMap()
{
//  for(int i = 0; i < 128; i++)
//  {
//    parameters[i] = new EffectParameter;
//  }
}

void MIDIMapperCCMap::bindEffectParameter(byte index, EffectParameter * parameter)
{
  parameters[index] = parameter;
}

END_EFFECTRINO_NAMESPACE

#endif
