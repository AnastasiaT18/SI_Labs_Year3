#ifdef RUN_LAB9

#include "TaskReport.h"
#include "SharedData.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>

static LCDDisplay* _lcd;

void Task_Report_init(LCDDisplay* lcd) {
    _lcd = lcd;
}

void Task_Report(void* pvParameters) {
    // Stagger slightly so control runs first
    vTaskDelay(pdMS_TO_TICKS(2500));

    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (true) {
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(2000));

        // Snapshot shared data
        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        float temp      = g_temperature;
        float hum       = g_humidity;
        float sp        = g_setPoint;
        float hys       = g_hysteresis;
        bool  relay     = g_relayState;
        bool  sensorErr = g_sensorError;
        xSemaphoreGive(xDataMutex);

        // ── LCD ───────────────────────────────────────────────────
        // Line 0:  "SP:28.0 T:25.3C"
        // Line 1:  "Relay:ON  H:55%"
        char line0[17], line1[17];
        if (sensorErr) {
            snprintf(line0, sizeof(line0), "Sensor ERROR    ");
            snprintf(line1, sizeof(line1), "SP:%-5.1f        ", sp);
        } else {
            snprintf(line0, sizeof(line0), "SP:%-4.1f T:%-4.1fC", sp, temp);
            snprintf(line1, sizeof(line1), "Relay:%-3s H:%2.0f%%",
                relay ? "ON " : "OFF", hum);
        }
        _lcd->printLine(0, line0);
        _lcd->printLine(1, line1);

        // ── Serial Plotter ────────────────────────────────────────
        // Arduino Serial Plotter graphs every comma-separated value.
        // Label:value format keeps the legend readable.
        if (sensorErr) {
            printf("SENSOR_ERR\n");
        } else {
            // Header is printed once in setup; values every tick
            printf("SetPoint:%.2f Temperature:%.2f Relay:%d\n", sp, temp, (int)relay);
            // printf("%.2f,%.2f,%d\n", sp, temp, (int)relay);


        }
    }
}

#endif