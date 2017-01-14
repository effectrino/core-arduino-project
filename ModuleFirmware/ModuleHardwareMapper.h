#ifndef MODULE_HARDWARE_MAPPER_H_
#define MODULE_HARDWARE_MAPPER_H_

#include <Arduino.h>
#include <Effectrino.h>

// #include <StandardCplusplus.h>
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

END_EFFECTRINO_NAMESPACE

#endif
