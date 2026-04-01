#ifdef RUN_LAB7

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
        // reads from Serial via stdin/STDIO redirection
        // yields automatically inside serial_getchar while waiting
        printf("Enter command: ");
        
        scanf("%15s", cmd);   // reads first word e.g. "relay" or "servo"
        
        String c = String(cmd);
        c.toLowerCase();
































































































        
        if (c == "relay") {
            scanf("%15s", arg);  // reads second word "on" or "off"
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
            scanf("%15s", arg);  // reads angle e.g. "90"
            int angle = String(arg).toInt();

            if (angle >= 0 && angle <= 180) {
                xSemaphoreTake(xDataMutex, portMAX_DELAY);
                g_servoCommand = angle;
                xSemaphoreGive(xDataMutex);
                printf("CMD: servo -> %d deg\n", angle);
            } else {
                printf("CMD ERR: servo must be 0-180\n");
            }

        } else {
            printf("CMD ERR: unknown '%s'\n", cmd);
            printf("Use: 'relay on', 'relay off', 'servo 0-180'\n");
        }
    }
}

#endif
