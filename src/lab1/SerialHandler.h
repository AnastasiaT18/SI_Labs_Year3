#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <Arduino.h>
#include "LedControl.h"

class SerialHandler {
  private:
    LedControl* led;
  public:
    SerialHandler(LedControl* ledModule);
    void checkCommands();
};

#endif
