#include "app_lab_2_1.h"
#include "Scheduler.h"
#include "Timer.h"
#include "lab1/LedControl.h"
#include "ButtonSensor.h"
#include "SharedData.h"
#include "Task_Button.h"
#include "Task_Stats.h"
#include "Task_Report.h"

// --- Hardware objects ---
static LedControl   ledGreen(4);
static LedControl   ledRed(5);
static LedControl   ledYellow(6);
static ButtonSensor button(7);

void appLab21Setup() {
    Serial.begin(9600);

    Task_Button_init(&button, &ledGreen, &ledRed);
    Task_Stats_init(&ledYellow);
    Task_Report_init();

    os_seq_scheduler_setup();
    timer1_init();

    Serial.println("=== Lab 2.1 Ready ===");
    Serial.println("Tasks:");
    for (int i = 0; i < MAX_OF_TASKS; i++) {
        Serial.print("  ["); Serial.print(i); Serial.print("] ");
        Serial.print("rec="); Serial.print(tasks[i].rec);
        Serial.print("ms offset="); Serial.print(tasks[i].offset);
        Serial.println("ms");
    }
    Serial.println("=====================");
}

void appLab21Loop() {
    // intentionally empty
    // everything runs via timer ISR → scheduler
}