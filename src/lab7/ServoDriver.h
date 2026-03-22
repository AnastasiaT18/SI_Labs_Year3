#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H

#include <Arduino.h>
#include <Servo.h>

class ServoDriver {
private:
    Servo _servo;
    int _pin;
    int _angle;
public:
    ServoDriver(int pin);
    void begin();
    void setAngle(int angle);
    int getAngle();
};

#endif