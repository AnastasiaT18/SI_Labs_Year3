#ifndef TASK_TRAFFIC_FSM_H
#define TASK_TRAFFIC_FSM_H

#include "LedBank.h"

void Task_TrafficFSM_init(TrafficLedBank* leds);
void Task_TrafficFSM(void* pvParameters);

#endif