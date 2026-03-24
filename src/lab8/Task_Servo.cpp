#ifdef RUN_LAB8

#include "Task_Servo.h"
#include "SharedData.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>

// Signal conditioner: limits 0-180 degrees, ramp step 2 deg per 50ms tick
static ServoConditioner sc(0, 170, 2);
static ServoDriver* _servo;

void Task_Servo_init(ServoDriver* servo) {
    _servo = servo;
}

void Task_Servo(void* pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    int currentAngle = 0;   // actual currently applied angle
    int targetAngle  = 0;   // conditioned target we are ramping toward

    while (true) {
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(50));

        // read raw command
        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        int rawCmd = g_servoCommand;
        xSemaphoreGive(xDataMutex);

        // if a new command arrived, run it through the conditioning pipeline
        if (rawCmd != -1) {
            // 1. Saturation
            int saturated = sc.saturate(rawCmd);
            bool alert = (rawCmd != saturated); // alert if clamped

            // 2. Median filter
            int median = sc.medianFilter(saturated);

            // 3. Weighted average (returns float, round to int for target)
            float weighted = sc.weightedAverage(median);
            targetAngle = (int)(weighted + 0.5f);

            // write intermediate values and clear command
            xSemaphoreTake(xDataMutex, portMAX_DELAY);
            g_servoSaturated = saturated;
            g_servoMedian    = median;
            g_servoWeighted  = weighted;
            g_servoAlert     = alert;
            g_servoCommand   = -1;
            xSemaphoreGive(xDataMutex);
        }

        // 4. Ramp current angle toward target every tick (even when no new command)
        int nextAngle = sc.ramp(currentAngle, targetAngle);
        if (nextAngle != currentAngle) {
            currentAngle = nextAngle;
            _servo->setAngle(currentAngle);

            xSemaphoreTake(xDataMutex, portMAX_DELAY);
            g_servoAngle = currentAngle;
            xSemaphoreGive(xDataMutex);

            printf("SERVO ramp: %d deg\n", currentAngle);
        }
    }
}

#endif