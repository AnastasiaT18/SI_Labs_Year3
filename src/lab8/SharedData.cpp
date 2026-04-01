#ifdef RUN_LAB8

#include "SharedData.h"

volatile int  g_relayCommand   = -1;
volatile bool g_relayState     = false;
volatile bool g_relayAlert     = false;

volatile int   g_motorCommand   = -1;
volatile int   g_motorSaturated = 0;
volatile int   g_motorMedian    = 0;
volatile float g_motorWeighted  = 0.0f;
volatile int   g_motorSpeed     = 0;
volatile bool  g_motorAlert     = false;

SemaphoreHandle_t xDataMutex = NULL;

#endif