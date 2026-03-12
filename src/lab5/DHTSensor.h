#ifndef DHTSENSOR_H
#define DHTSENSOR_H

#include <Arduino.h>
#include <DHT.h>

class DHTSensor {
private:
    DHT _dht;

public:
    DHTSensor(int pin);
    void begin();
    float readTempC();      // returns temperature in °C
    float readHumidity();   // returns relative humidity %
};

#endif