#ifdef RUN_LAB5
#include "Task_NTC.h"
#include "SharedData5.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#define THRESHOLD_HIGH   26.0
#define THRESHOLD_LOW    24.0
#define DEBOUNCE_MAX     5

static NTCSensor* _sensor;
static int debounceCounter = 0;
static bool confirmedAlert = false;

void Task_NTC_init(NTCSensor* sensor) {
    _sensor = sensor;
}

void Task_NTC(void* pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (true) {
        // --- ACQUISITION ---
        int   raw   = _sensor->readRaw();
        float tempC = _sensor->readTempC();
        // NOTE: NTC in a voltage divider is INVERTED —
        // higher temperature = lower resistance = lower raw ADC value
        // BUT readTempC() already handles this math correctly via the
        // Steinhart-Hart equation, so tempC is already the real temperature.
        // We compare tempC directly — no inversion needed here.

        // --- THRESHOLD WITH HYSTERESIS ---
        bool rawAlert;
        if      (tempC > THRESHOLD_HIGH) rawAlert = true;
        else if (tempC < THRESHOLD_LOW)  rawAlert = false;
        else                             rawAlert = confirmedAlert; // stay

        // --- DEBOUNCE COUNTER ---
        if (rawAlert) debounceCounter = min(debounceCounter + 1, DEBOUNCE_MAX);
        else          debounceCounter = max(debounceCounter - 1, 0);

        if      (debounceCounter >= DEBOUNCE_MAX) confirmedAlert = true;
        else if (debounceCounter == 0)             confirmedAlert = false;

        // --- WRITE TO SHARED DATA ---
        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        g_ntcTempC       = tempC;
        g_ntcRaw         = raw;
        g_ntcAlertActive = confirmedAlert;
        xSemaphoreGive(xDataMutex);

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(50));
    }
}
#endif