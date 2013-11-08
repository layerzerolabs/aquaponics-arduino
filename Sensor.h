#include "Arduino.h"
#ifndef SENSOR_H
#define SENSOR_H


class Sensor {
    public:
        Sensor();
        virtual void setup();
	virtual int read();
        float value;
        char* name;
        const int OK = 0;
        const int LOST_CONNECTION = 1;
        const int BAD_DATA = 2;
        const int LOST_CONNECTION_OR_BAD_DATA = 3;
        const float arduinoVoltage = 4.93;
};


#endif
