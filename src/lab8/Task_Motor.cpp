#ifdef RUN_LAB8

#include "Task_Motor.h"
#include "SharedData.h"
#include "MotorConditioner.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>

// Conditioner: 0-100% range, ramp step 2% per 50ms tick
static MotorConditioner mc(0, 100, 2);
static MotorDriver* _motor;

void Task_Motor_init(MotorDriver* motor) {
    _motor = motor;
}

void Task_Motor(void* pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    int currentSpeed = 0;  // actual currently applied speed %
    int targetSpeed  = 0;  // conditioned target we are ramping toward

    while (true) {
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(50));

        // read raw command
        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        int rawCmd = g_motorCommand;
        xSemaphoreGive(xDataMutex);

        // if a new command arrived, run it through the conditioning pipeline
        if (rawCmd != -1) {
            // 1. Saturation
            int saturated = mc.saturate(rawCmd);
            bool alert = (rawCmd != saturated);

            // 2. Median filter
            int median = mc.medianFilter(saturated);

            // 3. Weighted average
            float weighted = mc.weightedAverage(median);
            targetSpeed = (int)(weighted + 0.5f);

            // write intermediate values and clear command
            xSemaphoreTake(xDataMutex, portMAX_DELAY);
            g_motorSaturated = saturated;
            g_motorMedian    = median;
            g_motorWeighted  = weighted;
            g_motorAlert     = alert;
            g_motorCommand   = -1;
            xSemaphoreGive(xDataMutex);
        }

        // 4. Ramp current speed toward target every tick
        int nextSpeed = mc.ramp(currentSpeed, targetSpeed);
        if (nextSpeed != currentSpeed) {
            currentSpeed = nextSpeed;
            _motor->setSpeed(currentSpeed);

            xSemaphoreTake(xDataMutex, portMAX_DELAY);
            g_motorSpeed = currentSpeed;
            xSemaphoreGive(xDataMutex);

            printf("MOTOR ramp: %d%%\n", currentSpeed);
        }
    }
}

#endif