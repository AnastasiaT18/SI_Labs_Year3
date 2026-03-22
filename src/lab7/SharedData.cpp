#ifdef RUN_LAB7

#include "SharedData.h"

volatile int  g_relayCommand = -1;
volatile bool g_relayState   = false;
volatile bool g_relayAlert   = false;
volatile int  g_servoCommand = -1;
volatile int  g_servoAngle   = 0;

SemaphoreHandle_t xDataMutex = NULL;

#endif