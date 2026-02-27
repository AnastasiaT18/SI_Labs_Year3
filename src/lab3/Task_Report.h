#ifndef TASK_REPORT_H
#define TASK_REPORT_H

// Called once in setup
void Task_Report_init(void);

// Called every 10000ms by scheduler
void Task_Report(void);

#endif