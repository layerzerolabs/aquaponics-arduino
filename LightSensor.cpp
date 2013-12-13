#include "LightSensor.h"

LightSensor::LightSensor(char name[]) {
  this->name = name;
}

void LightSensor::setup() {
  tsl = new Adafruit_TSL2561(TSL2561_ADDR_FLOAT, 12345);
  /* You can also manually set the gain or enable auto-gain support */
  // tsl.setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
  // tsl.setGain(TSL2561_GAIN_16X);     /* 16x gain ... use in low light to boost sensitivity */
  tsl->enableAutoGain(true);          /* Auto-gain ... switches automatically between 1x and 16x */
  
  /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
  tsl->setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
  // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
  // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */
}

int LightSensor::read() {
  sensors_event_t event;
  tsl->getEvent(&event);
  value = event.light;
  return value ? OK : LOST_CONNECTION_OR_BAD_DATA;
}


