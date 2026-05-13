#ifndef LED_BANK_H
#define LED_BANK_H

#include "lab1/LedControl.h"
#include "TrafficFSMController.h"

// ── TrafficLedBank ─────────────────────────────────────────────────────────
// Wraps 6 LedControl instances (reused from Part 1) for a full intersection.
// Applies a TrafficOutput struct to all 6 LEDs in a single call.
//
// EW direction: red, yellow, green
// NS direction: red, yellow, green
class TrafficLedBank {
private:
    LedControl _ew_red;
    LedControl _ew_yellow;
    LedControl _ew_green;
    LedControl _ns_red;
    LedControl _ns_yellow;
    LedControl _ns_green;

public:
    TrafficLedBank(int ew_red, int ew_yellow, int ew_green,
                   int ns_red, int ns_yellow, int ns_green);

    void apply(const TrafficOutput& out);  // set all 6 LEDs from FSM output
    void allOff();                         // turn everything off (safety)
};

#endif