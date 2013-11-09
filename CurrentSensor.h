#include "Sensor.h"

class CurrentSensor : public Sensor
{
  public:
    CurrentSensor(char name[]);
    void setup(int pin, float multiplier, float offset);
    int read();
  private:
    int pin;
    float multiplier; // Resolution factor
    int offset; // Raw value when no current
    const int numberOfSamples = 1000;
};
