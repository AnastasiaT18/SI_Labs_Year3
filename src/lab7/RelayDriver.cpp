#include "RelayDriver.h"

RelayDriver::RelayDriver(int pin) : _pin(pin), _state(false) {
}

void RelayDriver::begin(){
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW); // Ensure relay is off at startup
}

void RelayDriver::turnOn() {
    _state = true;
    digitalWrite(_pin, HIGH);
}

void RelayDriver::turnOff() {
    _state = false;
    digitalWrite(_pin, LOW);
}

bool RelayDriver::getState() {
    return _state;
}