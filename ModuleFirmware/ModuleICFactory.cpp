// #include <Effectrino.h>
// #include "ModuleIC.h"
#include "ModuleICFactory.h"


// CPU`s internals
#include "ATmega328PWM.h"
  
// Digital pots
#include "AD8430.h"


USING_NAMESPASE_EFFECTRINO

#define REGISTER_MODULE_IC(CODENAME) \
  if ( codename == F(#CODENAME) ) \
    moduleIC = new ModuleIC##CODENAME();

ModuleIC * ModuleICFactory::create(String codename, const uint8_t SPISpeed, const uint8_t CSPin, const bool inverseCS)
{
  ModuleIC * nullValue = (ModuleIC*)NULL;
  ModuleIC * moduleIC = nullValue;

  // CPU`s internals
  REGISTER_MODULE_IC(ATmega328PWM);

  // Digital Pots
  REGISTER_MODULE_IC(AD8430);
  
  if ( moduleIC != nullValue )
  {
    moduleIC
      ->setSPISpeed(SPISpeed)
      ->setCSPin(CSPin)
      ->setInverseCS(inverseCS);
  }

  return moduleIC;
}
