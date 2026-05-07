#include "FSMController.h"

// ── State table ────────────────────────────────────────────────────────────
// Directly mirrors course Table 7.1:
//
//  State#  Name      Output  Delay   In=0 (released)  In=1 (pressed)
//    0     LED_OFF     0     100ms       0 (stay)         1 (→ ON)
//    1     LED_ON      1     100ms       1 (stay)         0 (→ OFF)
//
// Format: { output, delay_ms, { next_if_not_pressed, next_if_pressed } }
const FSMState FSMController::_table[FSM_NUM_STATES] = {
    { 0, 100, { FSM_STATE_LED_OFF, FSM_STATE_LED_ON  } },   // state 0: LED_OFF
    { 1, 100, { FSM_STATE_LED_ON,  FSM_STATE_LED_OFF } },   // state 1: LED_ON
};

FSMController::FSMController() : _currentState(FSM_STATE_LED_OFF) {}

void FSMController::reset() {
    _currentState = FSM_STATE_LED_OFF;
}

uint8_t FSMController::getOutput() const {
    return _table[_currentState].output;
}

uint32_t FSMController::getDelay() const {
    return _table[_currentState].delay_ms;
}

uint8_t FSMController::getState() const {
    return _currentState;
}

const char* FSMController::getStateName() const {
    return (_currentState == FSM_STATE_LED_ON) ? "LED_ON" : "LED_OFF";
}

uint8_t FSMController::transition(uint8_t input) {
    if (input > 1) input = 1;
    _currentState = _table[_currentState].next[input];
    return _currentState;
}