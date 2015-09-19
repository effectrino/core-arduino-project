#ifndef MIDIMAPPER_H_
#define MIDIMAPPER_H_

#include <Arduino.h>
#include <Effectrino.h>

#include <StandardCplusplus.h>
#include <map>
#include "EffectParameter.h"

USING_NAMESPASE_EFFECTRINO

BEGIN_EFFECTRINO_NAMESPACE

class MIDIMapper
{
  public:
    MIDIMapper();
    EffectParameter* getEffectParameterByCC(unsigned char controlIndex);
    void bindEffectParameterToCC(unsigned char controlIndex, EffectParameter *parameter);
    EffectParameter* getEffectParameterByNote(unsigned char noteIndex);
    void bindEffectParameterToNote(unsigned char noteIndex, EffectParameter *parameter);
  protected:
    std::map<byte, EffectParameter*> ccMap;
    std::map<byte, EffectParameter*> noteMap;
};

MIDIMapper::MIDIMapper()
{
}

EffectParameter* MIDIMapper::getEffectParameterByCC(unsigned char controlIndex)
{
  return ccMap[controlIndex];
}

void MIDIMapper::bindEffectParameterToCC(unsigned char controlIndex, EffectParameter *parameter)
{
  ccMap[controlIndex] = parameter;
}

EffectParameter* MIDIMapper::getEffectParameterByNote(unsigned char noteIndex)
{
  return noteMap[noteIndex];
}

void MIDIMapper::bindEffectParameterToNote(unsigned char noteIndex, EffectParameter *parameter)
{
  noteMap[noteIndex] = parameter;
}

END_EFFECTRINO_NAMESPACE

#endif
