#include <I2C_EEPROM.h>

#define ADDRESS 0x50

void setup() {
  Serial.begin(9600);
  I2C_EEPROM.begin(); /* Initializes the I2C communication */
  int addr = 0; // The memory address
  /* Read the byte in I2C `ADDRESS` on the memory address `0` */
  int data = I2C_EEPROM.read(ADDRESS, addr);
  Serial.println("Data: " + String(data));
}


void loop() { }