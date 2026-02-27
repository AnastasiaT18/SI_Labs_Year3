#ifndef BUTTONSENSOR_H
#define BUTTONSENSOR_H

#include <Arduino.h>

class ButtonSensor {
  private:
    int pin;
    bool wasPressed;
    unsigned long pressStartTime;

  public:
    ButtonSensor(int pin);
    unsigned long update();  // returns duration on release, 0 otherwise
};

#endif