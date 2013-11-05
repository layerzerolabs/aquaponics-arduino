#include "Arduino.h"
#include <OneWire.h>
#include <SPI.h>              // Needed for ethernet
#include <Ethernet.h>         // Ethernet library
#include <PubSubClient.h>     // mqtt library - nice work Nick O'Leary
#include "Sensor.h"
#include "TemperatureSensor.h"
#include "CurrentSensor.h"
#include "AnalogueWaterLevelSensor.h"
#include "DigitalWaterLevelSensor.h"

byte mac[]    = { 0x90, 0xA2, 0xDA, 0x0D, 0xc0, 0xAB };  // the arduino's mac address
byte ip[]     = { 172, 16, 1, 92 };                       // the arduino's ip address
byte server[] = { 172, 16, 1, 91 };                      // the mqtt server ip address

byte airTempAddress[] = {0x28, 0xFF, 0x00, 0x36, 0x05, 0x00, 0x00, 0x3C};
byte waterTempAddress[] = {0x28, 0x8A, 0xF9, 0x35, 0x05, 0x00, 0x00, 0x92};

int air1CurrentPin = A7;
int air2CurrentPin = A10;
int waterCurrentPin = A13;
int digitalWaterLevelPins[] = {3, 5, 6, 9}; // low to high
int analogueWaterLevelPin = A0;

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

void setup(void) {
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
}

void loop(void) {
  read(airTemp);
  read(waterTemp);
  read(air1Current);
  read(air2Current);
  read(waterCurrent);
  read(analogueWaterLevel);
  read(digitalWaterLevel);
  delay(500);
}

void read(Sensor &sensor) {
  char mqttOut[50];
  int returnCode = sensor.read();
  if (returnCode == sensor.LOST_CONNECTION){
    String errorMessage = String("Lost the ");
    errorMessage += sensor.name;
    Serial.println(errorMessage);
    errorMessage.toCharArray(mqttOut, 50);
    client.publish("system", mqttOut);
  } else if (returnCode == sensor.BAD_DATA) {
    Serial.println("BAD DATA");
  } else if (returnCode == sensor.OK) {
    Serial.print(sensor.name);
    Serial.print(": ");
    Serial.println(sensor.value);
    char output[10];
    dtostrf(sensor.value, 10, 2, output);
    client.publish(sensor.name, output);
    client.loop();
  }
}
