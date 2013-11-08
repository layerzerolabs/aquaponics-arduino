#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561.h>
#include <OneWire.h>
#include <SPI.h>              // Needed for ethernet
#include <Ethernet.h>         // Ethernet library
#include <PubSubClient.h>     // mqtt library
#include "Sensor.h"
#include "TemperatureSensor.h"
#include "CurrentSensor.h"
#include "AnalogueWaterLevelSensor.h"
#include "DigitalWaterLevelSensor.h"
#include "LightSensor.h"
#include "pHSensor.h"

byte mac[]    = { 0x90, 0xA2, 0xDA, 0x0D, 0xc0, 0xAB };  // the arduino's mac address
byte ip[]     = { 172, 16, 1, 92 };                       // the arduino's ip address
byte server[] = { 172, 16, 1, 91 };                      // the mqtt server ip address

byte airTempAddress[] = {0x28, 0xFF, 0x00, 0x36, 0x05, 0x00, 0x00, 0x3C};
byte waterTempAddress[] = {0x28, 0x8A, 0xF9, 0x35, 0x05, 0x00, 0x00, 0x92};

int air1CurrentPin = A7;
int air2CurrentPin = A10;
int waterCurrentPin = A13;
int digitalWaterLevelPins[] = {3, 5, 6, 9}; // low to high
int analogueWaterLevelPin = A1;
int pHPin = A3;

void callback(char* topic, byte* payload, unsigned int length) {} // handle incoming mqtt

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);

TemperatureSensor        airTemp("Air Temperature");
TemperatureSensor        waterTemp("Water Temperature");
CurrentSensor            waterCurrent("Water Pump Current");
CurrentSensor            air1Current("Air Pump 1 Current");
CurrentSensor            air2Current("Air Pump 2 Current");
AnalogueWaterLevelSensor analogueWaterLevel("Analogue Water Level");
DigitalWaterLevelSensor  digitalWaterLevel("Digital Water Level");
LightSensor              light("Far Light");
pHSensor                 pH("pH");

void setup(void) {
  light.setup();
  Serial.begin(9600);
  Serial.println("Starting up");
  Ethernet.begin(mac, ip);
  if (client.connect("arduinoClient")) {
      Serial.println("mqtt setup OK"); 
      client.publish("system", "arduino starting");   
  }
  else {
      Serial.println("mqtt setup FAILED");
  }
  airTemp.setup(airTempAddress);
  waterTemp.setup(waterTempAddress);
  air1Current.setup(air1CurrentPin);
  air2Current.setup(air2CurrentPin);
  waterCurrent.setup(waterCurrentPin);
  analogueWaterLevel.setup(analogueWaterLevelPin);
  digitalWaterLevel.setup(digitalWaterLevelPins);
  light.setup();
  pH.setup(pHPin);
}

void loop(void) {
  read(airTemp);
  read(waterTemp);
  read(air1Current);
  read(air2Current);
  read(waterCurrent);
  read(analogueWaterLevel);
  read(digitalWaterLevel);
  read(light);
  read(pH);
  client.loop();
}

void read(Sensor &sensor) {
  String message  = String(sensor.name);
  char mqttOut[100];
  int returnCode = sensor.read();
  if (returnCode != sensor.OK) {
    if (returnCode == sensor.LOST_CONNECTION) {
      message += ": Lost Connection";
    } else if (returnCode == sensor.BAD_DATA) {
      message += ": Bad Data";
    } else if (returnCode == sensor.LOST_CONNECTION_OR_BAD_DATA) {
      message += ": Lost Connection or Bad Data"; 
    } else {
      message += ": Mysteriously Gone Wrong"; 
    }
    Serial.println(message);
    message.toCharArray(mqttOut, 100);
    client.publish("system", mqttOut);
  } else {
    Serial.print(sensor.name);
    Serial.print(": ");
    Serial.println(sensor.value);
    char reading[10];
    dtostrf(sensor.value, 10, 2, reading);
    client.publish(sensor.name, reading);
  }
}
