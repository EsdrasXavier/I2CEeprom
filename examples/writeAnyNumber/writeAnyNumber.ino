#include <I2C_EEPROM.h>

#define ADDRESS 0x50

void setup() {
  I2C_EEPROM.begin(); /* Initializes the I2C communication */

  int myData = 12345;  // The variable to be saved
  int myData2 = 63304; // My second larger number to be saved
  int addr = 0;        // The start address
  int size = sizeof(myData); // The size of the variable

  /* Write the number in I2C `ADDRESS` on the memory address `0` */
  I2C_EEPROM.put(ADDRESS, addr, myData);

  /**
   * In this case to be able to use more than 1Byte variable value size the eeprom
   * must reserve the varible type space. So the `size` varible will get the
   * size of varible based on the architecture of the processor and after save the
   * first number in the address will add the size of the variable to the address.
   * So the next free memory space will be:
   * actual_address + sizeof(my_varible_type)
   * In esp32 (32Bits processor) `int` is 4Bytes
  */
  addr += size; // Add the size of the varible to the address

  /* Write the second data into the new memory space */
  I2C_EEPROM.put(ADDRESS, addr, myData2);

}


void loop() { }