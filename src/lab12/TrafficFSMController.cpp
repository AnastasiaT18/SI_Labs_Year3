#include "TrafficFSMController.h"

// ── State table ────────────────────────────────────────────────────────────
// Moore FSM — 5 states, 1 input (NS request), 6 outputs (LED pins)
//
//  #  Name              EW:R,Y,G   NS:R,Y,G   Delay    In=0            In=1
//  0  EW_GREEN          0,0,1      1,0,0      100ms*   stay(0)         →1
//  1  EW_YELLOW         0,1,0      1,0,0      3000ms   →2              →2
//  2  EW_RED_NS_GREEN   1,0,0      0,0,1      5000ms   →3              →3
//  3  NS_YELLOW         1,0,0      0,1,0      3000ms   →4              →4
//  4  NS_RED_EW_GREEN   0,0,1      1,0,0      1000ms   →0              →0
//
// *State 0 uses a short 100ms poll loop so it can react to button quickly.
//  States 1-4 are committed — sequence runs to completion regardless of input.
//
// Format: { {ew_r,ew_y,ew_g, ns_r,ns_y,ns_g}, delay_ms, {next_no_req, next_req} }

const TrafficFSMState TrafficFSMController::_table[TF_NUM_STATES] = {
    // 0: EW_GREEN — EW has priority, polls for NS request every 100ms
    { {0,0,1, 1,0,0},  100,   { TF_EW_GREEN,        TF_EW_YELLOW       } },

    // 1: EW_YELLOW — committed, EW going yellow
    { {0,1,0, 1,0,0},  3000,  { TF_EW_RED_NS_GREEN, TF_EW_RED_NS_GREEN } },

    // 2: EW_RED_NS_GREEN — NS gets to cross
    { {1,0,0, 0,0,1},  5000,  { TF_NS_YELLOW,       TF_NS_YELLOW       } },

    // 3: NS_YELLOW — committed, NS going yellow
    { {1,0,0, 0,1,0},  3000,  { TF_NS_RED_EW_GREEN, TF_NS_RED_EW_GREEN } },

    // 4: NS_RED_EW_GREEN — brief overlap state, returns EW priority
    { {0,0,1, 1,0,0},  1000,  { TF_EW_GREEN,        TF_EW_GREEN        } },
};

TrafficFSMController::TrafficFSMController() : _currentState(TF_EW_GREEN) {}

void TrafficFSMController::reset() {
    _currentState = TF_EW_GREEN;
}

const TrafficOutput& TrafficFSMController::getOutput() const {
    return _table[_currentState].output;
}

uint32_t TrafficFSMController::getDelay() const {
    return _table[_currentState].delay_ms;
}

uint8_t TrafficFSMController::getState() const {
    return _currentState;
}

const char* TrafficFSMController::getStateName() const {
    switch (_currentState) {
        case TF_EW_GREEN:        return "EW_GREEN";
        case TF_EW_YELLOW:       return "EW_YELLOW";
        case TF_EW_RED_NS_GREEN: return "NS_GREEN";
        case TF_NS_YELLOW:       return "NS_YELLOW";
        case TF_NS_RED_EW_GREEN: return "EW_RESTORE";
        default:                 return "UNKNOWN";
    }
}

uint8_t TrafficFSMController::transition(uint8_t request) {
    if (request > 1) request = 1;
    _currentState = _table[_currentState].next[request];
    return _currentState;
}