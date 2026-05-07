#ifdef RUN_LAB11

#include "SharedData.h"

volatile uint8_t g_fsmState     = 0;      // initial: LED_OFF
volatile bool    g_ledState      = false;
volatile bool    g_buttonPressed = false;

SemaphoreHandle_t xDataMutex = NULL;

#endif