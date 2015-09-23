#ifndef MODULE_MIDI_MAPPER_ITEM_H_
#define MODULE_MIDI_MAPPER_ITEM_H_

#include <Arduino.h>
#include <Effectrino.h>
#include <duino-tools.h>
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

void ModuleHardwareMapperItem::addBinding(ModuleEffectParameterHardwareBinding* binding)
{
  hwMapping.push_back(binding);
}

void ModuleHardwareMapperItem::process(ModuleICRegistry& icRegistry, const uint8_t value)
{
  // Get channels count
  ModuleHardwareMapperItemBindingsVectorSizeType max = hwMapping.size();

  // Iterate over linked IC channels
  for(ModuleHardwareMapperItemBindingsVectorSizeType i = 0; i != max; i++)
  {
    // Binding
    ModuleEffectParameterHardwareBinding* binding = hwMapping[i];

    // Get IC object
    ModuleIC* ic = icRegistry.getICByIndex(binding->icIndex);

    // Warn if no IC found
    if ( !ic )
    {
      Debug << F("Wrong IC index in effect midi mapping!");
      continue;
    }

    // Set IC channel data
    ic->setChannelValue(binding->channelIndex, value);
  }
}

END_EFFECTRINO_NAMESPACE

#endif