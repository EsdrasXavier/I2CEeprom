# I2CEeprom

Arduino library made to use I2C EEPROM Chip AT24C128, was based in the EEPROM library to arduino. This library will handler the data and memory allocation in the eeprom for your, for any primary data type in any microprocessor architecture (8-bit, 16-bit, 32-bit and 64-bit).

## Getting Started

To use this lib you must download it and import into your Arduino IDE. Make sure you have arduino IDE and `Wire` lib (Cames with Arduino IDE).

## Running the examples

In this repo has a folder called **examples**, inside of it has all the examples of data save and read in the EEPROM module. Thwy will cover:

- Read a single Byte
- Write a single Byte
- Read any number from EEPROM
- Write any number in EEPROM
- Read a text from EEPROM (Max of 30 Bytes)
- Write a text in EEPROM (Max of 30 Bytes)
- Read an number array from the EEPROM
- Write an number array in the EEPROM


### How to use it
The I2C_EEPROM library is included in your IDE download. To add its functionality to your sketch you'll need to reference the library header file. You do this by adding an include directive to the top of your sketch.

```
#include <I2C_EEPROM.h>

void setup() {

}

void loop() {

}

```

The library has a global variable name **I2C_EEPROM**, you use this variable to access the library functions. The methods provided in the EEPROM class are listed below.

## Library functions

#### **`I2C_EEPROM.begin()`**
Will start the communication with the I2C device, in case you do not call this function in the setup nothing will work.

```
#include <I2C_EEPROM.h>

void setup() {
  I2C_EEPROM.begin();
}

void loop() {

}

```


#### **`I2C_EEPROM.read( deviceAddress, memoryAddress )`** [[_example_]](examples/readByte/readByte.ino)
This function allows you to read a single byte of data from the eeprom.
The first parameters is the I2C chip addres.
The second parametes is the memory addres you wish to read.

Will return a Byte.

#### **`I2C_EEPROM.write( deviceAddress, memoryAddress, value)`** [[_example_]](examples/writeByte/writeByte.ino)
This function allows you to write a single byte of data in the eeprom.
The first parameters is the I2C chip addres.
The second parametes is the memory addres you wish to write.
The third will be the value to write goes from 0 up to 255.

Will return a Byte.


#### **`I2C_EEPROM.put( deviceAddress, memoryAddress, value)`** [[_example_]](examples/writeAnyNumber/writeAnyNumber.ino)
This function allows you to write any data in the eeprom.
The first parameters is the I2C chip addres.
The second parametes is the memory addres you wish to start writting.
The third is the variable to write.

**Note:** This function will take the data type and reserve an amount of memory relative to the data type. That means if you pass an `int` as parameter and you are using a 32-bit microcontroller for example the function will reserve 4 Bytes of memory in I2C chip to save this data. This function only must be used in cases where the data is larger than _255_ and you cannot use the `write` function.

Returns nothing

#### **`I2C_EEPROM.get( deviceAddress, memoryAddress, value)`** [[_example_]](examples/readAnyNumber/readAnyNumber.ino)
This function allows you to read eany data from the eeprom.
The first parameters is the I2C chip addres.
The second parametes is the memory addres you wish to start writting.
The third is the variable to store the value read. The function will take a pointer from the number, so you can just pass the variable as parameter and it will be changed by the function.

###### Example
```
#include <I2C_EEPROM.h>

void setup() {
  I2C_EEPROM.begin();
  int data = 0;
  I2C_EEPROM.get(0x50, 0, data);
}

void loop() {

}
```

**Note:** This function will take the data type and reserve an amount of memory relative to the data type. That means if you pass an `int` as parameter and you are using a 32-bit microcontroller for example the function will reserve 4 Bytes of memory in I2C chip to read this data, that means if the data type is too large may have some unexpected values returned. This function only must be used in cases where the data is larger than _255_ and you cannot use the `read` function.

Returns the value read from EEPROM



#### **`I2C_EEPROM.putString( deviceAddress, memoryAddress, dataPointer, lenghtOfData)`** [[_example_]](examples/writeAnyNumber/writeAnyNumber.ino)
This function allows you to write a text in the EEPROM.
The first parameters is the I2C chip addres.
The second parametes is the memory addres you wish to start writting.
The third is the pointer of the char variable to be written.
The forth parameter defines how many Bytes must be used, usually is the variable size.


###### Example
```
#include <I2C_EEPROM.h>

#define ADDRESS 0x50

void setup() {
  I2C_EEPROM.begin();
  char data[] = "Just an example of eeprom";
  int addr = 0;

  I2C_EEPROM.putString(ADDRESS, addr, (byte *) data, sizeof(data));
}

void loop() { }
```
Returns nothing

**Note:** The data char must be cast as a pointer of byte `(byte *) char[]`

#### **`I2C_EEPROM.getString( deviceAddress, memoryAddress, dataPointer, lenghtOfData)`** [[_example_]](examples/readAnyNumber/readAnyNumber.ino)
This function allows you to read a text from the EEPROM.
The first parameters is the I2C chip addres.
The second parametes is the memory addres you wish to start writting.
The third is the pointer of the char variable to be read.
The forth parameter defines how many Bytes must be used, usually is the variable size.


###### Example
```
#include <I2C_EEPROM.h>

#define ADDRESS 0x50

void setup() {
  Serial.begin(9600);
  I2C_EEPROM.begin();

  char sentenceSaved[] = "Just an example of eeprom"; // Just for me know the size of the array
  char data[_BUFFER_LENGTH];

  int addr = 0;

  Serial.println("Before read EEPROM -> Data: " + String(data));
  I2C_EEPROM.getString(ADDRESS, addr, (byte *) data, sizeof(sentenceSaved));
  Serial.println("After read EEPROM -> Data: " + String(data));
}


void loop() { }
```
Returns nothing

**Note:** The data char must be cast as a pointer of byte `(byte *) char[]`


## Built With

* [Wire](https://github.com/esp8266/Arduino/tree/master/libraries/Wire) - Take care of the I2c communication


## Authors

* **Esdras Xavier** - *Initial work* - [EsdrasXavier](https://github.com/EsdrasXavier)

<!-- See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project. -->

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Thanks to [Arduino playground](https://playground.arduino.cc/Code/I2CEEPROM/), which helped a lot to start develop this lib
* Inspired by EEPROM Library for Arduino built-int EEPROM [Repo](https://github.com/PaulStoffregen/EEPROM)
