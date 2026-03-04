#ifdef RUN_LAB4


#include "app_lab_2_2.h"
#include "lab1/LedControl.h"
#include "lab3/ButtonSensor.h"
#include "SharedData.h"
#include "Task_Button.h"
#include "Task_Stats.h"
#include "Task_Report.h"
#include <stdio.h>  


// --- Hardware objects ---
static LedControl   ledGreen(12);
static LedControl   ledRed(11);
static LedControl   ledYellow(10);
static ButtonSensor button(2);

int serial_putchar(char c, FILE* f) {
    Serial.write(c);
    return c;
}

FILE serial_stdout;  


void appLab22Setup() {
    Serial.begin(9600);

    fdev_setup_stream(&serial_stdout, serial_putchar, NULL, 
        _FDEV_SETUP_WRITE); 
    stdout = &serial_stdout; 

     // create synchronization primitives
     xPressEvent = xSemaphoreCreateBinary();
     xDataMutex  = xSemaphoreCreateMutex();

    Task_Button_init(&button, &ledGreen, &ledRed);
    Task_Stats_init(&ledYellow);
    Task_Report_init();

     // create FreeRTOS tasks
     xTaskCreate(Task_Button, "Button", 128, NULL, 2, NULL);
     xTaskCreate(Task_Stats,  "Stats",  128, NULL, 1, NULL);
     xTaskCreate(Task_Report, "Report", 128, NULL, 1, NULL);

     printf("=== Lab 2.2 FreeRTOS Ready ===\n");
     printf("Tasks created:\n");
     printf("  Button  — every 20ms,    priority 2\n");
     printf("  Stats   — event-driven,  priority 1\n");
     printf("  Report  — every 10000ms, priority 1\n");
     printf("===========================\n");
 
     // start FreeRTOS scheduler — never returns
     vTaskStartScheduler();
}

void appLab22Loop() {
    // intentionally empty
    // FreeRTOS scheduler takes over after vTaskStartScheduler()
    }

#endif