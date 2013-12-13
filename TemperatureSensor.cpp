#include "TemperatureSensor.h"

// Code lifted from DallasTemperature library by Jordan Hochenbaum

TemperatureSensor::TemperatureSensor(char name[]) {
  this->name = name;
}

void TemperatureSensor::setup(byte address[]){
  this->address = address;
  oneWire = new OneWire(2);
}

int TemperatureSensor::read() {
  byte data[12];
  
  oneWire->reset();
  oneWire->skip();         // skip address, i.e. send to all devices 
  oneWire->write(0x44, 0); // start conversion, no parasitic power
  
  delay(94); // the right delay for 9-bit precision
  
  if (!oneWire->reset()) {
     return LOST_CONNECTION;
  }
  oneWire->select(address);    
  oneWire->write(0xBE);   

  byte i;
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = oneWire->read();
  }

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  raw = raw & ~7;  // zero the undefined bits (9-bit resolution)
  
  value = (float)raw / 16.0;
  if (value < -20 || value > 120) {
    return BAD_DATA;
  }
  return OK;
}


