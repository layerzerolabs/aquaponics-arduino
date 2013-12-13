#include "Sensor.h"
class ECSensor : public Sensor
{
  public:
    ECSensor(char name[]);
    void setup();
    int read();
  private:
    int pin;
    float total;
    const int numberOfSamples = 4096;
    const float minCond = 0.1;
    const int minFreq = 1124;
    const float maxCond = 2.8;
    const int maxFreq = 3194;
    const int enable_pin = 7;
    const int reading_pin = 8;
};
