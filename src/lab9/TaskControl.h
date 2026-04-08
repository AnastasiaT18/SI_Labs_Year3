#ifndef TASK_CONTROL_LAB9_H
#define TASK_CONTROL_LAB9_H

#include "lab7/RelayDriver.h"

void Task_Control_init(RelayDriver* relay);
void Task_Control(void* pvParameters);

#endif