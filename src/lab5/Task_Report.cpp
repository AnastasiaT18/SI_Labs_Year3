#ifdef RUN_LAB5
#include "Task_Report.h"
#include "SharedData5.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>

// Helper: AVR printf doesn't support %f, so we split into whole + decimal parts
// e.g. 22.75 → whole=22, dec=75
static void printTemp(float temp) {
    if (temp < -100.0) {
        // -127 means DS18B20 failed to read
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

void Task_Report_init() {
    // nothing to initialize
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
        float dsTemp   = g_dsTempC;
        bool  dsAlert  = g_dsAlertActive;
        xSemaphoreGive(xDataMutex);

        // print combined report
        printf("========================================\n");
        printf("[NTC]  Raw: %4d | Temp: ", ntcRaw);
        printTemp(ntcTemp);
        printf(" C | Alert: %s\n", ntcAlert ? "!!! HIGH !!!" : "OK");

        printf("[DS18] Temp: ");
        printTemp(dsTemp);
        printf(" C | Alert: %s\n", dsAlert ? "!!! HIGH !!!" : "OK");

        printf("  Thresholds: LOW=24.0C  HIGH=26.0C\n");
        printf("========================================\n");
    }
}
#endif