#ifndef MODULE_MIDI_MAPPER_ITEM_H_
#define MODULE_MIDI_MAPPER_ITEM_H_

#include <Arduino.h>
#include <Effectrino.h>
#include <vector>

#include "ModuleICRegistry.h"
#include "ModuleEffectParameterHardwareBinding.h"

USING_NAMESPASE_EFFECTRINO

BEGIN_EFFECTRINO_NAMESPACE

typedef std::vector<ModuleEffectParameterHardwareBinding> MIDIMapperItemHardwareBindingsVector;
typedef std::vector<ModuleEffectParameterHardwareBinding>::iterator MIDIMapperItemHardwareBindingsVectorIterator;
typedef std::vector<ModuleEffectParameterHardwareBinding>::size_type MIDIMapperItemHardwareBindingsVectorSizeType;

class ModuleMIDIMapperItem
{
  public:
    void processMapping(ModuleICRegistry& icRegistry, const char);
    // MIDIMapperItemHardwareBindingsVectorIterator getHardwareBindingsBegin();
    // MIDIMapperItemHardwareBindingsVectorIterator getHardwareBindingsEnd();

  protected:
    MIDIMapperItemHardwareBindingsVector hwMapping;
};

void ModuleMIDIMapperItem::processMapping(ModuleICRegistry& icRegistry, const char value)
{
  // Get linked hardware IC channels

  // Get channels count
  MIDIMapperItemHardwareBindingsVectorSizeType max = hwMapping.size();

  // Iterate over each channel
  for(MIDIMapperItemHardwareBindingsVectorSizeType i = 0; i != max; i++)
  {
    // Binding
    ModuleEffectParameterHardwareBinding bind = hwMapping[i];

    // Get IC object
    ModuleIC* ic = icRegistry.getICByIndex(hwMapping[i].icIndex);

    if ( !ic )
      continue;

    // Set IC channel data
    ic->setChannelValue(hwMapping[i].channelIndex, value);
  }
}

// MIDIMapperItemHardwareBindingsVectorIterator ModuleMIDIMapperItem::getHardwareBindingsIterator()
// {
//   return hwMapping.begin();
// }

// MIDIMapperItemHardwareBindingsVectorSizeType ModuleMIDIMapperItem::getHardwareBindingsSize()
// {
//   return hwMapping.size();
// }

END_EFFECTRINO_NAMESPACE

#endif