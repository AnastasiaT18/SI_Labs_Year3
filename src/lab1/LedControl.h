#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#include <Arduino.h>

class LedControl {
  private:
    int ledPin;
  public:
    LedControl(int pin);
    void turnOn();
    void turnOff();
};

#endif
