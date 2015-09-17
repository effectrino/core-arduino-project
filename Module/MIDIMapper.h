#ifndef MIDIMAPPER_H_
#define MIDIMAPPER_H_

#include <Arduino.h>
#include <Effectrino.h>

#include "MIDIMapperCCMap.h"

USING_NAMESPASE_EFFECTRINO

BEGIN_EFFECTRINO_NAMESPACE

class MIDIMapper
{
  protected:
    MIDIMapperCCMap ccMap;
};

END_EFFECTRINO_NAMESPACE

#endif
