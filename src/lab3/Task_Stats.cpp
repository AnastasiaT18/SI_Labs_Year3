#include "Task_Stats.h"
#include "SharedData.h"
#include <Arduino.h>

static LedControl* _ledY;

// blink state machine variables
static bool          blinking        = false;
static int           blinksRemaining = 0;
static bool          ledState        = false;
static unsigned long lastBlinkTime   = 0;
const  unsigned long BLINK_MS        = 100;

void Task_Stats_init(LedControl* ledY) {
    _ledY = ledY;
}

void Task_Stats(void) {
    // check if Task1 signaled a new press
    if (g_newPressAvailable) {
        g_newPressAvailable = false;  // consume flag

        // update global statistics
        g_totalPresses++;
        if (g_lastPressWasShort) {
            g_shortPresses++;
            g_sumShortDuration += g_lastPressDuration;
            blinksRemaining = 5 * 2;   // 5 blinks = 10 half-cycles
        } else {
            g_longPresses++;
            g_sumLongDuration += g_lastPressDuration;
            blinksRemaining = 10 * 2;  // 10 blinks = 20 half-cycles
        }

        blinking      = true;
        ledState      = false;
        lastBlinkTime = millis();

        printf("[T2] total=%lu short=%lu long=%lu\n", g_totalPresses, g_shortPresses, g_longPresses);

    }

    // non-blocking blink state machine
    // just checks time and flips LED, returns immediately
    if (blinking) {
        unsigned long now = millis();
        if (now - lastBlinkTime >= BLINK_MS) {
            lastBlinkTime = now;
            ledState = !ledState;
            ledState ? _ledY->turnOn() : _ledY->turnOff();
            if (--blinksRemaining <= 0) {
                blinking = false;
                _ledY->turnOff();
            }
        }
    }
}