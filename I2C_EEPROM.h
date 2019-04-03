#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <inttypes.h>

#ifndef I2C_EEPROM_H
#define I2C_EEPROM_H


#define I2C_MAX_BYTES 32 // Must be used to get string

struct I2C_EEPROMClass {

  void begin(void) { Wire.begin(); };

  void write(int deviceaddress, unsigned int eeaddress, int val) {
    int rdata = val;
    Wire.beginTransmission(deviceaddress);
    Wire.write((int) (eeaddress >> 8)); // MSB
    Wire.write((int) (eeaddress & 0xFF)); // LSB
    Wire.write(rdata);
    Wire.endTransmission();
    delay(10);  // Must have this delay, according the  datasheet for the chip
                // atmel AT24C256 Two-wire Serial EEPROMs
                // the write must have a delay, if is lower than 10 will not work
  }

  byte read(int deviceAddr, unsigned int addr) {
    byte rdata = 0xFF;
    Wire.beginTransmission(deviceAddr);
    Wire.write((int)(addr >> 8)); // MSB
    Wire.write((int)(addr & 0xFF)); // LSB
    Wire.endTransmission();
    Wire.requestFrom(deviceAddr, 1);
    if (Wire.available()) rdata = Wire.read();
    return rdata;
  }

  template <typename T> const T get(int deviceAddr, unsigned int addr, T &val) {
    T j = 0;
    for (int i = 0; i < sizeof(T); i++) {
      j |= ((read(deviceAddr, addr++) << (i*8)) & (0xFF << i*8));
    }
    val = j;
    return j;
  }

  template <typename T> const T put(int deviceAddr, unsigned int addr, const T &val) {
    for (int i = 0; i < sizeof(T); i++) write(deviceAddr, addr++, (val & (0xFF << (i*8))) >> (i*8));
  }

  void putString(int deviceAddr, unsigned int addr, byte* data, byte length) {
    Wire.beginTransmission(deviceAddr);
    Wire.write((int)(addr >> 8)); // MSB
    Wire.write((int)(addr & 0xFF)); // LSB
    for (byte c = 0; c < length; c++)
      Wire.write(data[c]);

    Wire.endTransmission();

    delay(10);
  }

  char getString(int deviceAddr, unsigned int addr, byte *buffer, int length) {
    Wire.beginTransmission(deviceAddr);
    Wire.write((int)(addr >> 8)); // MSB
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