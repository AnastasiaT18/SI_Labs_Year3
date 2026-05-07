#ifndef FSM_CONTROLLER_H
#define FSM_CONTROLLER_H

#include <Arduino.h>

// ── State table entry ──────────────────────────────────────────────────────
// Each row directly mirrors Table 7.1 from the course theory:
//   output   - LED value for this state (0 = off, 1 = on)
//   delay_ms - how long to dwell in this state before sampling input
//   next[2]  - next[0] = input not pressed, next[1] = input pressed
struct FSMState {
    uint8_t  output;
    uint32_t delay_ms;
    uint8_t  next[2];
};

// ── State index constants ──────────────────────────────────────────────────
#define FSM_STATE_LED_OFF  0
#define FSM_STATE_LED_ON   1
#define FSM_NUM_STATES     2

// ── FSMController ──────────────────────────────────────────────────────────
// Encapsulates the Moore FSM state table and transition logic.
// Has NO knowledge of FreeRTOS, hardware, or any driver.
// Caller is responsible for applying output and waiting the state delay.
class FSMController {
private:
    uint8_t _currentState;
    static const FSMState _table[FSM_NUM_STATES];

public:
    FSMController();
    void     reset();                   // go back to LED_OFF state
    uint8_t  getOutput()    const;      // output = f(state) — Moore
    uint32_t getDelay()     const;      // dwell time for current state
    uint8_t  getState()     const;      // current state index
    const char* getStateName() const;   // human-readable name
    uint8_t  transition(uint8_t input); // step FSM: input = 0 or 1
};

#endif