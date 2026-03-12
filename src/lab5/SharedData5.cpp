#ifdef RUN_LAB5

#include "SharedData5.h"

float g_ntcTempC       = 0.0;
bool  g_ntcAlertActive = false;
int   g_ntcRaw         = 0;

float g_dhtTempC       = 0.0;
float g_dhtHumidity    = 0.0;
bool  g_dhtAlertActive = false;

SemaphoreHandle_t xDataMutex = NULL;

#endif