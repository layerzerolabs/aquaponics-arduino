#include "pHSensor.h"

pHSensor::pHSensor(char name[]) {
  this->name = name;
}

void pHSensor::setup(int pin) {
  this->pin = pin;
}

// See https://github.com/andrewoke/MacroDuino/blob/master/supportFunctions.h
int pHSensor::read() {
  unsigned int analogreadings = 0; // See http://www.practicalmaker.com/comment/3258#comment-3258
  unsigned int millivolts;
  unsigned int i;

  for(i = 0; i < numberOfSamples; i++){
    analogreadings += analogRead(pin);
    delay(10);    // Give analog pin time to recover
  }
  analogreadings /= numberOfSamples;
  millivolts = ((analogreadings * arduinoVoltage) / 1024) * 1000;
  value = ((millivolts / phGain) / 59.2) + 3.9;
  return millivolts <= maxSaneRawValue ? OK: LOST_CONNECTION_OR_BAD_DATA;
}


