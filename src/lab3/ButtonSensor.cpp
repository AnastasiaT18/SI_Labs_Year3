#include "ButtonSensor.h"

ButtonSensor::ButtonSensor(int pin) {
    this->pin      = pin;
    wasPressed     = false;
    pressStartTime = 0;
    pinMode(pin, INPUT_PULLUP);
}

unsigned long ButtonSensor::update() {
    bool isPressed = (digitalRead(pin) == LOW);

    if (isPressed && !wasPressed) {
        pressStartTime = millis();
        wasPressed     = true;
        return 0;
    }

    if (!isPressed && wasPressed) {
        unsigned long duration = millis() - pressStartTime;
        wasPressed = false;
        if (duration >= 30) return duration;  // valid press
        return 0;                              // noise, ignore
    }

    return 0;
}