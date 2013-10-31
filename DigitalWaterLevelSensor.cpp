#include "DigitalWaterLevelSensor.h"
#include <stdio.h>
#include <string.h>

DigitalWaterLevelSensor::DigitalWaterLevelSensor(char name[]) {
  this->name = name;
}

void DigitalWaterLevelSensor::setup(int pins[]) {
  this->pins = pins;
  for(int i = 0; i <= 3; i++) {
    pinMode(pins[i], INPUT_PULLUP); // switch is to ground so pullup needed
  }
}

int DigitalWaterLevelSensor::read() {
  value = 0;
  for(int i = 0; i <= 3; i++) { // read each switch in turn
    value += !digitalRead(pins[i]) << i; // switch is 0 when high. Bitshifting adds 1,2,4,8
  }
  return 0;
}


