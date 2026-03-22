#ifdef RUN_LAB7

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
        bool relayState = g_relayState;
        bool relayAlert = g_relayAlert;
        int  servoAngle = g_servoAngle;
        xSemaphoreGive(xDataMutex);

        // update LCD
        String line0 = "Relay:" + String(relayState ? "ON " : "OFF");
        if (relayAlert) line0 += "!";
        String line1 = "Servo:" + String(servoAngle) + "d";

        _lcd->printLine(0, line0);
        _lcd->printLine(1, line1);

        // serial report
        printf("=============================\n");
        printf("[RELAY] State: %s  Alert: %s\n",
            relayState ? "ON" : "OFF",
            relayAlert ? "YES" : "NO");
        printf("[SERVO] Angle: %d deg\n", servoAngle);
        printf("=============================\n\n");
    }
}

#endif