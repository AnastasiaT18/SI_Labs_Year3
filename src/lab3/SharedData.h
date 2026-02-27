#ifndef SHAREDDATA_H
#define SHAREDDATA_H

#include <Arduino.h>

// Task1 → Task2
extern unsigned long g_lastPressDuration;
extern bool          g_newPressAvailable;
extern bool          g_lastPressWasShort;

// Task2 → Task3
extern unsigned long g_totalPresses;
extern unsigned long g_shortPresses;
extern unsigned long g_longPresses;
extern unsigned long g_sumShortDuration;
extern unsigned long g_sumLongDuration;

#endif