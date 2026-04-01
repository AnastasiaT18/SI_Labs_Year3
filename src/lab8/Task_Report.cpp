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
        int   motorSpeed     = g_motorSpeed;
        int   motorSaturated = g_motorSaturated;
        int   motorMedian    = g_motorMedian;
        float motorWeighted  = g_motorWeighted;
        bool  motorAlert     = g_motorAlert;
        xSemaphoreGive(xDataMutex);

        // LCD line 0 = relay, line 1 = motor speed
        String line0 = "Relay:" + String(relayState ? "ON " : "OFF");
        if (relayAlert) line0 += "!";
        String line1 = "Motor:" + String(motorSpeed) + "%";
        if (motorAlert) line1 += "!";

        _lcd->printLine(0, line0);
        _lcd->printLine(1, line1);

        // full serial report
        printf("=============================\n");
        printf("[RELAY] State: %s  Alert: %s\n",
            relayState ? "ON" : "OFF",
            relayAlert ? "YES" : "NO");
        int weightedInt = (int)(motorWeighted + 0.5f);
        printf("[MOTOR] Saturated:%d Median:%d Weighted:%d Final:%d%%  Alert:%s\n",
            motorSaturated, motorMedian, weightedInt, motorSpeed,
            motorAlert ? "YES(limit hit)" : "NO");
        printf("=============================\n\n");
    }
}

#endif