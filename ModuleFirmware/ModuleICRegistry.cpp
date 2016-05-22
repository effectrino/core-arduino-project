// #include <Arduino.h>
// #include <Effectrino.h>
// #include <map>
// #include "ModuleIC.h"

#include "ModuleICRegistry.h"

USING_NAMESPASE_EFFECTRINO

ModuleIC* ModuleICRegistry::getICByIndex(const unsigned char index)
{
  if ( !icMap.count(index) )
    return this->invalid();

  return icMap[index];
}

void ModuleICRegistry::setICByIndex(const unsigned char index, ModuleIC* ic)
{
  icMap[index] = ic;
}

unsigned char ModuleICRegistry::size()
{
  return icMap.size();
}

ModuleIC* ModuleICRegistry::invalid()
{
  return (ModuleIC*)NULL;
}
