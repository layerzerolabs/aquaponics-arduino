#include "CurrentSensor.h"

// See http://forum.arduino.cc/index.php?topic=168468.0;wap2

CurrentSensor::CurrentSensor(char name[]) {
  this->name = name;
}

void CurrentSensor::setup(int pin, float multiplier, float offset) {
  this->pin = pin;
  this->multiplier = multiplier;
  this->offset = offset;
}

int CurrentSensor::read() {
  float total = 0;
  for (int i = 0; i < numberOfSamples; i++) {
    float current = analogRead(pin) - 512;
    total += current * current ;  // sum squares
  }
  value = abs(sqrt (total / numberOfSamples) - offset) * multiplier ;
  return OK;
}


