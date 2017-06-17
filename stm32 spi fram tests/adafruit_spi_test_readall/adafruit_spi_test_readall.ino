#include <SPI.h>
#include "Adafruit_FRAM_SPI.h"

/* Example code for the Adafruit SPI FRAM breakout */
uint8_t FRAM_CS = PA15;//10;

//Adafruit_FRAM_SPI fram = Adafruit_FRAM_SPI(FRAM_CS);  // use hardware SPI

uint8_t FRAM_SCK= PB3;//13;
uint8_t FRAM_MISO = PB4;//12;
uint8_t FRAM_MOSI = PB5;//11;
//Or use software SPI, any pins!
Adafruit_FRAM_SPI fram = Adafruit_FRAM_SPI(FRAM_SCK, FRAM_MISO, FRAM_MOSI, FRAM_CS);

uint16_t          addr = 0;

void setup(void) {
  Serial.begin(115200);
  delay (5000);
  if (fram.begin()) {
    Serial.println("Found SPI FRAM");
  } else {
    Serial.println("No SPI FRAM found ... check your connections\r\n");
    while (1);
  }
  
  // Read the first byte
  //uint8_t test = fram.read8(0x0);
  //Serial.print("Restarted "); Serial.print(test); Serial.println(" times");
  uint8_t value;
  // Test write ++
  //for (uint16_t a = 0; a < 150; a++) {
  // NVMEMwrite(a,a); //fram.read8(a);
//  }

  // dump the entire 8K of memory!

  for (uint16_t a = 0; a < 8192; a++) {
    value = NVMEMread(a);//fram.read8(a);
    if ((a % 32) == 0) {
      Serial.print("\n 0x"); Serial.print(a, HEX); Serial.print(": ");
    }
    Serial.print("0x"); 
    if (value < 0x1) 
      Serial.print('0');
    Serial.print(value, HEX); Serial.print(" ");
  }
}

void loop(void) {

}


uint8_t NVMEMread(uint16_t address)
{
#if defined (MCU_STM32F103C8)
  uint8_t theValue = fram.read8(address);
#endif  
  return theValue;
}

void NVMEMwrite(uint16_t address, uint8_t dataByte)
{
  #if defined (MCU_STM32F103C8)
  fram.writeEnable(true);
  fram.write8(address, dataByte);
  fram.writeEnable(false);
  #endif
}

