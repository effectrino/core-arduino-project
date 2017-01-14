// #include <Arduino.h>
#include <Effectrino.h>
// #include <map>

#include "ModuleEffectRegistry.h"
// #include "ModuleEffect.h"

USING_NAMESPASE_EFFECTRINO

// ModuleEffectRegistry::ModuleEffectRegistry() {}

ModuleEffect* ModuleEffectRegistry::getEffectByIndex(unsigned char effectIndex)
{
  return fxMap[effectIndex];
}

void ModuleEffectRegistry::setEffectByIndex(unsigned char effectIndex, ModuleEffect *effect)
{
  fxMap[effectIndex] = effect;
}
