#include "Sensor.h"
class AnalogueWaterLevelSensor : public Sensor
{
  public:
    AnalogueWaterLevelSensor(char name[]);
    void setup(int pin);
    int read();
  private:
    int pin;
    const float fullReading = 614;
    const float emptyReading = 704;
    const float cmRange = 15;
    const float unit = (emptyReading - fullReading) / cmRange;
    const int cmBottom = 5;
};
