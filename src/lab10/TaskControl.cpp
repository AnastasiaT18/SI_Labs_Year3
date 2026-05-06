#ifdef RUN_LAB10

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
    vTaskDelay(pdMS_TO_TICKS(2000));

    TickType_t xLastWakeTime = xTaskGetTickCount();

    // PID internal state — not shared, only used by this task
    float integral  = 0.0f;
    float e_prev    = 0.0f;
    const float dt  = 2.0f;   // seconds, matches task period

    while (true) {
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(2000));

        // Read shared snapshot
        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        float temp      = g_temperature;
        float sp        = g_setPoint;
        float kp        = g_Kp;
        float ki        = g_Ki;
        float kd        = g_Kd;
        bool  prevRelay = g_relayState;
        bool  sensorErr = g_sensorError;
        xSemaphoreGive(xDataMutex);

        if (sensorErr) continue;

        // PID calculation
        float e          = sp - temp;
        integral        += e * dt;
        float derivative = (e - e_prev) / dt;
        float output     = kp * e + ki * integral + kd * derivative;
        e_prev           = e;

        // Clamp integral to prevent windup
        if (integral >  100.0f) integral =  100.0f;
        if (integral < -100.0f) integral = -100.0f;

        // Convert PID output to relay state
        // output > 0 means temperature is below SP → need to heat
        bool nextRelay = (output > 0.0f);

        // Apply to hardware
        if (nextRelay) _relay->turnOn();
        else           _relay->turnOff();

        // Write back to shared state
        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        g_relayState = nextRelay;
        g_pidOutput  = output;
        xSemaphoreGive(xDataMutex);

        // Log transitions
        if (nextRelay != prevRelay) {
            printf("PID: relay -> %s  (T=%.1f SP=%.1f e=%.2f out=%.2f)\n",
                nextRelay ? "ON" : "OFF",
                (double)temp, (double)sp,
                (double)e, (double)output);
        }
    }
}

#endif