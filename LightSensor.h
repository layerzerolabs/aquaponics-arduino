#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561.h>
#include "Sensor.h"

class LightSensor : public Sensor
{
  public:
    LightSensor(char name[]);
    void setup();
    int read();
  private:
    Adafruit_TSL2561* tsl;
};
