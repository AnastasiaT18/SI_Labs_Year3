#ifdef RUN_LAB11

#include "app_lab_6_1.h"
#include "SharedData.h"
#include "lab3/ButtonSensor.h"          // replaces ButtonDriver
#include "lab1/LedControl.h"
#include "lab7/LCDDisplay.h"
#include "Task_FSM.h"
#include "Task_Report.h"
#include <stdio.h>

static ButtonSensor btn(2);            // button on pin D2
static LedControl   led(13);
static LCDDisplay   lcd(0x27, 16, 2);

static int serial_putchar(char c, FILE* f) {
    if (c == '\n') Serial.write('\r');
    return Serial.write(c);
}

static int serial_getchar(FILE* f) {
    while (!Serial.available())
        vTaskDelay(pdMS_TO_TICKS(50));
    return Serial.read();
}

static FILE serial_stdio;

void appLab61Setup() {
    Serial.begin(9600);

    fdev_setup_stream(&serial_stdio, serial_putchar, serial_getchar, _FDEV_SETUP_RW);
    stdout = &serial_stdio;
    stdin  = &serial_stdio;

    lcd.begin();
    lcd.printLine(0, "FSM Button-LED");
    lcd.printLine(1, "Starting...");

    xDataMutex = xSemaphoreCreateMutex();

    Task_FSM_init(&btn, &led);
    Task_Report_init(&lcd);

    xTaskCreate(Task_FSM,    "FSM",    256,  NULL, 2, NULL);
    xTaskCreate(Task_Report, "REPORT", 512,  NULL, 1, NULL);

    printf("=== Lab 6 Part 1: FSM Button-LED ===\n");
    printf("Press button on pin 2 to toggle LED on pin 13\n");
    printf("State transitions logged to serial\n");
    printf("=====================================\n");

    vTaskStartScheduler();
}

void appLab61Loop() {}

#endif