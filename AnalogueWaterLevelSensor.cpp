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
  value = (emptyReading - rawValue) / unit + cmBottom;
  return OK;
}


