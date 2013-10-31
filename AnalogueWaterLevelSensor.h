#include "Sensor.h"
class AnalogueWaterLevelSensor : public Sensor
{
  public:
    AnalogueWaterLevelSensor(char name[]);
    void setup(int pin);
    int read();
  private:
    int pin;
    float total;
};
