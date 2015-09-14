#ifndef MODULE_IC_H_
#define MODULE_IC_H_

#include <Effectrino.h>
#include <SPI.h>

USING_NAMESPASE_EFFECTRINO
BEGIN_EFFECTRINO_NAMESPACE

class ModuleIC {

  public:
    ModuleIC(const byte speedInMHz, const byte csPin, const bool invCS)
      : SPISpeed(speedInMHz * 1000000), CSPin(csPin), inverseCS(invCS) {};

    virtual void setChannelValue(byte channel, int value) = 0;

  protected:
    const byte CSPin;
    const byte inverseCS;
    const uint32_t SPISpeed;
    void sendData(byte data[]);
    void setCS(bool value);
  
};

inline void ModuleIC::sendData(byte data[])
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
    digitalWrite(this->CSPin, ((value == LOW) ? HIGH : LOW));
  else
    digitalWrite(this->CSPin, value);
}

END_EFFECTRINO_NAMESPACE

#endif
