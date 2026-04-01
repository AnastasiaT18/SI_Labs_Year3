#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <Arduino.h>

class MotorDriver {
private:
    int _pinENA;  // PWM speed pin
    int _pinIN1;  // direction pin 1
    int _pinIN2;  // direction pin 2
    int _speed;   // current speed 0-100%
public:
    MotorDriver(int pinENA, int pinIN1, int pinIN2);
    void begin();
    void setSpeed(int percent); // 0-100%
    int  getSpeed();
};

#endif