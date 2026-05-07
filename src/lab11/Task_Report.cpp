#ifdef RUN_LAB11

#include "Task_Report.h"
#include "FSMController.h"
#include "SharedData.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>

static LCDDisplay* _lcd;

void Task_Report_init(LCDDisplay* lcd) {
    _lcd = lcd;
}

void Task_Report(void* pvParameters) {
    // Short startup delay — let FSM run at least one full cycle first
    vTaskDelay(pdMS_TO_TICKS(500));

    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (true) {
        // Report every 500ms — fast enough to reflect button presses visibly
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(500));

        // Snapshot shared data under mutex
        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        uint8_t state = g_fsmState;
        bool    led   = g_ledState;
        bool    btn   = g_buttonPressed;
        xSemaphoreGive(xDataMutex);

        const char* stateName = (state == FSM_STATE_LED_ON) ? "LED_ON" : "LED_OFF";

        // ── LCD output ────────────────────────────────────────────────────
        // Line 0: "State: LED_OFF "
        // Line 1: "LED:OFF  BTN:0  "
        char line0[17], line1[17];
        snprintf(line0, sizeof(line0), "State:%-9s", stateName);
        snprintf(line1, sizeof(line1), "LED:%-3s  BTN:%d",
                 led ? "ON " : "OFF", btn ? 1 : 0);
        _lcd->printLine(0, line0);
        _lcd->printLine(1, line1);

        // ── STDIO serial output ───────────────────────────────────────────
        // Periodic structured report (also drives Serial Plotter)
        printf("[REPORT] State:%-7s  LED:%s  BTN:%d\n",
               stateName,
               led ? "ON " : "OFF",
               btn ? 1 : 0);

        // Serial Plotter compatible line (separate labeled values)
        // Uncomment to use with Arduino Serial Plotter instead of terminal:
        // printf("State:%d LED:%d Button:%d\n", state, led?1:0, btn?1:0);
    }
}

#endif