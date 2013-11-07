#include "Sensor.h"

class pHSensor : public Sensor
{
  public:
    pHSensor(char name[]);
    void setup(int pin);
    int read();
  private:
    const int numberOfSamples = 50;
    int pin;
    const float phGain = 4000 / (59.2 * 7); // BNC sensor shield circuit max output: 4000mv
};
