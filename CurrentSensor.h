#include "Sensor.h"
class CurrentSensor : public Sensor
{
  public:
    CurrentSensor(char name[]);
    void setup(int pin);
    int read();
  private:
    int pin;
    float total;
};
