#ifndef MODULE_H_
#define MODULE_H_

#include <ArduinoJson.h>
#include <StandardCplusplus.h>
#include <Effectrino.h>
#include <duino-tools.h>
// #include <MIDI.h>

// #include "ConfigParser.h"
#include "ModuleHardwareMapper.h"
// #include "ModuleHardwareMapperItem.h"
// #include "ModuleIC.h"
// #include "ModuleICFactory.h"
#include "ModuleICRegistry.h"
#include "ModuleEffect.h"
// #include "ModuleEffectParameter.h"
#include "ModuleEffectRegistry.h"


USING_NAMESPASE_EFFECTRINO
BEGIN_EFFECTRINO_NAMESPACE

class Module {

  public:
    bool init();
    bool parseJSON(char* input);

    void noteOnEvent(const byte pitch, const byte velocity);
    void noteOffEvent(const byte pitch);
    void ccEvent(const byte control, const byte value);

    void selectEffectByIndex(unsigned char fxIndex);

  protected:
    // Pointer to current effect
    ModuleEffect* currentEffect = (ModuleEffect*)NULL; 

    // Effects instances
    ModuleEffectRegistry fxRegistry;

    // Mapper for module hardware
    ModuleICRegistry icRegistry;

    ModuleHardwareMapper* getHardwareMapper();

};

END_EFFECTRINO_NAMESPACE

#endif
