#ifdef RUN_LAB8

#include "Task_Report.h"
#include "SharedData.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>

static LCDDisplay* _lcd;

void Task_Report_init(LCDDisplay* lcd) {
    _lcd = lcd;
}

void Task_Report(void* pvParameters) {
    vTaskDelay(pdMS_TO_TICKS(1000));
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (true) {
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(2000));

        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        bool  relayState     = g_relayState;
        bool  relayAlert     = g_relayAlert;
        int   servoAngle     = g_servoAngle;
        int   servoSaturated = g_servoSaturated;
        int   servoMedian    = g_servoMedian;
        float servoWeighted  = g_servoWeighted;
        bool  servoAlert     = g_servoAlert;
        xSemaphoreGive(xDataMutex);

        // LCD: line 0 = relay, line 1 = servo final angle
        String line0 = "Relay:" + String(relayState ? "ON " : "OFF");
        if (relayAlert) line0 += "!";
        String line1 = "Servo:" + String(servoAngle) + "d";
        if (servoAlert) line1 += "!";

        _lcd->printLine(0, line0);
        _lcd->printLine(1, line1);

        // full serial report with conditioning pipeline values
        printf("=============================\n");
        printf("[RELAY] State: %s  Alert: %s\n",
            relayState ? "ON" : "OFF",
            relayAlert ? "YES" : "NO");
            int weightedInt = (int)(servoWeighted + 0.5f);
        printf("[SERVO] Saturated:%d Median:%d Weighted:%d Final:%d deg  Alert:%s\n",
            servoSaturated, servoMedian, weightedInt, servoAngle,
            servoAlert ? "YES(limit hit)" : "NO");
        printf("=============================\n\n");
    }
}

#endif