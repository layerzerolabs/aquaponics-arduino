aquaponics
==========

arduino part of aquaponics control system

* Reads various sensors
* Publishes readings over mqtt

## Structure
Each type of sensor (e.g. LightSensor, CurrentSensor) has its own class. These classes inherit from the Sensor class.
Every sensor instance must have a name, which is used as the topic for mqtt communications. This is passed into the constructor when the instance is created.
If a type of sensor needs another configuration element such as a pin or hardware address, these are specified as parameters to its setup() method.
The structure is intended to be extensible - if you want to add more sensors, just create classes for them that inherit from the Sensor class and reference them in the AquaSensors sketch following the example of the existing ones.

## Dependencies
Temperature sensor depends on the OneWire library
Light sensor depends on the Wire, Adafruit_Sensor and Adafruit_TSL2561 libraries
Everything depends on the Arduino library!

