#include <Arduino.h>
#include <Wire.h>
#include <MIDI.h>
#include <SoftwareSerial.h>

// Some useful tools
#include <duino-tools.h>

// Headers
#include <Effectrino.h>
#include <Patch.h>
#include <PatchEffect.h>
#include <EffectsStack.h>
#include <AudioMatrixProtocol.h>

// TODO Maybe hardware serial on Mega?
#define CORE_EXTERNAL_MIDI_RX_PIN 10
#define CORE_EXTERNAL_MIDI_TX_PIN 11

// TODO Maybe hardware serial on Mega?
#define CORE_MODULE_MIDI_RX_PIN 7
#define CORE_MODULE_MIDI_TX_PIN 8


USING_NAMESPACE_MIDI

USING_NAMESPASE_EFFECTRINO

// TODO Move to EEPROM config
const byte  MIDIInputChannel = 1;
const bool  MIDIThru = true;
const bool  MIDIDirectControl = true;

const int   LED = 13;

// TODO EEPROM global effects register (for reserving MIDI notes and CC for every effect)

// TODO MIDI config (MIDI IN channel + MIDI Thru + allow direct access + MIDI mapping options)

// TODO current patch (MIDI notes mapping => effects list + effects stack)
Patch currentPatch;

// Current effects stack instance
EffectsStack effectsStack;

// Audio Matrix instance
AudioMatrixProtocol AMP(Wire);


// TODO Set up a new serial port for External MIDI
SoftwareSerial CoreExternalMIDISerialPort = SoftwareSerial(CORE_EXTERNAL_MIDI_RX_PIN, CORE_EXTERNAL_MIDI_TX_PIN);

// TODO Initialize External MIDI input/output
MIDI_CREATE_INSTANCE(SoftwareSerial, CoreExternalMIDISerialPort, CoreExternalMIDI);
// MIDI_CREATE_INSTANCE(HardwareSerial, Serial, CoreExternalMIDI);


// Set up a new serial port for Module MIDI
SoftwareSerial CoreModuleMIDISerialPort = SoftwareSerial(CORE_MODULE_MIDI_RX_PIN, CORE_MODULE_MIDI_TX_PIN);

// Initialize Module MIDI input/output
MIDI_CREATE_INSTANCE(SoftwareSerial, CoreModuleMIDISerialPort, CoreModuleMIDI);


void setup()
{
    initDebug();

    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);

    // Fix for external pull-up resistor
    // digitalWrite(CORE_EXTERNAL_MIDI_RX_PIN, LOW);

    // Serial.begin(9600);

    // // Wait for serial init
    // while(!Serial) {}

    // // Initialize matrix connector
    // initAudioMatrix();
    Wire.begin();

    // Load last used patch
    loadLastPatch();

    // Init MIDI connector
    initMIDI();
}

// void initAudioMatrix()
// {
// }

void initMIDI()
{
    // Define pin modes for MIDI tx, rx:
    pinMode(CORE_EXTERNAL_MIDI_RX_PIN, INPUT);
    pinMode(CORE_EXTERNAL_MIDI_TX_PIN, OUTPUT);


    // Callbacks
    CoreExternalMIDI.setHandleNoteOn(handleCoreNoteOn);
    CoreExternalMIDI.setHandleNoteOff(handleCoreNoteOff);
    CoreExternalMIDI.setHandleControlChange(handleCoreControlChange);

    // TODO Configure MIDI Thru
    // CoreExternalMIDI.setThruFilterMode(MIDI_NAMESPACE::Off);
    CoreExternalMIDI.setThruFilterMode(MIDI_NAMESPACE::Full);

    // Listening to all channels
    CoreExternalMIDI.begin(MIDI_CHANNEL_OMNI);
}

// TODO Load last used patch
void loadLastPatch()
{
    // load JSON
    // iterate throug it
    // fillup currentPatch via setters
    // fillup effectsStack via setters
}

void loadSystemConfig()
{
    // setup mapping "effect ID" => "slot number" + "MIDI CC start point"
}

void loop()
{
    // Call MIDI.read the fastest you can for real-time performance.
    CoreExternalMIDI.read();
}


// TODO
void handleCoreNoteOn(byte channel, byte pitch, byte velocity)
{
    digitalWrite(LED, HIGH);
    // return;

    // Do whatever you want when a note is pressed.
    // Try to keep your callbacks short (no delays ect)
    // otherwise it would slow down the loop() and have a bad impact
    // on real-time performance.

    Debug << "NoteOn: pitch = " << pitch << ", velocity = " << velocity << "\r\n"; //"channel: " +
    // Serial.println(channel, DEC); //"channel: " +
    // Serial.println(pitch, DEC); //", note pitch: " +
    // Serial.println(velocity, DEC); //", velocity: " +

    // TODO Get channel from system MIDI config
    if ( channel == MIDIInputChannel )
    {
        Wire.beginTransmission(AMP.getI2CAddress());
        AMP.sendOn(pitch >> 3, pitch >> 3);
        AMP.sendOff(pitch >> 3, pitch >> 3);
        AMP.sendOn(pitch >> 3, pitch >> 3);
        // AMP.sendOn(velocity >> 3, pitch >> 3);
        Wire.endTransmission();

        return;

        // Get effect object from current patch by note
        PatchEffect * effect = currentPatch.getEffectByMIDINote(pitch);

        if ( !effect )
            return;

        effectsStack.on(effect, velocity);
    }
    // If direct modules control enabled
    else if ( MIDIDirectControl )
    {
    	// Process mapping messages to modules
    }
}



// TODO
void handleCoreNoteOff(byte channel, byte pitch, byte velocity)
{
    digitalWrite(LED, LOW);
    // return;

    Debug << "NoteOff: pitch = " << pitch << "\r\n"; //"channel: " +

    // Serial.println("NoteOff"); //"channel: " +
    // Serial.println(channel, DEC); //"channel: " +
    // Serial.println(pitch, DEC); //", note pitch: " +
    // Serial.println(velocity, DEC); //", velocity: " +

    // Do something when the note is released.
    // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.

    Wire.beginTransmission(AMP.getI2CAddress());
    AMP.sendOff(pitch >> 3, pitch >> 3);
    // AMP.sendOff(pitch >> 3, velocity >> 3);
    Wire.endTransmission();

    return;

    // Get effect object from current patch by note
    PatchEffect * effect = currentPatch.getEffectByMIDINote(pitch);

    if ( !effect )
    {
        return;
    }

    effectsStack.off(effect);
}

void handleCoreControlChange(byte channel, byte number, byte value)
{
  // Serial.println("ControlChange");
  // Serial.println(channel, DEC);
  // Serial.println(number, DEC);
  // Serial.println(value, DEC);

  // TODO get "CC => Slot + CC" mapping
  // Send CC to module
}

// void matrixSendOn(int x, int y)
// {
//     Wire.beginTransmission(AMP.getI2CAddress());
//     AMP.sendOn(x, y);
//     Wire.endTransmission();
// }
