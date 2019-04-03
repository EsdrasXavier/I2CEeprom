#include <I2C_EEPROM.h>

#define ADDRESS 0x50

void setup() {
  Serial.begin(9600);
  I2C_EEPROM.begin(); /* Initializes the I2C communication */

  /**
   * My data char varible. This var can have until 32Bytes of data,
   * that means, 32characters at maximum.
   */
  char sentenceSaved[] = "Just an example of eeprom";

  /**
   * This varible will store the data from eeprom, you must initialize
   * the varible empty and with the memory of 32Bytes reserved (maximum of I2C),
   * you can just use the I2C_EEPROM constant _BUFFER_LENGTH, will already return
   * the maximum value to reserve the space
  */
  char data[_BUFFER_LENGTH];

  int addr = 0; // Define the address to start in I2c

  Serial.println("Before read EEPROM -> Data: " + String(data));

  /**
   * To read the text grom eeprom, you must specify the I2c address,
   * the second parameter is the initial address of the memory.
   * The third param will pass the text as a byte pointer, this varible pointer
   * will be filled with the data recover from eeprom, and
   * the last parameter pass the size of the char array, the value must be the same
   * used to save your text, otherwise will return extra characters or wrong characters
  */
  I2C_EEPROM.getString(ADDRESS, addr, (byte *) data, sizeof(sentenceSaved));
  Serial.println("After read EEPROM -> Data: " + String(data));
}


void loop() { }