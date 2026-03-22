#ifndef TASK_SERVO_H
#define TASK_SERVO_H

#include "ServoDriver.h"

void Task_Servo_init(ServoDriver* servo);
void Task_Servo(void* pvParameters);

#endif