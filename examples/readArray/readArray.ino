#include <I2C_EEPROM.h>

#define ADDRESS 0x50
#define ARRAY_SIZE 5 // This was the size used in the writeArray example

void setup() {
  Serial.begin(9600);
  I2C_EEPROM.begin(); /* Initializes the I2C communication */

  /* Define the array with the size and every element equal 0 */
  int myData[ARRAY_SIZE] = { 0 };
  int size = sizeof(int); // The size of the variable type used to declare
                          // the previus array

  int addr = 0; // The address off memory to start with in eeprom
  int arrLen = sizeof(myData) / size; // Gets the array size. Whatever how many
                                      // elements are

  for (int i = 0; i < arrLen; i++) { // Runs for every array item
    addr = i * size; // Stores the memory address to retrieve data from
    int val = 0; // Declare the variable who will store the the data retrieved from eeprom
    I2C_EEPROM.get(ADDRESS, addr, val); // Will read the eeprom as the readAnyNumber example
    myData[i] = val; // Stores the retrieved value in the array position
  }

  for (int i = 0; i < arrLen; i++) // Runs for every array item and print in Serial
    Serial.println("Index " + String(i) + ": " + String(myData[i]));
}


void loop() { }