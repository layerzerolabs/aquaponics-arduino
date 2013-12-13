#include "Arduino.h"
#ifndef SENSOR_H
#define SENSOR_H


class Sensor {
    public:
        Sensor();
        virtual void setup();
	virtual int read();
        String getErrorMessage(int errorCode);
        float value;
        char* name;
        static const int OK = 0;
        static const int LOST_CONNECTION = 1;
        static const int BAD_DATA = 2;
        static const int LOST_CONNECTION_OR_BAD_DATA = 3;
        const float arduinoVoltage = 4.93;
};


#endif
