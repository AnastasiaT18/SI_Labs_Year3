#ifndef TASK_TRAFFIC_REPORT_H
#define TASK_TRAFFIC_REPORT_H

#include "lab7/LCDDisplay.h"

void Task_TrafficReport_init(LCDDisplay* lcd);
void Task_TrafficReport(void* pvParameters);

#endif