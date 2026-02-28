#include "app_lab_2_1.h"
#include "Scheduler.h"
#include "Timer.h"
#include "lab1/LedControl.h"
#include "ButtonSensor.h"
#include "SharedData.h"
#include "Task_Button.h"
#include "Task_Stats.h"
#include "Task_Report.h"
#include <stdio.h>  


// --- Hardware objects ---
static LedControl   ledGreen(4);
static LedControl   ledRed(5);
static LedControl   ledYellow(6);
static ButtonSensor button(7);

int serial_putchar(char c, FILE* f) {
    Serial.write(c);
    return c;
}

FILE serial_stdout;  


void appLab21Setup() {
    Serial.begin(9600);

    fdev_setup_stream(&serial_stdout, serial_putchar, NULL, 
        _FDEV_SETUP_WRITE); 
    stdout = &serial_stdout; 

    Task_Button_init(&button, &ledGreen, &ledRed);
    Task_Stats_init(&ledYellow);
    Task_Report_init();

    os_seq_scheduler_setup();
    timer1_init();

    printf("=== Lab 2.1 Ready ===");
    printf("Tasks:");
    for (int i = 0; i < MAX_OF_TASKS; i++) {
        printf("  [%d] rec=%dms offset=%dms\n", i, tasks[i].rec, tasks[i].offset);
    }
    printf("=====================\n");
}

void appLab21Loop() {
    // intentionally empty
    // everything runs via timer ISR → scheduler
}