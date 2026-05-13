#ifdef RUN_LAB12

#include "Task_Report.h"
#include "TrafficFSMController.h"
#include "SharedData.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>

static LCDDisplay* _lcd;

void Task_TrafficReport_init(LCDDisplay* lcd) {
    _lcd = lcd;
}


void Task_TrafficReport(void* pvParameters) {
    vTaskDelay(pdMS_TO_TICKS(500));  // let FSM run one cycle first
 
    TickType_t xLastWakeTime = xTaskGetTickCount();
 
    while (true) {
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(500));
 
        // Snapshot shared data under mutex
        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        uint8_t state   = g_fsmState;
        bool    ewGreen = g_ewGreen;
        bool    nsGreen = g_nsGreen;
        bool    req     = g_nsRequest;
        xSemaphoreGive(xDataMutex);
 
        const char* stateName;
        switch (state) {
            case TF_EW_GREEN:        stateName = "EW_GREEN";   break;
            case TF_EW_YELLOW:       stateName = "EW_YELLOW";  break;
            case TF_EW_RED_NS_GREEN: stateName = "NS_GREEN";   break;
            case TF_NS_YELLOW:       stateName = "NS_YELLOW";  break;
            case TF_NS_RED_EW_GREEN: stateName = "EW_RESTORE"; break;
            default:                 stateName = "UNKNOWN";    break;
        }
 
        // ── LCD output ────────────────────────────────────────────────────
        // Line 0: "EW:GRN  NS:RED  "
        // Line 1: "St:EW_GREEN     "
        char line0[17], line1[17];
        snprintf(line0, sizeof(line0), "EW:%-3s  NS:%-3s",
                 ewGreen ? "GRN" : "---",
                 nsGreen ? "GRN" : "---");
        snprintf(line1, sizeof(line1), "%-16s", stateName);
        _lcd->printLine(0, line0);
        _lcd->printLine(1, line1);
 
        // ── Serial output ─────────────────────────────────────────────────
        printf("[REPORT] %-10s  EW:%s  NS:%s  REQ:%d\n",
               stateName,
               ewGreen ? "GRN" : "---",
               nsGreen ? "GRN" : "---",
               req ? 1 : 0);
    }
}
 
#endif