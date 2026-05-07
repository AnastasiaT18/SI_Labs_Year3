#ifdef RUN_LAB10

#include "SharedData.h"

SemaphoreHandle_t xDataMutex = NULL;

volatile float g_setPoint  = 26.0f;   
volatile float g_hysteresis = 0.5f;   // unchanged

volatile float g_temperature = 0.0f;
volatile float g_humidity    = 0.0f;
volatile bool  g_sensorError = false;

volatile bool  g_relayState  = false;

volatile float g_Kp = 2.0f;
volatile float g_Ki = 0.1f;
volatile float g_Kd = 1.0f;

volatile float g_pidOutput = 0.0f;

#endif