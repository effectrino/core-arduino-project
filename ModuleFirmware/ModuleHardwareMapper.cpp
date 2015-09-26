// #include <Arduino.h>
// #include <Effectrino.h>

// #include <StandardCplusplus.h>
// #include <map>
#include "ModuleHardwareMapper.h"
//#include "ModuleHardwareMapperItem.h"

USING_NAMESPASE_EFFECTRINO

ModuleHardwareMapper::ModuleHardwareMapper() {}

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
