#include "Sensor.h"
class DigitalWaterLevelSensor : public Sensor
{
  public:
    DigitalWaterLevelSensor(char name[]);
    void setup(int pins[]);
    int read();
  private:
    int* pins;
    float total;
};
