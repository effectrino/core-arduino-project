#ifndef MODULE_IC_REGISTRY_H_
#define MODULE_IC_REGISTRY_H_

#include <Arduino.h>
#include <Effectrino.h>
#include "ModuleIC.h"

#include <map>

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

inline ModuleIC* ModuleICRegistry::getICByIndex(const unsigned char index)
{
  if ( !icMap.count(index) )
    return this->invalid();

  return icMap[index];
}

inline void ModuleICRegistry::setICByIndex(const unsigned char index, ModuleIC* ic)
{
  icMap[index] = ic;
}

inline unsigned char ModuleICRegistry::size()
{
  return icMap.size();
}

inline ModuleIC* ModuleICRegistry::invalid()
{
  return (ModuleIC*)NULL;
}

END_EFFECTRINO_NAMESPACE

#endif
