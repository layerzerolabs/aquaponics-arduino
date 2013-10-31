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
        int LOST_CONNECTION = 1;
        int BAD_DATA = 2;
        int OK = 0;
};


#endif
