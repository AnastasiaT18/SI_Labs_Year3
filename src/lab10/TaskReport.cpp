#ifdef RUN_LAB10

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
        float pidOut = g_pidOutput;
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
            char spStr[8], tempStr[8], humStr[6];
            dtostrf(sp,   4, 1, spStr);
            dtostrf(temp, 4, 1, tempStr);
            dtostrf(hum,  3, 0, humStr);

            snprintf(line0, sizeof(line0), "SP:%s T:%sC", spStr, tempStr);
            snprintf(line1, sizeof(line1), "Rly:%s H:%s%%", relay ? "ON " : "OFF", humStr);
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
            char spStr[8], tempStr[8], outStr[8];
            dtostrf(sp,     5, 2, spStr);
            dtostrf(temp,   5, 2, tempStr);
            dtostrf(g_pidOutput, 6, 2, outStr);  // read g_pidOutput directly, it's volatile
            printf("SetPoint:%s Temperature:%s PID_Output:%s Relay:%d\n",
                spStr, tempStr, outStr, (int)relay);


        }
    }
}

#endif