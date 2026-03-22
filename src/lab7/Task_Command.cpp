#ifdef RUN_LAB7

#include "Task_Command.h"
#include "SharedData.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>

void Task_Command_init() {}

// void Task_Command(void* pvParameters) {
//     char input[32];

//     while (true) {
//         // blocks here waiting for input — other tasks keep running
//         scanf("%31s", input);
        
//         String cmd = String(input);
//         cmd.toLowerCase();

//         // read second word if needed
//         char arg[16] = "";
//         if (cmd == "relay" || cmd == "servo") {
//             scanf("%15s", arg);
//         }

//         xSemaphoreTake(xDataMutex, portMAX_DELAY);

//         if (cmd == "relay") {
//             String a = String(arg);
//             a.toLowerCase();
//             if (a == "on") {
//                 g_relayCommand = 1;
//                 printf("CMD: relay -> ON\n");
//             } else if (a == "off") {
//                 g_relayCommand = 0;
//                 printf("CMD: relay -> OFF\n");
//             } else {
//                 printf("CMD ERR: use 'relay on' or 'relay off'\n");
//             }
//         } else if (cmd == "servo") {
//             int angle = String(arg).toInt();
//             if (angle >= 0 && angle <= 180) {
//                 g_servoCommand = angle;
//                 printf("CMD: servo -> %d deg\n", angle);
//             } else {
//                 printf("CMD ERR: servo must be 0-180\n");
//             }
//         } else {
//             printf("CMD ERR: unknown. Use: relay on/off, servo 0-180\n");
//         }

//         xSemaphoreGive(xDataMutex);
//     }
// }

void Task_Command(void* pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (true) {
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(50));

        if (Serial.available() > 0) {
            String input = Serial.readStringUntil('\n');
            input.trim();
            input.toLowerCase();

            if (input == "relay on") {
                xSemaphoreTake(xDataMutex, portMAX_DELAY);
                g_relayCommand = 1;
                xSemaphoreGive(xDataMutex);
                printf("CMD: relay -> ON\n");

            } else if (input == "relay off") {
                xSemaphoreTake(xDataMutex, portMAX_DELAY);
                g_relayCommand = 0;
                xSemaphoreGive(xDataMutex);
                printf("CMD: relay -> OFF\n");

            } else if (input.startsWith("servo ")) {
                int angle = input.substring(6).toInt();
                if (angle >= 0 && angle <= 180) {
                    xSemaphoreTake(xDataMutex, portMAX_DELAY);
                    g_servoCommand = angle;
                    xSemaphoreGive(xDataMutex);
                    printf("CMD: servo -> %d deg\n", angle);
                } else {
                    printf("CMD ERR: servo must be 0-180\n");
                }
            } else {
                printf("CMD ERR: unknown\n");
                printf("Use: 'relay on', 'relay off', 'servo 0-180'\n");
            }
        }
    }
}

#endif