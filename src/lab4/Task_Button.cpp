#ifdef RUN_LAB4

#include "Task_Button.h"
#include "SharedData.h"
#include <Arduino.h>

static ButtonSensor* _btn;
static LedControl*   _ledG;
static LedControl*   _ledR;

void Task_Button_init(ButtonSensor* btn,
                      LedControl* ledG,
                      LedControl* ledR) {
    _btn  = btn;
    _ledG = ledG;
    _ledR = ledR;
}

void Task_Button(void* pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (true) {
        unsigned long duration = _btn->update();

        if (duration > 0) {
            // lock mutex before writing shared data
            xSemaphoreTake(xDataMutex, portMAX_DELAY);
            g_lastPressDuration = duration;
            g_lastPressWasShort = (duration < 500);
            xSemaphoreGive(xDataMutex);

            // signal Task_Stats a press is ready
            xSemaphoreGive(xPressEvent);

            // LED feedback (no shared data, no mutex needed)
            if (duration < 500) {
                _ledG->turnOn();
                _ledR->turnOff();
            } else {
                _ledG->turnOff();
                _ledR->turnOn();
            }

            printf("[T1] %lums %s\n", duration,
                   duration < 500 ? "SHORT" : "LONG");
        }

        // sleep until next 20ms tick
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(20));
    }
}

#endif

