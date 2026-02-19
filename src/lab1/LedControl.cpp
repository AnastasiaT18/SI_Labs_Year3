#include "LedControl.h"

LedControl::LedControl(int pin) {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);
  }
  
  void LedControl::turnOn() {
    digitalWrite(ledPin, HIGH);
  }
  
  void LedControl::turnOff() {
    digitalWrite(ledPin, LOW);
  }