//#include "OneWire.h"
#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(char name[]) {
  this->name = name;
}

void TemperatureSensor::setup(byte address[]){
  this->address = address;
  _oneWire = new OneWire(2);
}

int TemperatureSensor::read() {
  byte data[12];
  
  _oneWire->reset();
  _oneWire->skip();         // skip address, i.e. send to all devices 
  _oneWire->write(0x44, 0); // start conversion, no parasitic power
  
  delay(94); // the right delay for 9-bit precision
  
  if (!_oneWire->reset()) {
     return 1;
  }
  _oneWire->select(address);    
  _oneWire->write(0xBE);   
  
  
  delay(1000);

  byte i;
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = _oneWire->read();
  }

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  // at lower res, the low bits are undefined, so let's zero them
  raw = raw & ~7;  // 9 bit resolution, 93.75 ms
  
  value = (float)raw / 16.0;
  if (value < -20 || value > 120) {
    return BAD_DATA;
  }
  return OK;
}


