#ifndef NTCSENSOR_H
#define NTCSENSOR_H

#include <Arduino.h>

class NTCSensor {
private:
    int _pin;                    // analog pin number
    float rawToResistance(int raw);
    float resistanceToC(float resistance);

public:
    NTCSensor(int pin);
    void begin();
    int   readRaw();             // returns 0-1023
    float readTempC();           // returns temperature in °C
};

#endif