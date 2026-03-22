#ifndef TASK_REPORT_H
#define TASK_REPORT_H

#include "lab1/LedControl.h" 


void Task_Report_init(LedControl* ledNTC, LedControl* ledDHT);
void Task_Report(void* pvParameters);


#endif