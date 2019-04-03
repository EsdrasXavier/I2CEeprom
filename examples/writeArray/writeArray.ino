#include <I2C_EEPROM.h>

#define ADDRESS 0x50

void setup() {
  I2C_EEPROM.begin(); /* Initializes the I2C communication */

  /* Define the array and the contents of it */
  int myData[] = { 1234, 7539, 4568, 7893, 6578 };
  int size = sizeof(int); // The size of the variable type used to declare
                          // the previus array

  int addr = 0; // The address off memory to start with in eeprom
  int arrLen = sizeof(myData) / size; // Gets the array size. Whatever how many
                                      // elements are

  for (int i = 0; i < arrLen; i++) { // Run for every item in the array
    /** Will do the same as the example of `writeAnyNumber.ino`,
     * but in this case the memory address are calculated dynamically based in the
     * array type and size.
     */
    addr = i * size;  // Get i and multiply by the size of the variable type,
                      // always will rerserve the right amount of memory

    /* Just put in I2C eeprom memory the data. */
    I2C_EEPROM.put(ADDRESS, addr, (int) myData[i]); // (int) myData -> Will cast for int, you can
                                                    // replace it with whatever varible type you are using
  }
}


void loop() { }