#ifndef TASK_CONTROL_LAB10_H
#define TASK_CONTROL_LAB10_H

#include "lab7/RelayDriver.h"

void Task_Control_init(RelayDriver* relay);
void Task_Control(void* pvParameters);

#endif