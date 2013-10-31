#include "AnalogueWaterLevelSensor.h"
#include <stdio.h>
#include <string.h>

AnalogueWaterLevelSensor::AnalogueWaterLevelSensor(char name[]) {
  this->name = name;
}

void AnalogueWaterLevelSensor::setup(int pin) {
  this->pin = pin;
}

int AnalogueWaterLevelSensor::read() {
}


