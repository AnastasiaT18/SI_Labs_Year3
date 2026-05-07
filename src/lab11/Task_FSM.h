#ifndef TASK_FSM_H
#define TASK_FSM_H

#include "lab3/ButtonSensor.h"
#include "lab1/LedControl.h"   // reused from previous labs

void Task_FSM_init(ButtonSensor* btn, LedControl* led);
void Task_FSM(void* pvParameters);


#endif