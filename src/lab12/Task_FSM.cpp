#ifdef RUN_LAB12

#include "Task_FSM.h"
#include "TrafficFSMController.h"
#include "SharedData.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>

static TrafficLedBank*     _leds;
static TrafficFSMController fsm;

void Task_TrafficFSM_init(TrafficLedBank* leds) {
    _leds = leds;
}
 
void Task_TrafficFSM(void* pvParameters) {
    fsm.reset();
 
    while (true) {
        // Step 1: Apply outputs for current state (Moore)
        _leds->apply(fsm.getOutput());
 
        // Step 2: Update shared data so Task_Report sees current state
        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        g_fsmState = fsm.getState();
        g_ewGreen  = (fsm.getOutput().ew_green == 1);
        g_nsGreen  = (fsm.getOutput().ns_green == 1);
        xSemaphoreGive(xDataMutex);
 
        // Step 3: Wait state-specific dwell time
        vTaskDelay(pdMS_TO_TICKS(fsm.getDelay()));
 
        // Step 4: Only check the request flag in state 0 (EW_GREEN).
        // In all other states the sequence is committed — any button press
        // during states 1-4 is intentionally ignored AND the flag is cleared
        // so it cannot carry over into the next EW_GREEN hold.
        uint8_t request = 0;
        if (fsm.getState() == TF_EW_GREEN) {
            xSemaphoreTake(xDataMutex, portMAX_DELAY);
            request     = g_nsRequest ? 1 : 0;
            g_nsRequest = false;   // always clear — fresh decision each poll
            xSemaphoreGive(xDataMutex);
        } else {
            // Committed state — discard any accumulated press
            xSemaphoreTake(xDataMutex, portMAX_DELAY);
            g_nsRequest = false;
            xSemaphoreGive(xDataMutex);
        }
 
        // Step 5: Transition
        fsm.transition(request);
    }
}

#endif