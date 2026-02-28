#include "Task_Button.h"
#include "SharedData.h"
#include <Arduino.h>

static ButtonSensor* _btn;
static LedControl*   _ledG;
static LedControl*   _ledR;

void Task_Button_init(ButtonSensor* btn,
                      LedControl* ledG,
                      LedControl* ledR) {
    _btn  = btn;
    _ledG = ledG;
    _ledR = ledR;
}

void Task_Button(void) {
    unsigned long duration = _btn->update();

    // nothing happened, return immediately (non-blocking)
    if (duration == 0) return;

    // save to global variables (as required by task spec)
    g_lastPressDuration = duration;
    g_lastPressWasShort = (duration < 500);
    g_newPressAvailable = true;  // signal Task2

    // visual feedback
    if (g_lastPressWasShort) {
        _ledG->turnOn();
        _ledR->turnOff();
    } else {
        _ledG->turnOff();
        _ledR->turnOn();
    }

    printf("[T1] %lums %s\n", duration, g_lastPressWasShort ? "SHORT" : "LONG");

}