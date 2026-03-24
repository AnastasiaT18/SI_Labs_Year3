#ifdef RUN_LAB8

#include "SharedData.h"

volatile int  g_relayCommand   = -1;
volatile bool g_relayState     = false;
volatile bool g_relayAlert     = false;

volatile int   g_servoCommand  = -1;
volatile int   g_servoSaturated = 0;
volatile int   g_servoMedian   = 0;
volatile float g_servoWeighted = 0.0f;
volatile int   g_servoAngle    = 0;
volatile bool  g_servoAlert    = false;

SemaphoreHandle_t xDataMutex = NULL;

#endif