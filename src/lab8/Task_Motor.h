#ifndef TASK_MOTOR_H
#define TASK_MOTOR_H

#include "MotorDriver.h"

void Task_Motor_init(MotorDriver* motor);
void Task_Motor(void* pvParameters);

#endif