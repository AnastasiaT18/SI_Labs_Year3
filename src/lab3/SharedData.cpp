#include "SharedData.h"

unsigned long g_lastPressDuration = 0;
bool          g_newPressAvailable = false;
bool          g_lastPressWasShort = false;

unsigned long g_totalPresses     = 0;
unsigned long g_shortPresses     = 0;
unsigned long g_longPresses      = 0;
unsigned long g_sumShortDuration = 0;
unsigned long g_sumLongDuration  = 0;