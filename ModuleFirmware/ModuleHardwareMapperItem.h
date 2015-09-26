#ifndef MODULE_MIDI_MAPPER_ITEM_H_
#define MODULE_MIDI_MAPPER_ITEM_H_

// #include <Arduino.h>
#include <Effectrino.h>
#include <duino-tools.h>
#include <StandardCplusplus.h>
#include <vector>

#include "ModuleICRegistry.h"
#include "ModuleEffectParameterHardwareBinding.h"

USING_NAMESPASE_EFFECTRINO

BEGIN_EFFECTRINO_NAMESPACE

typedef std::vector<ModuleEffectParameterHardwareBinding*> ModuleHardwareMapperItemBindingsVector;
typedef std::vector<ModuleEffectParameterHardwareBinding*>::iterator ModuleHardwareMapperItemBindingsVectorIterator;
typedef std::vector<ModuleEffectParameterHardwareBinding*>::size_type ModuleHardwareMapperItemBindingsVectorSizeType;

class ModuleHardwareMapperItem
{
  public:
    void addBinding(ModuleEffectParameterHardwareBinding* binding);
    void process(ModuleICRegistry& icRegistry, const uint8_t);

  protected:
    ModuleHardwareMapperItemBindingsVector hwMapping;
};

END_EFFECTRINO_NAMESPACE

#endif