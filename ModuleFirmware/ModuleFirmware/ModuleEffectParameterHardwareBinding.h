#ifndef MODULE_EFFECT_PARAMETER_HARDWARE_BINDING_H_
#define MODULE_EFFECT_PARAMETER_HARDWARE_BINDING_H_

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <Effectrino.h>


USING_NAMESPASE_EFFECTRINO

BEGIN_EFFECTRINO_NAMESPACE

class ModuleEffectParameterHardwareBinding {
  public:
    ModuleEffectParameterHardwareBinding(uint8_t icI, uint8_t chI);
    const uint8_t icIndex;
    const uint8_t channelIndex;
};

inline ModuleEffectParameterHardwareBinding::ModuleEffectParameterHardwareBinding(uint8_t icI, uint8_t chI) : icIndex(icI), channelIndex(chI) {}

END_EFFECTRINO_NAMESPACE

#endif
