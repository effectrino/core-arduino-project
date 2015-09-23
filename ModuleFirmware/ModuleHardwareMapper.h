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
    void setItemByCC(unsigned char controlIndex, ModuleHardwareMapperItem *item);
    ModuleHardwareMapperItem* getItemByNote(unsigned char noteIndex);
    void setItemByNote(unsigned char noteIndex, ModuleHardwareMapperItem *item);
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

void ModuleHardwareMapper::setItemByCC(unsigned char controlIndex, ModuleHardwareMapperItem *item)
{
  ccMap[controlIndex] = item;
}

ModuleHardwareMapperItem* ModuleHardwareMapper::getItemByNote(unsigned char noteIndex)
{
  return noteMap[noteIndex];
}

void ModuleHardwareMapper::setItemByNote(unsigned char noteIndex, ModuleHardwareMapperItem *item)
{
  noteMap[noteIndex] = item;
}

END_EFFECTRINO_NAMESPACE

#endif
