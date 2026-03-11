#ifndef DS18B20SENSOR_H
#define DS18B20SENSOR_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

class DS18B20Sensor {
private:
    OneWire        _oneWire;
    DallasTemperature _sensors;

public:
    DS18B20Sensor(int pin);
    void begin();
    float readTempC();   // returns temperature in °C directly
};

#endif