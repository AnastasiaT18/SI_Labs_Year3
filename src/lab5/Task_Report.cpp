#ifdef RUN_LAB5
#include "Task_Report.h"
#include "SharedData5.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>

// Helper: AVR printf doesn't support %f, so we split into whole + decimal parts
// e.g. 22.75 → whole=22, dec=75
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
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (true) {
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(500));

        // read shared data safely under mutex
        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        float ntcTemp  = g_ntcTempC;
        int   ntcRaw   = g_ntcRaw;
        bool  ntcAlert = g_ntcAlertActive;
        float dhtTemp = g_dhtTempC;
        float dhtHumidity = g_dhtHumidity;
        bool  dhtAlert = g_dhtAlertActive;
        xSemaphoreGive(xDataMutex);

        if (ntcAlert) _ledNTC->turnOn();
        else          _ledNTC->turnOff();

        if (dhtAlert) _ledDHT->turnOn();
        else          _ledDHT->turnOff();

        // print combined report
        printf("========================================\n");
        printf("[NTC]  Raw: %4d | Temp: ", ntcRaw);
        printTemp(ntcTemp);
        printf(" C | Alert: %s\n", ntcAlert ? "!!! HIGH !!!" : "OK");

        printf("[DHT22] Temp: ");
        printTemp(dhtTemp);
        int humWhole = (int)dhtHumidity;
        int humDec   = (int)((dhtHumidity - humWhole) * 100);
        printf(" C | Hum: %d.%02d%% | Alert: %s\n",
            humWhole, humDec, dhtAlert ? "!!! HIGH !!!" : "OK");

        printf("  Thresholds: LOW=24.0C  HIGH=26.0C\n");
        printf("========================================\n");
    }
}

#endif