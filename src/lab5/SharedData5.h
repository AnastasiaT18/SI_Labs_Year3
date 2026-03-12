#ifndef SHAREDDATA_H
#define SHAREDDATA_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// NTC sensor shared data
extern float g_ntcTempC;          // current temperature in °C
extern bool  g_ntcAlertActive;    // is alert currently confirmed ON?
extern int   g_ntcRaw;            // raw ADC value (for debugging)


extern float g_dhtTempC;
extern float g_dhtHumidity;
extern bool  g_dhtAlertActive;

// Synchronization
extern SemaphoreHandle_t xDataMutex;  // protects all shared variables above

#endif