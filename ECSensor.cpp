#include "ECSensor.h"

ECSensor::ECSensor(char name[]) {
  this->name = name;
}

void ECSensor::setup() {
	pinMode(reading_pin, INPUT);
	pinMode(enable_pin, OUTPUT);
}

int ECSensor::read() {
	digitalWrite(enable_pin, HIGH);
	unsigned long freqhigh = 0;
	unsigned long freqlow = 0;
	unsigned long frequency = 0;
	for(unsigned int j=0; j<numberOfSamples; j++) {
		freqhigh+= pulseIn(reading_pin, HIGH, 250000);
		freqlow+= pulseIn(reading_pin, LOW, 250000);
	}
 
	frequency = 1000000 / ( (freqhigh / numberOfSamples) + (freqlow / numberOfSamples) );
	float m = (maxFreq - minFreq) / (maxCond - minCond);
	float b = minFreq - (m * minCond);
	value = ((float)frequency - b) / m;
	digitalWrite(enable_pin, LOW);
        return OK;
}
