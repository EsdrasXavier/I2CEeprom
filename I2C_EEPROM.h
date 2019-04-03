/*
  I2C_EEPROM.h - I2C_EEPROM library
  Original Copyright (c) 2019 Esdras Xavier Raimundo.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <inttypes.h>

#ifndef I2C_EEPROM_H
#define I2C_EEPROM_H

/* This value will define the max of data which Wire can sent */
#define _BUFFER_LENGTH 30

/***
 * I2C_EEPROM class
 *
 * This object will be just a bridge between the I2C EEPROM device and the user.
 * It will gave almost every same functionality as the EEPROM from Arduino, but with some
 * changes.
 * This class must be compatible with almost 100% of I2C EEPROM chips in the maket,
 * for tests and development was used the chip AT24C128 with 32KB.
***/

struct I2C_EEPROMClass {

  /* Will just call the Wire begin to open the i2c connection */
  void begin(void) { Wire.begin(); };


  /**
   * @brief Will write in the I2C devive some byte value from 0 up to 255,
   *        based on the memory addres.
   *
   * @warning This function uses a delay of 10 milliseconds after send the data to
   *          I2C EEPROM Chip, this could cause a little problem in case you wants
   *          real time write. The delay cannot be removed according the datasheet
   *          for the chip atmel AT24C256 Two-wire Serial EEPROMs (Chip used to development
   *          this lib), the write must have a delay, if is lower than 10 will not work
   *
   * @param deviceAddr. The I2C Device addres, almost every chip is 0X50
   * @param addr. EEPROM Memory addres, goes from 0 up to the EEPROM chip memory limit,
   *             in the case of AT24C128, goes from 0 to 32.767 (32KB)
   * @param val. The value to be saved in the I2C device, limit is 0 to 255
   */
  void write(int deviceAddr, unsigned int addr, int val) {
    int rdata = val;
    Wire.beginTransmission(deviceAddr);
    Wire.write((int) (addr >> 8));   // MSB
    Wire.write((int) (addr & 0xFF)); // LSB
    Wire.write(rdata);
    Wire.endTransmission();
    delay(10); // Delay because write cycle of the I2C Chip
  }

  /**
   * @brief Will read the I2C device in some space of memory pass by param, and
   *        will return the value saved in that space.
   *
   * @param deviceAddr. The I2C Device addres, almost every chip is 0X50
   * @param addr. EEPROM Memory addres, goes from 0 up to the EEPROM chip memory limit,
   *             in the case of AT24C128, goes from 0 to 32.767 (32KB)
   *
   * @return Will return the value saved in the memory space, value goes from 0 to 255.
  */


  byte read(int deviceAddr, unsigned int addr) {
    byte rdata = 0xFF;
    Wire.beginTransmission(deviceAddr);
    Wire.write((int)(addr >> 8));   // MSB
    Wire.write((int)(addr & 0xFF)); // LSB
    Wire.endTransmission();
    Wire.requestFrom(deviceAddr, 1);
    if (Wire.available()) rdata = Wire.read();
    return rdata;
  }

  /**
   * @brief Will get a value from multiple memory address, in this case,
   *        will be used for numbers largers than 255. Usually in those cases
   *        is used more than 1Byte of memory because the memory space are
   *        reserved based in the variable type passed as parameter
   *
   * @param deviceAddr. The I2C Device addres, almost every chip is 0X50
   * @param addr. EEPROM Memory addres, goes from 0 up to the EEPROM chip memory limit,
   *             in the case of AT24C128, goes from 0 to 32.767 (32KB)
   * @param val. The variable to be filled whith the data retrieved from eeprom,
   *             get the pointer of it and change the variable directly
   *
   * @return Will return the variable it self
  */
  template <typename T> const T get(int deviceAddr, unsigned int addr, T &val) {
    val = 0;

    for (int i = 0; i < sizeof(T); i++)
      val |= ((read(deviceAddr, addr++) << (i*8)) & (0xFF << i*8));

    return val;
  }

  /**
   * @brief Will save a value in eeprom using multiple memory address,
   *        must be used in cases of numbers largers than 255. Usually
   *        in those cases is used more than 1Byte of memory because
   *        the memory space are reserved based in the variable type
   *        passed as parameter.
   *
   * @param deviceAddr. The I2C Device addres, almost every chip is 0X50
   * @param addr. EEPROM Memory addres, goes from 0 up to the EEPROM chip memory limit,
   *             in the case of AT24C128, goes from 0 to 32.767 (32KB)
   * @param val. The variable to be saved in eeprom
  */
  template <typename T> const T put(int deviceAddr, unsigned int addr, const T &val) {
    for (int i = 0; i < sizeof(T); i++)
      write(deviceAddr, addr++, (val & (0xFF << (i*8))) >> (i*8));
  }


  /**
   * @brief Will save a array of char in the eeprom, the max size of the eeprom must be 30
   *        at max, because Wire lib just suport until 32 and we already use 2 Bytes to define
   *        the memory address to been written in the I2C EEPROM.
   *
   * @warning This function uses a delay of 10 milliseconds after send the data to
   *          I2C EEPROM Chip, this could cause a little problem in case you wants
   *          real time write. The delay cannot be removed according the datasheet
   *          for the chip atmel AT24C256 Two-wire Serial EEPROMs (Chip used to development
   *          this lib), the write must have a delay, if is lower than 10 will not work
   *          because write cycle of the I2C Chip
   *
   * @param deviceAddr. The I2C Device addres, almost every chip is 0X50
   * @param addr. EEPROM Memory addres, goes from 0 up to the EEPROM chip memory limit,
   *             in the case of AT24C128, goes from 0 to 32.767 (32KB)
   * @param data. A pointer in byte of the char array to be written in the memory,
   *              the variable must be cast like -> (byte *) char[]
   * @param length. The size of your char array, the limit is 30.
  */
  void putString(int deviceAddr, unsigned int addr, byte* data, byte length) {
    Wire.beginTransmission(deviceAddr);
    Wire.write((int)(addr >> 8));   // MSB
    Wire.write((int)(addr & 0xFF)); // LSB

    for (byte c = 0; c < length; c++)
      Wire.write(data[c]);

    Wire.endTransmission();

    delay(10); // Delay because write cycle of the I2C Chip
  }


  /**
   * @brief Will read the I2C EEPROM Chip and get the text saved,
   *        will use the size of the char array saved, in case
   *        the size is wrong the result probably will be also wrong,
   *        since the function will use the size to define how many
   *        Bytes of memory will be needed
   *
   * @param deviceAddr. The I2C Device addres, almost every chip is 0X50
   * @param addr. EEPROM Memory addres, goes from 0 up to the EEPROM chip memory limit,
   *             in the case of AT24C128, goes from 0 to 32.767 (32KB)
   * @param data. A pointer in byte of the char array to be filled ,
   *              the variable must be cast like -> (byte *) char[]
   * @param length. The size of your char array, the limit is 30.
  */
  char getString(int deviceAddr, unsigned int addr, byte *buffer, int length) {
    Wire.beginTransmission(deviceAddr);
    Wire.write((int)(addr >> 8));   // MSB
    Wire.write((int)(addr & 0xFF)); // LSB
    Wire.endTransmission();
    Wire.requestFrom(deviceAddr, length);
    for (int c = 0; c < length;  c++) {
      if (Wire.available()) buffer[c] = Wire.read();
    }
  }
};

static I2C_EEPROMClass I2C_EEPROM;
#endif