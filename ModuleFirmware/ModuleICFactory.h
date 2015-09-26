#ifndef MODULE_IC_FACTORY_H_
#define MODULE_IC_FACTORY_H_

#include <Effectrino.h>
#include "ModuleIC.h"

BEGIN_EFFECTRINO_NAMESPACE

class ModuleICFactory {
  public:
    static ModuleIC * create(String codename, const uint8_t SPISpeed, const uint8_t CSPin, const bool inverseCS);
};

END_EFFECTRINO_NAMESPACE

#endif
