#include "I2C_EEPROM.h"

#define EEPROM_ADDR 0x50

void setup() {

  Serial.begin(9600);
  I2C_EEPROM.begin();


  char test[] = "Fazendo um teste";
  char test2[I2C_MAX_BYTES];
  unsigned long int a = 7536984;

  I2C_EEPROM.write(EEPROM_ADDR, 90, 10);
  I2C_EEPROM.put(EEPROM_ADDR, 64, a);

  Serial.println("Before: " + String(test));
  Serial.println("Before: " + String(test2));
  I2C_EEPROM.putString(EEPROM_ADDR, 100, (byte *) test, sizeof(test));
  Serial.println("Middle: " + String(test));
  Serial.println("Middle: " + String(test2));
  I2C_EEPROM.getString(EEPROM_ADDR, 100, (byte *) test2, sizeof(test));
  Serial.println("After: " + String(test));
  Serial.println("After: " + String((char *) test2));

  delay(200);
  Serial.println("Writted");

  a = 100;
  Serial.println("EEPROM at addr 90: " + String(I2C_EEPROM.read(EEPROM_ADDR, 90)));
  Serial.println("A before eeprom: " + String(a));
  Serial.println(I2C_EEPROM.get(EEPROM_ADDR, 64, a));
  Serial.println("A after eeprom: " + String(a));
}


void loop() {

}