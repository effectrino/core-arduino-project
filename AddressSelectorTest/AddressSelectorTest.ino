#include <Arduino.h>
#include <duino-tools.h>
// #include <Debug.h>
// #include <Misc.h>
// #include <HardwareAddressDetector.h>

void setup()
{
  Debug.init(true);

  HardwareAddressDetector hwAddress;

  byte address = hwAddress.get(4, 5, 6, 7);

  Debug << F("Address is ") << address << CRLF;

  Debug.printFreeRam();
}

void loop()
{
  // Noop  
}
