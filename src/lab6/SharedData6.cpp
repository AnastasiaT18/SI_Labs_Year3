#ifdef RUN_LAB6

#include "SharedData6.h"

float g_ntcTempC        = 0.0f;
bool  g_ntcAlertActive  = false;
int   g_ntcRaw          = 0;

// NEW intermediates
int   g_ntcSaturated    = 0;
int   g_ntcMedian       = 0;
float g_ntcWeighted     = 0.0f;

float g_dhtTempC        = 0.0f;
float g_dhtHumidity     = 0.0f;
bool  g_dhtAlertActive  = false;

SemaphoreHandle_t xDataMutex = NULL;

#endif