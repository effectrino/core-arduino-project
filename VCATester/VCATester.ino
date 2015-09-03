const int pwmFrequency = 88200;
const int pwmPin = 3;
const int ledPin = 13;

int oldValue = 0;
int slopeStep = 1; 

void setup()
{
  analogWriteFrequency(pwmPin, pwmFrequency);
  analogWriteResolution(8);

  pinMode(ledPin, OUTPUT);

  usbMIDI.setHandleNoteOn(onNoteOn);
  usbMIDI.setHandleNoteOff(onNoteOff);
  usbMIDI.setHandleControlChange(onControlChange);

  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}

void onNoteOn(byte channel, byte note, byte velocity)
{
  setValue(velocity * 2);
//  analogWrite(pwmPin, velocity * 2);
  digitalWrite(ledPin, HIGH);
}

void onNoteOff(byte channel, byte note, byte velocity)
{
//  setValue(0); // skip off notes
//  analogWrite(pwmPin, 0);
  digitalWrite(ledPin, LOW);
}

void onControlChange(byte channel, byte control, byte value)
{
  switch(control) {
    case 6:
      if (value == 0)
        value = 1;
        
      slopeStep = 0xFF / value;
      break;

    case 7:
      setPWM(value * 2);
      break;
    
  }
}

void setValue(byte newValue)
{
  const int step = slopeStep;
  const int baseDelay = 40;
  const int incDelay = baseDelay * step;

  int delta = newValue - oldValue;
  int inc = (delta > 0) ? step : -step;
  
  if (delta == 0)
    return;
  
  while ( (delta > 0) ? (oldValue < newValue) : (oldValue > newValue) )
  {
    oldValue += inc;
//    analogWrite(pwmPin, oldValue);
    setPWM(oldValue);
    delayMicroseconds(incDelay);
  }
}

void setPWM(byte value)
{
  analogWrite(pwmPin, value);
  analogWrite(pwmPin + 1, value);
}

//void OnControlChange(byte channel, byte control, byte value)
//{
//}

void loop()
{
//  analogWrite(pwmPin, 128);
//  delay(100);
//  analogWrite(pwmPin, 16);
//  delay(100);

  usbMIDI.read();
}

