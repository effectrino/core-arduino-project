#ifndef MODULE_MIDI_MAPPER_H_
#define MODULE_MIDI_MAPPER_H_

#include <Arduino.h>
#include <Effectrino.h>

#include <StandardCplusplus.h>
#include <map>
#include "ModuleMIDIMapperItem.h"

USING_NAMESPASE_EFFECTRINO

BEGIN_EFFECTRINO_NAMESPACE

class ModuleMIDIMapper
{
  public:
    ModuleMIDIMapper();
    ModuleMIDIMapperItem* getItemByCC(unsigned char controlIndex);
    void setParameterByCC(unsigned char controlIndex, ModuleMIDIMapperItem *parameter);
    ModuleMIDIMapperItem* getItemByNote(unsigned char noteIndex);
    void setParameterByNote(unsigned char noteIndex, ModuleMIDIMapperItem *parameter);
  protected:
    std::map<unsigned char, ModuleMIDIMapperItem*> ccMap;
    std::map<unsigned char, ModuleMIDIMapperItem*> noteMap;
};

ModuleMIDIMapper::ModuleMIDIMapper()
{
}

ModuleMIDIMapperItem* ModuleMIDIMapper::getItemByCC(unsigned char controlIndex)
{
  return ccMap[controlIndex];
}

void ModuleMIDIMapper::setParameterByCC(unsigned char controlIndex, ModuleMIDIMapperItem *parameter)
{
  ccMap[controlIndex] = parameter;
}

ModuleMIDIMapperItem* ModuleMIDIMapper::getItemByNote(unsigned char noteIndex)
{
  return noteMap[noteIndex];
}

void ModuleMIDIMapper::setParameterByNote(unsigned char noteIndex, ModuleMIDIMapperItem *parameter)
{
  noteMap[noteIndex] = parameter;
}

END_EFFECTRINO_NAMESPACE

#endif
