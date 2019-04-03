#include <I2C_EEPROM.h>

#define ADDRESS 0x50

void setup() {
  I2C_EEPROM.begin(); /* Initializes the I2C communication */

  /** My data char varible. This var can have until 32Bytes of data,
   * that means, 32characters at maximum
   */
  char data[] = "Just an example of eeprom";

  int addr = 0; // Define the address to start in I2c

  /** To write the text into eeprom, you must specify the I2c address,
   * the second parameter is the initial address of the memory.
   * The third param will pass the text as a byte pointer and
   * the last parameter pass the size of the char array, in maximum of 32
  */
  I2C_EEPROM.putString(ADDRESS, addr,  (byte *) data, sizeof(data));
}


void loop() { }