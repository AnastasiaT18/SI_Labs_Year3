#ifdef RUN_LAB4

#include "SharedData.h"

//same as Lab 2.1
unsigned long g_lastPressDuration = 0;
bool          g_lastPressWasShort = false;
//removed  g_newPressAvailable = false;


unsigned long g_totalPresses     = 0;
unsigned long g_shortPresses     = 0;
unsigned long g_longPresses      = 0;
unsigned long g_sumShortDuration = 0;
unsigned long g_sumLongDuration  = 0;

//new
SemaphoreHandle_t xPressEvent = NULL;
SemaphoreHandle_t xDataMutex  = NULL;

#endif