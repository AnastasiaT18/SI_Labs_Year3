#ifndef RELAY_DRIVER_H
#define RELAY_DRIVER_H

#include <Arduino.h>

class RelayDriver {
private:
    int _pin;
public:
    RelayDriver(int pin);
    void begin();
    void turnOn();
    void turnOff();
    bool getState();
private:
    bool _state;
};

#endif