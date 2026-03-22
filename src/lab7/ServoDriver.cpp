#include "ServoDriver.h"

ServoDriver::ServoDriver(int pin) : _pin(pin), _angle(0) {}

void ServoDriver::begin() {
    _servo.attach(_pin);
    _servo.write(0);
}

void ServoDriver::setAngle(int angle) {
    // saturate to valid range
    if (angle < 0)   angle = 0;
    if (angle > 180) angle = 180;
    _angle = angle;
    _servo.write(_angle);
}

int ServoDriver::getAngle() {
    return _angle;
}