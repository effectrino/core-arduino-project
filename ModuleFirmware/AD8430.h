#ifndef AD8430_H_
#define AD8430_H_

#include <Arduino.h>
#include <Effectrino.h>
#include "ModuleIC.h"

USING_NAMESPASE_EFFECTRINO

BEGIN_EFFECTRINO_NAMESPACE

class ModuleICAD8430 : public ModuleIC
{
  public:
    void setChannelValue(byte channel, int value);
};

inline void ModuleICAD8430::setChannelValue(byte channel, int value)
{
  byte data[2] = {channel && 0x03, value && 0xFF};
  this->sendSPIData(data);
}

END_EFFECTRINO_NAMESPACE

#endif
