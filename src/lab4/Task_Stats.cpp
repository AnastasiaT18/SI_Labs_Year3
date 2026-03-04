
#ifdef RUN_LAB4

#include "Task_Stats.h"
#include "SharedData.h"
#include <Arduino.h>

static LedControl* _ledY;

void Task_Stats_init(LedControl* ledY) {
    _ledY = ledY;
}

void Task_Stats(void* pvParameters) {

    while (true) {

        xSemaphoreTake(xPressEvent, portMAX_DELAY);

        // lock mutex before reading shared data
        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        unsigned long duration = g_lastPressDuration;
        bool isShort           = g_lastPressWasShort;
        xSemaphoreGive(xDataMutex);

        // update  statistics
        g_totalPresses++;
        if (isShort) {
            g_shortPresses++;
            g_sumShortDuration += duration;
        } else {
            g_longPresses++;
            g_sumLongDuration += duration;
        }

        printf("[T2] total=%lu short=%lu long=%lu\n",
            g_totalPresses, g_shortPresses, g_longPresses);

        int blinks = isShort ? 5 : 10;
        for (int i = 0; i < blinks; i++) {
                _ledY->turnOn();
                vTaskDelay(pdMS_TO_TICKS(100));
                _ledY->turnOff();
                vTaskDelay(pdMS_TO_TICKS(100));
            }

    }
}

#endif
