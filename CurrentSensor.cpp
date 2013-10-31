#include "CurrentSensor.h"
#include <stdio.h>
#include <string.h>

CurrentSensor::CurrentSensor(char name[]) {
  this->name = name;
}

void CurrentSensor::setup(int pin) {
  this->pin = pin;
}

int CurrentSensor::read() {
  total = 0;
  for(int i = 0; i < 1000; i++) {
    total = total + (.0264 * analogRead(pin) -13.51) / 1000;
    delay(1);
  }
  value = total;
  return 0;
}


