#ifdef RUN_LAB6


#include "Task_Report.h"
#include "SharedData6.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>
#include <math.h>

static void printTemp(float temp) {
    if (isnan(temp) || temp < -100.0) {
        printf("ERR");
        return;
    }
    bool negative = (temp < 0);
    if (negative) temp = -temp;
    int whole = (int)temp;
    int dec   = (int)((temp - whole) * 100);
    if (negative) printf("-");
    printf("%d.%02d", whole, dec);
}

static LedControl* _ledNTC;
static LedControl* _ledDHT;

void Task_Report_init(LedControl* ledNTC, LedControl* ledDHT) {
    _ledNTC = ledNTC;
    _ledDHT = ledDHT;
}

void Task_Report(void* pvParameters) {

    vTaskDelay(pdMS_TO_TICKS(1000));

    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (true) {
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(2000));

        // --- READ ALL SHARED DATA UNDER MUTEX ---
        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        int   ntcRaw       = g_ntcRaw;
        int   ntcSat       = g_ntcSaturated;
        int   ntcMed       = g_ntcMedian;
        float ntcWeighted  = g_ntcWeighted;
        float ntcTemp      = g_ntcTempC;
        bool  ntcAlert     = g_ntcAlertActive;
        float dhtTemp      = g_dhtTempC;
        float dhtHumidity  = g_dhtHumidity;
        bool  dhtAlert     = g_dhtAlertActive;
        xSemaphoreGive(xDataMutex);

        // --- LED CONTROL ---
        if (ntcAlert) _ledNTC->turnOn(); else _ledNTC->turnOff();
        if (dhtAlert) _ledDHT->turnOn(); else _ledDHT->turnOff();

        // --- PRINT REPORT ---
        printf("========================================\n");

        // NTC: show full conditioning pipeline
        printf("[NTC] 1. Raw ADC:    %4d\n", ntcRaw);
        printf("[NTC] 2. Saturated:  %4d  (limit %d-%d)\n", ntcSat, 100, 900);
        printf("[NTC] 3. Median:     %4d  (spike removed)\n", ntcMed);
        printf("[NTC] 4. Weighted:   "); printTemp(ntcWeighted);
        printf("  (smoothed ADC)\n");
        printf("[NTC] 5. Temp:       "); printTemp(ntcTemp);
        printf(" C\n");
        printf("[NTC] 6. Alert:      %s\n", ntcAlert ? "!!! HIGH !!!" : "OK");

        printf("----------------------------------------\n");

        // DHT11: digital sensor, no analog conditioning needed
        printf("[DHT11] Temp:  "); printTemp(dhtTemp);
        printf(" C\n");
        int humW = (int)dhtHumidity;
        int humD = (int)((dhtHumidity - humW) * 100);
        printf("[DHT11] Hum:   %d.%02d%%\n", humW, humD);
        printf("[DHT11] Alert: %s\n", dhtAlert ? "!!! HIGH !!!" : "OK");

        printf("----------------------------------------\n");
        printf("Thresholds: LOW=24.0C  HIGH=26.0C\n");
        printf("========================================\n\n");
    }
}

#endif