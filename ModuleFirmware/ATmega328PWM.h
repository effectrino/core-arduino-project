#ifndef ATMEGA328PWM_H_
#define ATMEGA328PWM_H_

#include <Arduino.h>
#include <Effectrino.h>
#include "ModuleIC.h"

USING_NAMESPASE_EFFECTRINO

BEGIN_EFFECTRINO_NAMESPACE

class ModuleICATmega328PWM : public ModuleIC
{
  public:
    void setChannelValue(byte channel, int value);
};

inline void ModuleICATmega328PWM::setChannelValue(byte channel, int value)
{
  // Channel to output # mapping
  // TODO move to config
  const byte channelPins[] = {3, 5, 6, 9, 10, 11};

  analogWrite(channelPins[channel], value);
}

END_EFFECTRINO_NAMESPACE

#endif
