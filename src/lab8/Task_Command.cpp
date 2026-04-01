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

        } else if (c == "motor") {
            scanf("%15s", arg);
            int speed = String(arg).toInt();

            if (speed >= 0 && speed <= 100) {
                xSemaphoreTake(xDataMutex, portMAX_DELAY);
                g_motorCommand = speed;
                xSemaphoreGive(xDataMutex);
                printf("CMD: motor -> %d%%\n", speed);
            } else {
                printf("CMD ERR: motor must be 0-100 (percent)\n");
            }

        } else {
            printf("CMD ERR: unknown '%s'\n", cmd);
            printf("Use: 'relay on', 'relay off', 'motor 0-100'\n");
        }
    }
}

#endif