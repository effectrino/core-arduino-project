#ifndef MODULE_IC_AD8430_H_
#define MODULE_IC_AD8430_H_

USING_NAMESPASE_EFFECTRINO

#include <Arduino.h>
#include <Effectrino.h>
#include "ModuleIC.h"

BEGIN_EFFECTRINO_NAMESPACE

// (const byte speedInMHz, const byte csPin, const bool invCS)
//(speedInMHz, csPin, invCS)
class ModuleICAD8430 : public ModuleIC
{
  public:
    ModuleICAD8430(const byte speedInMHz, const byte csPin, const bool invCS) 
      : ModuleIC(speedInMHz, csPin, invCS) {}
    
    virtual void setChannelValue(byte channel, int value);
};

//ModuleICAD8430::ModuleICAD8430(const byte speedInMHz, const byte csPin, const bool invCS) 
//  : ModuleIC(speedInMHz, csPin, invCS) {};

void ModuleICAD8430::setChannelValue(byte channel, int value)
{
  byte data[] = {channel && 0x03, value && 0xFF};
  this->sendData(data);
}

END_EFFECTRINO_NAMESPACE

#endif
