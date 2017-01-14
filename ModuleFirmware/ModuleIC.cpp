// #include <Arduino.h>
// #include <Effectrino.h>
#include <SPI.h>

#include "ModuleIC.h"

USING_NAMESPASE_EFFECTRINO

ModuleIC * ModuleIC::setCSPin(uint8_t pin)
{
  this->CSPin = pin;
  return this;
}

ModuleIC * ModuleIC::setInverseCS(bool invCS)
{
  this->inverseCS = invCS;
  return this;
}

ModuleIC * ModuleIC::setSPISpeed(uint8_t speedInMHz)
{
  this->SPISpeed = speedInMHz * 1000000;
  return this;
}

void ModuleIC::sendSPIData(uint8_t data[])
{
  SPISettings spiSettings(SPISpeed, MSBFIRST, SPI_MODE0);

  // take the CS pin to select the chip
  setCS(HIGH);

  // configure SPI and start transaction
  SPI.beginTransaction(spiSettings);

  for (unsigned int i = 0; i < (sizeof(data)/sizeof(uint8_t)); i++)
  {
    SPI.transfer(data[i]);
  }

  SPI.endTransaction();

  // take the CS pin to de-select the chip
  setCS(LOW);
}

void ModuleIC::setCS(bool value)
{
  if ( this->inverseCS )
    value = !value;

  digitalWrite(this->CSPin, ((value == LOW) ? LOW : HIGH));
}
