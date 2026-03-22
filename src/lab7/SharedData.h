
#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// Relay shared data
extern volatile int  g_relayCommand;    // requested state: 0=OFF, 1=ON, -1=none
extern volatile bool g_relayState;      // confirmed current state
extern volatile bool g_relayAlert;      // true if state changed

// Servo shared data
extern volatile int  g_servoCommand;    // requested angle 0-180, -1=none
extern volatile int  g_servoAngle;      // confirmed current angle

// Synchronization
extern SemaphoreHandle_t xDataMutex;

#endif