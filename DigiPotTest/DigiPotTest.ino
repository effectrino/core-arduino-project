#include <SPI.h>

const int potCS = 2;
const int potSHDN = 13;
const int potRS = 16;
const int potSDI = 11;
const int potCLK = 14;

SPISettings potSPISettings(16000000, MSBFIRST, SPI_MODE0); 


void setup() {
  pinMode(potCS, OUTPUT);
  pinMode(potSHDN, OUTPUT);
  pinMode(potRS, OUTPUT);
  pinMode(potSDI, OUTPUT);
  pinMode(potCLK, OUTPUT);
  
  SPI.setSCK(potCLK);
  SPI.setMOSI(potSDI);
//  SPI.setClockDivider(SPI_CLOCK_DIV32);
  
  SPI.begin();

  // Reset IC 
  setPotReset(HIGH);
  delayMicroseconds(1);
  setPotReset(LOW);
  
  // Shutdown outputs
  setPotShutdown(HIGH);

  // Set all pots to zero as a starting point
  for (int channel = 0; channel < 4; channel++) {
    digitalPotWrite(channel, 0);
  }

  // Enable IC
  setPotShutdown(LOW);
}

void setPotShutdown(bool value)
{
  digitalWriteInverse(potSHDN, value);
}

void setPotReset(bool value)
{
  digitalWriteInverse(potRS, value);
}

void setPotCS(bool value)
{
  digitalWriteInverse(potCS, value);
}

void digitalWriteInverse(int pin, int value)
{
  digitalWrite(pin, ((value == HIGH) ? LOW : HIGH));
}

void digitalPotWrite(int address, int value) {
  // take the SS pin low to select the chip:
  setPotCS(HIGH);

  //  send in the address and value via SPI:
  SPI.beginTransaction(potSPISettings);
  SPI.transfer(address);
  SPI.transfer(value);
  SPI.endTransaction();

  // take the SS pin high to de-select the chip:
  setPotCS(LOW);
}

void loop()
{
  const int top = 255;
//  const int top = 64;
  const int incStep = 1;
  const int dly = 1;
//  return;

  for (int level = 0; level < top; level += incStep)
  {
    digitalPotWrite(0, level);
//    delayMicroseconds(dly);
//    delay(dly);
  }
  
  for (int level = top; level >= 0; level -= incStep)
  {
    digitalPotWrite(0, level);
//    delayMicroseconds(dly);
//    delay(dly);
  }
}
