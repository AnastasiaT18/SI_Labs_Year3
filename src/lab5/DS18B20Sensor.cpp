#include "DS18B20Sensor.h"

DS18B20Sensor::DS18B20Sensor(int pin)
    : _oneWire(pin), _sensors(&_oneWire) {}

void DS18B20Sensor::begin() {
    _sensors.begin();
}

float DS18B20Sensor::readTempC() {
    _sensors.requestTemperatures();          // send command to sensor
    return _sensors.getTempCByIndex(0);      // read first sensor on bus
}