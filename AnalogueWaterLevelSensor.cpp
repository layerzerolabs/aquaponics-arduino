#include "AnalogueWaterLevelSensor.h"

AnalogueWaterLevelSensor::AnalogueWaterLevelSensor(char name[]) {
  this->name = name;
}

void AnalogueWaterLevelSensor::setup(int pin) {
  this->pin = pin;
  pinMode(pin, INPUT);
}

int AnalogueWaterLevelSensor::read() {
  int rawValue = analogRead(pin);
  value = (695 - rawValue) / 7.81 + 5;
  //value = analogRead(pin);
  return OK;
}


