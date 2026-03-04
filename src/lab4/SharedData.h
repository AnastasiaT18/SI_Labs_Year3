#ifndef SHAREDDATA_H
#define SHAREDDATA_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

//same as Lab 2.1
extern unsigned long g_lastPressDuration;
extern bool          g_lastPressWasShort;

//removed  g_newPressAvailable

extern unsigned long g_totalPresses;
extern unsigned long g_shortPresses;
extern unsigned long g_longPresses;
extern unsigned long g_sumShortDuration;
extern unsigned long g_sumLongDuration;

//new
extern SemaphoreHandle_t xPressEvent;  
extern SemaphoreHandle_t xDataMutex;

#endif