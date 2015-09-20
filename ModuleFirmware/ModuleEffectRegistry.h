#ifndef MODULE_EFFECT_REGISTRY_H_
#define MODULE_EFFECT_REGISTRY_H_

#include <Arduino.h>
#include <Effectrino.h>

#include <StandardCplusplus.h>
#include <map>
#include "ModuleEffect.h"

USING_NAMESPASE_EFFECTRINO

BEGIN_EFFECTRINO_NAMESPACE

class ModuleEffectRegistry
{
  public:
    ModuleEffectRegistry();
    ModuleEffect* getEffectByIndex(unsigned char effectIndex);
    void setEffectByIndex(unsigned char effectIndex, ModuleEffect *effect);
  protected:
    std::map<unsigned char, ModuleEffect*> fxMap;
};

ModuleEffectRegistry::ModuleEffectRegistry()
{
}

ModuleEffect* ModuleEffectRegistry::getEffectByIndex(unsigned char effectIndex)
{
  return fxMap[effectIndex];
}

void ModuleEffectRegistry::setEffectByIndex(unsigned char effectIndex, ModuleEffect *effect)
{
  fxMap[effectIndex] = effect;
}

END_EFFECTRINO_NAMESPACE

#endif
