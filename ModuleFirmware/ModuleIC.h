#ifndef MODULE_IC_H_
#define MODULE_IC_H_

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <Effectrino.h>
// #include <SPI.h>

USING_NAMESPASE_EFFECTRINO
BEGIN_EFFECTRINO_NAMESPACE

class ModuleIC {

  public:
//    ModuleIC(const byte speedInMHz, const byte csPin, const bool invCS)
//      : SPISpeed(speedInMHz * 1000000), CSPin(csPin), inverseCS(invCS) {};

    ModuleIC* setCSPin(uint8_t pin);
    ModuleIC* setInverseCS(bool pin);
    ModuleIC* setSPISpeed(uint8_t speedInMHz);
    
    // TODO set channels pinout

    virtual void setChannelValue(uint8_t channel, int value) = 0;

  protected:
    uint8_t CSPin;
    bool inverseCS;
    uint32_t SPISpeed;

    void sendSPIData(uint8_t data[]);
    void setCS(bool value);
};

END_EFFECTRINO_NAMESPACE

#endif
