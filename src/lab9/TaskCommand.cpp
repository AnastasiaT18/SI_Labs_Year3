#ifdef RUN_LAB9

#include "TaskCommand.h"
#include "SharedData.h"
#include <Arduino_FreeRTOS.h>
#include <Arduino.h> // Include Arduino header for Serial
#include <semphr.h>
#include <stdio.h>
#include <string.h>   // strcmp
#include <stdlib.h>   // atof

void Task_Command_init() {}

static void printHelp() {
    printf("Commands:\n");
    printf("  SP <val>    Set setpoint in C  (e.g. 'SP 28.5')\n");
    printf("  HYS <val>   Set hysteresis band (e.g. 'HYS 1.5')\n");
    printf("  HELP        Show this list\n");
}

void Task_Command(void* pvParameters) {
    char cmd[16];
    char arg[16];

    printHelp();

    while (true) {
        // Yield until serial data is actually available
        // while (!Serial.available())
        //     vTaskDelay(pdMS_TO_TICKS(100));

        printf("> ");
        scanf("%15s", cmd);

        // uppercase in-place
        for (int i = 0; cmd[i]; i++)
            if (cmd[i] >= 'a' && cmd[i] <= 'z') cmd[i] -= 32;

        if (strcmp(cmd, "SP") == 0) {
            scanf("%15s", arg);
            float val = atof(arg);
            xSemaphoreTake(xDataMutex, portMAX_DELAY);
            g_setPoint = val;
            xSemaphoreGive(xDataMutex);
            printf("CMD: setpoint -> %.2f C\n", (double)val);

        } else if (strcmp(cmd, "HYS") == 0) {
            scanf("%15s", arg);
            float val = atof(arg);
            if (val < 0.0f) val = 0.0f;
            xSemaphoreTake(xDataMutex, portMAX_DELAY);
            g_hysteresis = val;
            xSemaphoreGive(xDataMutex);
            printf("CMD: hysteresis -> %.2f\n", (double)val);

        } else if (strcmp(cmd, "HELP") == 0) {
            printHelp();

        } else {
            printf("CMD ERR: unknown '%s'. Type HELP.\n", cmd);
        }
    }
}

#endif