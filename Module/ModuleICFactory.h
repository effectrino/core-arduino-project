#ifndef MODULE_IC_FACTORY_H_
#define MODULE_IC_FACTORY_H_

#include <Effectrino.h>
#include "ModuleIC.h"
//#include "ModuleICList.h"

#include "ModuleICAD8430.h"


USING_NAMESPASE_EFFECTRINO
BEGIN_EFFECTRINO_NAMESPACE

#define REGISTER_MODULE_IC(CODENAME) \
  if ( codename == #CODENAME ) \
    return new ModuleIC##CODENAME(SPISpeed, CSPin, inverseCS);

class ModuleICFactory {
  public:
    static ModuleIC * create(String codename, const byte SPISpeed, const byte CSPin, const bool inverseCS);
};

inline ModuleIC * ModuleICFactory::create(String codename, const byte SPISpeed, const byte CSPin, const bool inverseCS) {

  REGISTER_MODULE_IC(AD8430);

  return (ModuleIC*)NULL;
}

END_EFFECTRINO_NAMESPACE

#endif
