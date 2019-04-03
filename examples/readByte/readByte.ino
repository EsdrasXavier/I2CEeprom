#include "/home/esdras/Documentos/projects/EEPROM_I2c/I2C_EEPROM.h"

#define ADDRESS 0x50

void setup() {
  Serial.begin(9600);
  I2C_EEPROM.begin(); /* Initializes the I2C communication */

  /* Read the byte in I2C `ADDRESS` on the memory address `0` */
  int data = I2C_EEPROM.read(ADDRESS, 0);
  Serial.println("Data: " + String(data));
}


void loop() { }