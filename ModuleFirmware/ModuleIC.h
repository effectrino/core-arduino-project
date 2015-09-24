#ifndef MODULE_IC_H_
#define MODULE_IC_H_

#include <Effectrino.h>
#include <SPI.h>

USING_NAMESPASE_EFFECTRINO
BEGIN_EFFECTRINO_NAMESPACE

class ModuleIC {

  public:
//    ModuleIC(const byte speedInMHz, const byte csPin, const bool invCS)
//      : SPISpeed(speedInMHz * 1000000), CSPin(csPin), inverseCS(invCS) {};

    ModuleIC * setCSPin(byte pin);
    ModuleIC * setInverseCS(bool pin);
    ModuleIC * setSPISpeed(byte speedInMHz);
    
    // TODO set channels pinout

    virtual void setChannelValue(byte channel, int value) = 0;

  protected:
    byte CSPin;
    bool inverseCS;
    uint32_t SPISpeed;

    void sendSPIData(byte data[]);
    void setCS(bool value);
};

inline ModuleIC * ModuleIC::setCSPin(byte pin)
{
  this->CSPin = pin;
  return this;
}

inline ModuleIC * ModuleIC::setInverseCS(bool invCS)
{
  this->inverseCS = invCS;
  return this;
}

inline ModuleIC * ModuleIC::setSPISpeed(byte speedInMHz)
{
  this->SPISpeed = speedInMHz * 1000000;
  return this;
}

inline void ModuleIC::sendSPIData(byte data[])
{
  SPISettings spiSettings(SPISpeed, MSBFIRST, SPI_MODE0);
  
  // take the CS pin to select the chip
  setCS(HIGH);

  // configure SPI and start transaction
  SPI.beginTransaction(spiSettings);
  
  for (int i = 0; i < (sizeof(data)/sizeof(byte)); i++)
  {
    SPI.transfer(data[i]);
  }

  SPI.endTransaction();

  // take the CS pin to de-select the chip
  setCS(LOW);
}

inline void ModuleIC::setCS(bool value)
{
  if ( this->inverseCS )
    value = !value;

  digitalWrite(this->CSPin, ((value == LOW) ? LOW : HIGH));
}

END_EFFECTRINO_NAMESPACE

#endif
