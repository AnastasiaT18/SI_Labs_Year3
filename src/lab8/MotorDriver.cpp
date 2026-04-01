#include "MotorDriver.h"

MotorDriver::MotorDriver(int pinENA, int pinIN1, int pinIN2)
    : _pinENA(pinENA), _pinIN1(pinIN1), _pinIN2(pinIN2), _speed(0) {}

void MotorDriver::begin() {
    pinMode(_pinENA, OUTPUT);
    pinMode(_pinIN1, OUTPUT);
    pinMode(_pinIN2, OUTPUT);

    // set direction forward
    digitalWrite(_pinIN1, HIGH);
    digitalWrite(_pinIN2, LOW);

    // motor off at startup
    analogWrite(_pinENA, 0);
}

void MotorDriver::setSpeed(int percent) {
    if (percent < 0)   percent = 0;
    if (percent > 100) percent = 100;
    _speed = percent;

    int pwm = (int)((percent / 100.0f) * 255.0f);
    analogWrite(_pinENA, pwm);
}

int MotorDriver::getSpeed() {
    return _speed;
}