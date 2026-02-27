#ifndef TASK_STATS_H
#define TASK_STATS_H

#include "lab1/LedControl.h"

void Task_Stats_init(LedControl* ledY);

// Called every 20ms by scheduler
void Task_Stats(void);

#endif