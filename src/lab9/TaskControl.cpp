#ifdef RUN_LAB9

#include "TaskControl.h"
#include "SharedData.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>

static RelayDriver* _relay;

void Task_Control_init(RelayDriver* relay) {
    _relay = relay;
}

void Task_Control(void* pvParameters) {
    // Wait for first valid sensor reading
    vTaskDelay(pdMS_TO_TICKS(2000));

    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (true) {
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(2000));

        // Read shared data snapshot
        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        float temp      = g_temperature;
        float sp        = g_setPoint;
        float hys       = g_hysteresis;
        bool  prevRelay = g_relayState;
        bool  sensorErr = g_sensorError;
        xSemaphoreGive(xDataMutex);

        // Skip control if sensor is broken
        if (sensorErr) continue;

        // ON/OFF with hysteresis:
        //   turn ON  when temp drops below (sp - hys)
        //   turn OFF when temp rises above (sp + hys)
        //   hold previous state inside the dead-band
        bool nextRelay = prevRelay;
        if (temp < (sp - hys)) {
            nextRelay = true;
        } else if (temp > (sp + hys)) {
            nextRelay = false;
        }
        // inside dead-band: nextRelay unchanged (hysteresis)

        // Apply to hardware
        if (nextRelay) _relay->turnOn();
        else           _relay->turnOff();

        // Write result back to shared state
        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        g_relayState = nextRelay;
        xSemaphoreGive(xDataMutex);

        // Log transitions
        if (nextRelay != prevRelay) {
            printf("CONTROL: relay -> %s  (T=%.1f SP=%.1f HYS=%.1f)\n",
                nextRelay ? "ON" : "OFF", (double)temp, (double)sp, (double)hys);
        }
    }
}

#endif