// #include <Arduino.h>
// #include <Effectrino.h>
// #include <duino-tools.h>
// #include <vector>

#include "ModuleHardwareMapperItem.h"

// #include "ModuleICRegistry.h"
// #include "ModuleEffectParameterHardwareBinding.h"

USING_NAMESPASE_EFFECTRINO

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
