#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

//// GUItool: begin automatically generated code
////AudioPlaySdWav           playSdWav1;     //xy=110,48
//AudioSynthWaveform       lfo1;      //xy=119,139
//AudioMixer4              mixer1;         //xy=334,113
//AudioOutputPWM           pwm1;           //xy=523,114
//AudioConnection          patchCord1(lfo1, pwm1);
////AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
////AudioConnection          patchCord2(playSdWav1, 1, mixer1, 1);
////AudioConnection          patchCord3(OSC1, 0, mixer1, 2);
////AudioConnection          patchCord4(mixer1, pwm1);
//// GUItool: end automatically generated code

const int pwmPins[] = { 3, 4, 5, 6, 20, 21, 22, 23 }; // skip 10 pin (CS)
const int pwmPinsCount = (sizeof(pwmPins) / sizeof(int));

const int pwmFrequency = 187500; //93750

void setup()
{
  analogWriteResolution(8);
  analogWriteFrequency(3, pwmFrequency);

//  AudioMemory(8);
//  lfo1.begin(1, 0.2, WAVEFORM_TRIANGLE);
//  mixer1.gain(3, 2);
}

void loop()
{
  const int mcs = 1;

  for(int value = 0; value < 256; value++)
  {
//    setPWMOutput(3, value);
    setPWMOutputs(value);
    delayMicroseconds(mcs);
  }
  
  for(int value = 255; value >= 0; value--)
  {
//    setPWMOutput(3, value);
    setPWMOutputs(value);
    delayMicroseconds(mcs);
  }
}

//void timerISR(void)
//{
//}

void setPWMOutputs(int value)
{
  for(int i = 0; i < pwmPinsCount; i++)
  {
    int pin = pwmPins[i];
    setPWMOutput(pin, value);
  }
}

void setPWMOutput(int pin, int value)
{
//  analogWrite(pin, (value + (pin * 256 / pwmPinsCount)) % 256);
  analogWrite(pin, value);
//  delay(1);
//  delayMicroseconds(10);
}
