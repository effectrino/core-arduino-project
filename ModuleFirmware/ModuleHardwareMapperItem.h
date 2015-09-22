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

typedef std::vector<ModuleEffectParameterHardwareBinding> ModuleHardwareMapperItemBindingsVector;
typedef std::vector<ModuleEffectParameterHardwareBinding>::iterator ModuleHardwareMapperItemBindingsVectorIterator;
typedef std::vector<ModuleEffectParameterHardwareBinding>::size_type ModuleHardwareMapperItemBindingsVectorSizeType;

class ModuleHardwareMapperItem
{
  public:
    void process(ModuleICRegistry& icRegistry, const char);
    // ModuleHardwareMapperItemBindingsVectorIterator getHardwareBindingsBegin();
    // ModuleHardwareMapperItemBindingsVectorIterator getHardwareBindingsEnd();

  protected:
    ModuleHardwareMapperItemBindingsVector hwMapping;
};

void ModuleHardwareMapperItem::process(ModuleICRegistry& icRegistry, const char value)
{
  // Get channels count
  ModuleHardwareMapperItemBindingsVectorSizeType max = hwMapping.size();

  // Iterate over linked IC channels
  for(ModuleHardwareMapperItemBindingsVectorSizeType i = 0; i != max; i++)
  {
    // Binding
    ModuleEffectParameterHardwareBinding bind = hwMapping[i];

    // Get IC object
    ModuleIC* ic = icRegistry.getICByIndex(hwMapping[i].icIndex);

    // If no IC  found
    if ( !ic )
    {
      Debug << F("Wrong IC index in effect midi mapping!");
      continue;
    }

    // Set IC channel data
    ic->setChannelValue(hwMapping[i].channelIndex, value);
  }
}

// ModuleHardwareMapperItemBindingsVectorIterator ModuleHardwareMapperItem::getHardwareBindingsIterator()
// {
//   return hwMapping.begin();
// }

// ModuleHardwareMapperItemBindingsVectorSizeType ModuleHardwareMapperItem::getHardwareBindingsSize()
// {
//   return hwMapping.size();
// }

END_EFFECTRINO_NAMESPACE

#endif