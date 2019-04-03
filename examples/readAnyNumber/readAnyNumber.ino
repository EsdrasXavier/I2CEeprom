#include <I2C_EEPROM.h>

#define ADDRESS 0x50

void setup() {
  Serial.begin(9600);
  I2C_EEPROM.begin(); /* Initializes the I2C communication */

  int myData = 0;  // The variable to be read
  int myData2 = 0; // My second larger number to be read
  int addr = 0;    // The start address
  int size = sizeof(myData); // The size of the variable

  /**
   * Read the number in I2C `ADDRESS` on the memory address `0`
   * the third param is the varible who will store the value from
   * eeprom. Always when is used the `get` the variable type must
   * be the same type of the variable used to save. Otherwise the
   * value will be wrong
   */
  I2C_EEPROM.get(ADDRESS, addr, myData);

  addr += size; // Add the size of the varible to the address

  /* Read the second data into the new memory space */
  I2C_EEPROM.get(ADDRESS, addr, myData2);

  Serial.println("Data 1: " + String(myData) + " - Data 2: " + String(myData2));
}


void loop() { }