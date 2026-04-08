#ifndef SHARED_DATA_LAB9_H
#define SHARED_DATA_LAB9_H

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// ── Mutex ─────────────────────────────────────────────────────────
extern SemaphoreHandle_t xDataMutex;

// ── Parameters (written by Task_Command, read by Task_Control) ────
extern volatile float g_setPoint;       // desired temperature °C
extern volatile float g_hysteresis;     // dead-band half-width  °C

// ── Sensor data (written by Task_Sensor) ─────────────────────────
extern volatile float g_temperature;    // latest DHT reading °C
extern volatile float g_humidity;       // latest DHT reading %
extern volatile bool  g_sensorError;    // true if last read failed

// ── Control output (written by Task_Control) ─────────────────────
extern volatile bool  g_relayState;     // current relay state

#endif