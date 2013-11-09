#include "CurrentSensor.h"

// See http://forum.arduino.cc/index.php?topic=168468.0;wap2

CurrentSensor::CurrentSensor(char name[]) {
  this->name = name;
}

void CurrentSensor::setup(int pin) {
  this->pin = pin;
}

int CurrentSensor::read() {
  float total = 0;
  for (int i = 0; i < N; i++) {
    float current = 0.0264 * (analogRead(A3) - 512) ;  // in amps I presume
    sum += current * current ;  // sum squares
    // no delay, make sure N large enough to cover many waveforms.
  }
  value = sqrt (sum / N) ;  // root-mean of squares
}


