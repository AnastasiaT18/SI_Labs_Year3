#ifndef SHAREDDATA_H
#define SHAREDDATA_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// NTC sensor shared data
extern float g_ntcTempC;           // final weighted-averaged temp in °C
extern bool  g_ntcAlertActive;
extern int   g_ntcRaw;             // raw ADC value

// NEW: intermediate conditioning stages
extern int   g_ntcSaturated;       // after saturation
extern int   g_ntcMedian;          // after median filter
extern float g_ntcWeighted;        // weighted average (raw ADC units, before °C)

// DHT sensor shared data
extern float g_dhtTempC;
extern float g_dhtHumidity;
extern bool  g_dhtAlertActive;

// Synchronization
extern SemaphoreHandle_t xDataMutex;

#endif