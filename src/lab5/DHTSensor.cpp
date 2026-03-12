#include "DHTSensor.h"

DHTSensor::DHTSensor(int pin)
    : _dht(pin, DHT11) {}

void DHTSensor::begin() {
    _dht.begin();
}

float DHTSensor::readTempC() {
    return _dht.readTemperature();   // returns NaN on failure
}

float DHTSensor::readHumidity() {
    return _dht.readHumidity();
}