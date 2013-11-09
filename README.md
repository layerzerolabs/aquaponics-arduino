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

* Temperature sensor depends on the [OneWire library](http://playground.arduino.cc/Learning/OneWire)
* Light sensor depends on the [Wire](http://arduino.cc/en/reference/wire), [Adafruit_Sensor](https://github.com/adafruit/Adafruit_Sensor) and [Adafruit_TSL2561](https://github.com/adafruit/Adafruit_TSL2561) libraries
* mqtt stuff in the main program depends on the [Arduino mqtt client](http://knolleary.net/arduino-client-for-mqtt/)
* Everything depends on the [Arduino software and environment](http://arduino.cc/en/Main/Software)!


## Attributions

Layer Zero Labs cannot claim credit for all of this code!
If you see your code in here and you're not on the following list, please tell us.

* Current sensor: We took the basic logic from MarkT's post on the [arduino forum](http://forum.arduino.cc/index.php?topic=168468.0;wap2)
* pH sensor: Code lifted from [macroduino](https://github.com/andrewoke/MacroDuino/blob/master/supportFunctions.h), with the unsigned int tweak suggested by Justin at [praticalmaker](http://www.practicalmaker.com/comment/3258#comment-3258)
* Temperature Sensor: Lifted from the DallasTemperature library by [Jordan Hochenbaum](http://jordanhochenbaum.com/)(?)  
* Code in main program that uses mqtt client follows example provided by [Nick O'Leary](http://knolleary.net/arduino-client-for-mqtt/) 
