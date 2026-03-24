#ifdef RUN_LAB7

#include "Task_Relay.h"
#include "SharedData.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

static RelayDriver* _relay;

void Task_Relay_init(RelayDriver* relay) {
    _relay = relay;
}
void Task_Relay(void* pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    int  pendingCmd     = -1;
    int  debounceCount  = 0;
    bool confirmedState = false;

    printf("Task_Relay started\n"); // debug


    while (true) {
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(50));

        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        int cmd = g_relayCommand;
        xSemaphoreGive(xDataMutex);

        if (cmd == -1) continue;
        // printf("RELAY got cmd: %d counter: %d\n", cmd, debounceCount); // debug


        if (cmd != pendingCmd) {
            // new command — start debounce
            pendingCmd    = cmd;
            debounceCount = 1;
        } else {
            // same command — increment counter
            debounceCount++;
        }

        if (debounceCount >= 5) {
            // confirmed after 5 × 50ms = 250ms
            bool newState = (pendingCmd == 1);

            if (newState != confirmedState) {
                confirmedState = newState;
                if (confirmedState) _relay->turnOn();
                else                _relay->turnOff();
                printf("RELAY confirmed: %s\n", confirmedState ? "ON" : "OFF");

                xSemaphoreTake(xDataMutex, portMAX_DELAY);
                g_relayState   = confirmedState;
                g_relayAlert   = true;
                g_relayCommand = -1;
                xSemaphoreGive(xDataMutex);
            }
            debounceCount = 0;
            pendingCmd    = -1;
        }
    }
}

#endif