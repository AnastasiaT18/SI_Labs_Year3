#ifndef SHARED_DATA_LAB6_1_H
#define SHARED_DATA_LAB6_1_H

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// Written by Task_FSM, read by Task_Report
extern volatile uint8_t g_fsmState;       // current FSM state index (0=OFF, 1=ON)
extern volatile bool    g_ledState;       // current LED output value
extern volatile bool    g_buttonPressed;  // last sampled button input

extern SemaphoreHandle_t xDataMutex;

#endif