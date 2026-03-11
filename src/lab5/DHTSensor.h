#ifndef DHTSENSOR_H
#define DHTSENSOR_H
#include <Arduino.h>
#include <DHT.h>

class DHTSensor {
private:
    DHT _dht;
public:
    DHTSensor(int pin) : _dht(pin, DHT11) {}
    void begin() { _dht.begin(); }
    float readTempC() { return _dht.readTemperature(); }
};
#endif