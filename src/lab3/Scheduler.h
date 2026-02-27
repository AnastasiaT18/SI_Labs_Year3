#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <Arduino.h>

typedef struct {
    void (*task_func)(void);
    int rec;
    int offset;
    int rec_cnt;
} Task_t;

enum {
    TASK_BUTTON_ID = 0,
    TASK_STATS_ID,
    TASK_REPORT_ID,
    MAX_OF_TASKS
};

extern Task_t tasks[MAX_OF_TASKS];

void os_seq_scheduler_task_init(Task_t* task,
                                 void (*func)(void),
                                 int rec,
                                 int offset);
void os_seq_scheduler_setup(void);
void os_seq_scheduler_loop(void);

#endif