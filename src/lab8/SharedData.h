#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// Relay shared data
extern volatile int  g_relayCommand;
extern volatile bool g_relayState;
extern volatile bool g_relayAlert;

// Motor shared data
extern volatile int   g_motorCommand;     // raw command 0-100%, -1=none
extern volatile int   g_motorSaturated;   // after saturation
extern volatile int   g_motorMedian;      // after median filter
extern volatile float g_motorWeighted;    // after weighted average
extern volatile int   g_motorSpeed;       // final applied speed % (after ramp)
extern volatile bool  g_motorAlert;       // true if limit was hit (saturated)

// Synchronization
extern SemaphoreHandle_t xDataMutex;

#endif