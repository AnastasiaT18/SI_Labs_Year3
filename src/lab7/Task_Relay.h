#ifndef TASK_RELAY_H
#define TASK_RELAY_H

#include "RelayDriver.h"

void Task_Relay_init(RelayDriver* relay);
void Task_Relay(void* pvParameters);

#endif