#ifndef MODULE_PROCESSOR_H_
#define MODULE_PROCESSOR_H_

#include <ArduinoJson.h>
#include <Effectrino.h>
#include <duino-tools.h>

#include "ConfigParser.h"
#include "MIDIMapper.h"
#include "ModuleIC.h"
#include "ModuleICFactory.h"
#include "ModuleICRegistry.h"
#include "EffectParameter.h"


USING_NAMESPASE_EFFECTRINO
BEGIN_EFFECTRINO_NAMESPACE

class ModuleProcessor {

  // ArduinoJson jsonObject;
  public:
    bool init();
    bool parseJSON(char* input);

  	void noteOnEvent(const byte pitch, const byte velocity);
  	void noteOffEvent(const byte pitch);
  	void ccEvent(const byte control, const byte value);

  protected:
    // Mapper for linking MIDI events to effect parameters
    MIDIMapper midiMapper;

    // Mapper for module hardware
    ModuleICRegistry icRegistry;

};

inline bool ModuleProcessor::init()
{
  // TODO get JSON config
  // char* moduleConfig = this->getConfig();

  #include "TestJSONConfig.h"

  if ( !this->parseJSON(testJSONConfig) )
    return false;

  return true;
}

inline bool ModuleProcessor::parseJSON(char* input)
{
  ConfigParser parser(this->icRegistry);

  return parser.process(input);
}

// void ModuleProcessor::parseJSON(const Stream &input)
// {
//   // TODO someday
// }

inline void ModuleProcessor::noteOnEvent(const byte pitch, const byte velocity)
{
  EffectParameter* parameter = midiMapper.getEffectParameterByNote(pitch);

  if ( !parameter )
    return;

  // TODO process parameter on
}

inline void ModuleProcessor::noteOffEvent(const byte pitch)
{
  EffectParameter* parameter = midiMapper.getEffectParameterByNote(pitch);

  if ( !parameter )
    return;

  // TODO process parameter off
}

inline void ModuleProcessor::ccEvent(const byte control, const byte value)
{
  EffectParameter* parameter = midiMapper.getEffectParameterByCC(control);

  if ( !parameter )
    return;

  // Get linked hardware IC channels (in form of [<icIndex>, <channelIndex>])

  // Iterate over each channel
    // Get IC object
    // Set IC channel data
}

END_EFFECTRINO_NAMESPACE

#endif
