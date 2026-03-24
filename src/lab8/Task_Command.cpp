#ifdef RUN_LAB8

#include "Task_Command.h"
#include "SharedData.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>

void Task_Command_init() {}

void Task_Command(void* pvParameters) {
    char cmd[16];
    char arg[16];

    while (true) {
        printf("Enter command: ");
        scanf("%15s", cmd);

        String c = String(cmd);
        c.toLowerCase();

        if (c == "relay") {
            scanf("%15s", arg);
            String a = String(arg);
            a.toLowerCase();

            xSemaphoreTake(xDataMutex, portMAX_DELAY);
            if (a == "on") {
                g_relayCommand = 1;
                printf("CMD: relay -> ON\n");
            } else if (a == "off") {
                g_relayCommand = 0;
                printf("CMD: relay -> OFF\n");
            } else {
                printf("CMD ERR: use 'relay on' or 'relay off'\n");
            }
            xSemaphoreGive(xDataMutex);

        } else if (c == "servo") {
            // accepts 0-100 percent, mapped to 0-180 degrees
            scanf("%15s", arg);
            int percent = String(arg).toInt();

            if (percent >= 0 && percent <= 100) {
                int angle = (int)((percent / 100.0f) * 180.0f + 0.5f);
                xSemaphoreTake(xDataMutex, portMAX_DELAY);
                g_servoCommand = angle;
                xSemaphoreGive(xDataMutex);
                printf("CMD: servo -> %d%% (%d deg)\n", percent, angle);
            } else {
                printf("CMD ERR: servo must be 0-100 (percent)\n");
            }

        } else {
            printf("CMD ERR: unknown '%s'\n", cmd);
            printf("Use: 'relay on', 'relay off', 'servo 0-100'\n");
        }
    }
}

#endif