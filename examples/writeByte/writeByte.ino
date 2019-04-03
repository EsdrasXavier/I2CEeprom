#include <I2C_EEPROM.h>

#define ADDRESS 0x50

void setup() {
  I2C_EEPROM.begin(); /* Initializes the I2C communication */

  /* The variable to be saved, maximum of 255 */
  int myData = 126;
  int addr = 0; // The memory address
  /* Write the byte in I2C `ADDRESS` on the memory address `0` */
  I2C_EEPROM.write(ADDRESS, addr, myData);
}


void loop() { }