#ifdef RUN_LAB9

#include "SharedData.h"

SemaphoreHandle_t xDataMutex = NULL;

volatile float g_setPoint  = 32.0f;   // ~10°C above room temp, reachable by a small resistor
volatile float g_hysteresis = 1.0f;   // unchanged

volatile float g_temperature = 0.0f;
volatile float g_humidity    = 0.0f;
volatile bool  g_sensorError = false;

volatile bool  g_relayState  = false;

#endif