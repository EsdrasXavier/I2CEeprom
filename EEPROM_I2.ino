#include "I2C_EEPROM.h"

#define EEPROM_ADDR 0x50

void setup() {

  Serial.begin(9600);
  I2C_EEPROM.begin();

  char test[] = "Doing a test of eeprom :)";
  char test2[_BUFFER_LENGTH];
  unsigned long int a = 7536984;

  I2C_EEPROM.write(EEPROM_ADDR, 90, 10);
  I2C_EEPROM.put(EEPROM_ADDR, 64, a);

  Serial.println("Before test:  " + String(test));
  Serial.println("Before test2: " + String(test2));
  I2C_EEPROM.putString(EEPROM_ADDR, 100, (byte *) test, sizeof(test));
  Serial.println("Middle test:  " + String(test));
  Serial.println("Middle test2: " + String(test2));
  Serial.println("Written...");
  delay(200);
  Serial.println("Reading EEPROM...");
  I2C_EEPROM.getString(EEPROM_ADDR, 100, (byte *) test2, sizeof(test));
  Serial.println("After test:  " + String(test));
  Serial.println("After test2: " + String((char *) test2));

  a = 100; // Change the value of a before gets from EEPROM
  Serial.println("EEPROM at addr 90: " + String(I2C_EEPROM.read(EEPROM_ADDR, 90)));
  Serial.println("A before eeprom: " + String(a));
  Serial.println("Value returned from get: " + String(I2C_EEPROM.get(EEPROM_ADDR, 64, a)));
  Serial.println("A after eeprom: " + String(a));
}


void loop() { }