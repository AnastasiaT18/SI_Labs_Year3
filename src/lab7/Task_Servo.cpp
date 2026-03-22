#ifdef RUN_LAB7

#include "Task_Servo.h"
#include "SharedData.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

static ServoDriver* _servo;

void Task_Servo_init(ServoDriver* servo) {
    _servo = servo;
}

void Task_Servo(void* pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    int lastAngle = -1;

    while (true) {
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(50));

        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        int cmd = g_servoCommand;
        xSemaphoreGive(xDataMutex);

        if (cmd == -1) continue;
        if (cmd == lastAngle) {
            // same angle requested — clear and ignore
            xSemaphoreTake(xDataMutex, portMAX_DELAY);
            g_servoCommand = -1;
            xSemaphoreGive(xDataMutex);
            continue;
        }

        // new angle — apply it
        lastAngle = cmd;
        _servo->setAngle(cmd);
        printf("SERVO: %d deg\n", cmd);

        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        g_servoAngle   = cmd;
        g_servoCommand = -1;
        xSemaphoreGive(xDataMutex);
    }
}

#endif