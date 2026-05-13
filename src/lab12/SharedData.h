#ifndef SHARED_DATA_TRAFFIC_H
#define SHARED_DATA_TRAFFIC_H

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// ── Written by Task_Button, read by Task_TrafficFSM ───────────────────────
extern volatile bool g_nsRequest;      // NS crossing request (set on button press, cleared after FSM consumes it)

// ── Written by Task_TrafficFSM, read by Task_Report ──────────────────────
extern volatile uint8_t g_fsmState;   // current FSM state index
extern volatile bool    g_ewGreen;    // true when EW direction is green
extern volatile bool    g_nsGreen;    // true when NS direction is green

extern SemaphoreHandle_t xDataMutex;  // protects all shared variables above

#endif