#ifndef MODULE_EFFECT_PARAMETER_HARDWARE_BINDING_H_
#define MODULE_EFFECT_PARAMETER_HARDWARE_BINDING_H_

#include <Arduino.h>
#include <Effectrino.h>


USING_NAMESPASE_EFFECTRINO

BEGIN_EFFECTRINO_NAMESPACE

struct ModuleEffectParameterHardwareBinding {
    unsigned char icIndex;
    unsigned char channelIndex;
};

END_EFFECTRINO_NAMESPACE

#endif