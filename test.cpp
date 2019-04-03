#include <iostream>
#include "I2C_EEPROM.h"


// using namespace std;

int main() {


  long long int a = 32000;
  I2C_EEPROM.put(80, 10, a);
  I2C_EEPROM.get(80, 10, a);
  return 0;
}