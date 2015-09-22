#ifndef MODULE_MIDI_MAPPER_H_
#define MODULE_MIDI_MAPPER_H_

#include <Arduino.h>
#include <Effectrino.h>

#include <StandardCplusplus.h>
#include <map>
#include "ModuleHardwareMapperItem.h"

USING_NAMESPASE_EFFECTRINO

BEGIN_EFFECTRINO_NAMESPACE

class ModuleHardwareMapper
{
  public:
    ModuleHardwareMapper();
    ModuleHardwareMapperItem* getItemByCC(unsigned char controlIndex);
    void setParameterByCC(unsigned char controlIndex, ModuleHardwareMapperItem *parameter);
    ModuleHardwareMapperItem* getItemByNote(unsigned char noteIndex);
    void setParameterByNote(unsigned char noteIndex, ModuleHardwareMapperItem *parameter);
  protected:
    std::map<unsigned char, ModuleHardwareMapperItem*> ccMap;
    std::map<unsigned char, ModuleHardwareMapperItem*> noteMap;
};

ModuleHardwareMapper::ModuleHardwareMapper()
{
}

ModuleHardwareMapperItem* ModuleHardwareMapper::getItemByCC(unsigned char controlIndex)
{
  return ccMap[controlIndex];
}

void ModuleHardwareMapper::setParameterByCC(unsigned char controlIndex, ModuleHardwareMapperItem *parameter)
{
  ccMap[controlIndex] = parameter;
}

ModuleHardwareMapperItem* ModuleHardwareMapper::getItemByNote(unsigned char noteIndex)
{
  return noteMap[noteIndex];
}

void ModuleHardwareMapper::setParameterByNote(unsigned char noteIndex, ModuleHardwareMapperItem *parameter)
{
  noteMap[noteIndex] = parameter;
}

END_EFFECTRINO_NAMESPACE

#endif
