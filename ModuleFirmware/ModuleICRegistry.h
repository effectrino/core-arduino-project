#ifndef MODULE_IC_REGISTRY_H_
#define MODULE_IC_REGISTRY_H_

#include <Arduino.h>
#include <Effectrino.h>
// #include <StandardCplusplus.h>
#include <map>

#include "ModuleIC.h"

USING_NAMESPASE_EFFECTRINO

BEGIN_EFFECTRINO_NAMESPACE

class ModuleICRegistry
{
  public:
    ModuleIC* getICByIndex(const unsigned char index);
    void setICByIndex(const unsigned char index, ModuleIC* ic);
    ModuleIC* invalid();
    unsigned char size();

  protected:
    std::map<unsigned char, ModuleIC*> icMap;
};

END_EFFECTRINO_NAMESPACE

#endif
