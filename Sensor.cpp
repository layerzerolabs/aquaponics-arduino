#include "Sensor.h"

Sensor::Sensor(){}
int Sensor::read(){}
void Sensor::setup(){}  

String Sensor::getErrorMessage(int errorCode) {
    switch (errorCode) {
      case LOST_CONNECTION:
        return "Lost Connection";
      case BAD_DATA:
        return "Bad Data";
      case LOST_CONNECTION_OR_BAD_DATA:
        return "Lost Connection or Bad Data"; 
      default:
        return "Mysteriously Gone Wrong"; 
    }
}

