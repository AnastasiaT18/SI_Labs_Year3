#ifndef TASK_NTC_H
#define TASK_NTC_H

#include "lab5/NTCSensor.h"

void Task_NTC_init(NTCSensor* sensor);
void Task_NTC(void* pvParameters);  // FreeRTOS task function

#endif