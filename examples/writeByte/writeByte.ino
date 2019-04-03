#include "/home/esdras/Documentos/projects/EEPROM_I2c/I2C_EEPROM.h"

#define ADDRESS 0x50

void setup() {
  Serial.begin(9600);
  I2C_EEPROM.begin(); /* Initializes the I2C communication */
  // I2CEeprom
  // A lib made in C to use the I2C Module EEPROM to Arduino and Esp
  /* The variable to be saved, maximum of 255 */
  int myData = 126;

  /* Write the byte in I2C `ADDRESS` on the memory address `0` */
  I2C_EEPROM.write(ADDRESS, 0, myData);
}


void loop() { }