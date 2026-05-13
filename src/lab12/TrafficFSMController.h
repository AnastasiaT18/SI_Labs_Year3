#ifndef TRAFFIC_FSM_CONTROLLER_H
#define TRAFFIC_FSM_CONTROLLER_H

#include <Arduino.h>

// ── Traffic light output ───────────────────────────────────────────────────
// Defines the LED pattern for one intersection state.
// Each field is 0 (off) or 1 (on).
struct TrafficOutput {
    uint8_t ew_red;
    uint8_t ew_yellow;
    uint8_t ew_green;
    uint8_t ns_red;
    uint8_t ns_yellow;
    uint8_t ns_green;
};

// ── State table entry ──────────────────────────────────────────────────────
// output   - LED pattern for this state (Moore: output depends only on state)
// delay_ms - how long to stay in this state (state-specific dwell time)
// next[2]  - next[0] = no NS request, next[1] = NS request active
struct TrafficFSMState {
    TrafficOutput output;
    uint32_t      delay_ms;
    uint8_t       next[2];
};

// ── State index constants ──────────────────────────────────────────────────
#define TF_EW_GREEN         0   // EW green, NS red  — holds until request
#define TF_EW_YELLOW        1   // EW yellow, NS red — 3s committed
#define TF_EW_RED_NS_GREEN  2   // EW red, NS green  — 5s NS gets to go
#define TF_NS_YELLOW        3   // EW red, NS yellow — 3s committed
#define TF_NS_RED_EW_GREEN  4   // EW green, NS red  — 1s then back to 0
#define TF_NUM_STATES       5

// ── TrafficFSMController ───────────────────────────────────────────────────
// Pure Moore FSM — no FreeRTOS, no hardware knowledge.
// Caller applies outputs and waits the state delay.
class TrafficFSMController {
private:
    uint8_t _currentState;
    static const TrafficFSMState _table[TF_NUM_STATES];

public:
    TrafficFSMController();
    void                 reset();
    const TrafficOutput& getOutput()    const;
    uint32_t             getDelay()     const;
    uint8_t              getState()     const;
    const char*          getStateName() const;
    uint8_t              transition(uint8_t request); // request = 0 or 1
};

#endif