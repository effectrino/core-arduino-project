#ifndef MODULE_IC_FACTORY_H_
#define MODULE_IC_FACTORY_H_

#include <Effectrino.h>
#include "ModuleIC.h"

// Hardware drivers list
//#include "ICs.h"

// CPU`s internals
#include "ATmega328PWM.h"
  
// Digital pots
#include "AD8430.h"

USING_NAMESPASE_EFFECTRINO
BEGIN_EFFECTRINO_NAMESPACE

#define REGISTER_MODULE_IC(CODENAME) \
  if ( codename == #CODENAME ) \
    moduleIC = new ModuleIC##CODENAME();


class ModuleICFactory {
  public:
    static ModuleIC * create(String codename, const byte SPISpeed, const byte CSPin, const bool inverseCS);
};

inline ModuleIC * ModuleICFactory::create(String codename, const byte SPISpeed, const byte CSPin, const bool inverseCS)
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

END_EFFECTRINO_NAMESPACE

#endif
