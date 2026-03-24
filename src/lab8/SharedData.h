#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// Relay shared data
extern volatile int  g_relayCommand;
extern volatile bool g_relayState;
extern volatile bool g_relayAlert;

// Servo shared data
extern volatile int   g_servoCommand;     // raw command from Task_Command (0-180)
extern volatile int   g_servoSaturated;   // after saturation
extern volatile int   g_servoMedian;      // after median filter
extern volatile float g_servoWeighted;    // after weighted average
extern volatile int   g_servoAngle;       // final applied angle (after ramp)
extern volatile bool  g_servoAlert;       // true if limit was hit (saturated)

// Synchronization
extern SemaphoreHandle_t xDataMutex;

#endif