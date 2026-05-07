#ifdef RUN_LAB11

#include "Task_FSM.h"
#include "FSMController.h"
#include "SharedData.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>

static ButtonSensor*  _btn;
static LedControl*    _led;
static FSMController  fsm;

void Task_FSM_init(ButtonSensor* btn, LedControl* led) {
    _btn = btn;
    _led = led;
}

void Task_FSM(void* pvParameters) {
    fsm.reset();

    while (true) {
        // Step 1: Apply output based on current state (Moore)
        if (fsm.getOutput() == 1) _led->turnOn();
        else                      _led->turnOff();

        bool currentLedState = (fsm.getOutput() == 1);

        // Step 2: Poll every 20ms — fast enough to catch any press/release
        vTaskDelay(pdMS_TO_TICKS(20));

        // Step 3: Sample input via ButtonSensor edge detector
        unsigned long duration = _btn->update();
        uint8_t input = (duration > 0) ? 1 : 0;

        // Step 4: Transition only on valid press event
        uint8_t prevState = fsm.getState();
        fsm.transition(input);
        uint8_t newState = fsm.getState();

        // Update shared data for Task_Report
        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        g_fsmState      = newState;
        g_ledState      = currentLedState;
        g_buttonPressed = (input == 1);
        xSemaphoreGive(xDataMutex);

        // Log transition to serial
        if (newState != prevState) {
            printf("FSM transition: %s -> %s  (btn=%d, dur=%lums)\n",
                prevState == FSM_STATE_LED_OFF ? "LED_OFF" : "LED_ON",
                fsm.getStateName(),
                input,
                duration);
        }
    }
}

#endif