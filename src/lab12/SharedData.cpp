#ifdef RUN_LAB12

#include "SharedData.h"

volatile bool    g_nsRequest  = false;
volatile uint8_t g_fsmState   = 0;      // initial: TF_EW_GREEN
volatile bool    g_ewGreen    = true;
volatile bool    g_nsGreen    = false;

SemaphoreHandle_t xDataMutex  = NULL;

#endif