#include <OneWire.h>
#include "Sensor.h"

class TemperatureSensor : public Sensor
{
  public:
    TemperatureSensor(char name[]);
    void setup(byte address[]);
    int read();
  private:
    OneWire* _oneWire;
    byte* address;
};
