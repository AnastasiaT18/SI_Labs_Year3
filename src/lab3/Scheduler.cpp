#include "Scheduler.h"

Task_t tasks[MAX_OF_TASKS] = {
    {NULL, 0, 0, 0},
    {NULL, 0, 0, 0},
    {NULL, 0, 0, 0},
};

void os_seq_scheduler_task_init(Task_t* task,
                                 void (*func)(void),
                                 int rec,
                                 int offset) {
    task->task_func = func;
    task->rec       = rec;
    task->offset    = offset;
    task->rec_cnt   = offset;  // first run delayed by offset
}

void os_seq_scheduler_setup(void) {
    extern void Task_Button(void);
    extern void Task_Stats(void);
    extern void Task_Report(void);

    os_seq_scheduler_task_init(&tasks[TASK_BUTTON_ID], Task_Button, 20,    0  );
    os_seq_scheduler_task_init(&tasks[TASK_STATS_ID],  Task_Stats,  20,    5  );
    os_seq_scheduler_task_init(&tasks[TASK_REPORT_ID], Task_Report, 10000, 100);
}

void os_seq_scheduler_loop(void) {
    for (int i = 0; i < MAX_OF_TASKS; i++) {
        if (--tasks[i].rec_cnt <= 0) {
            tasks[i].rec_cnt = tasks[i].rec;
            tasks[i].task_func();
        }
    }
}