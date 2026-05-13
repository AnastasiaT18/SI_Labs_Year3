#ifdef RUN_LAB12

#include "Task_Button.h"
#include "SharedData.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>

static ButtonSensor* _btn;

void Task_Button_init(ButtonSensor* btn) {
    _btn = btn;
}

void Task_Button(void* pvParameters) {
    while (true) {
        // Poll every 20ms — fast enough to catch any press
        vTaskDelay(pdMS_TO_TICKS(20));

        unsigned long duration = _btn->update();

        if (duration > 0) {
            // Valid press detected — set the NS request flag
            xSemaphoreTake(xDataMutex, portMAX_DELAY);
            g_nsRequest = true;
            xSemaphoreGive(xDataMutex);

            printf("[BUTTON] NS request registered (dur=%lums)\n", duration);
        }
    }
}

#endif