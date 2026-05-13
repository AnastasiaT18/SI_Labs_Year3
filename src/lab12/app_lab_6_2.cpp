#ifdef RUN_LAB12

#include "app_lab_6_2.h"
#include "SharedData.h"
#include "lab3/ButtonSensor.h"          // reused from Part 1 (lab3)
#include "lab7/LCDDisplay.h"            // reused from Part 1 (lab7)
#include "LedBank.h"
#include "Task_Button.h"
#include "Task_FSM.h"
#include "Task_Report.h"
#include <stdio.h>


// ── Pin assignments ────────────────────────────────────────────────────────
// EW LEDs: pins 3 (red), 4 (yellow), 5 (green)
// NS LEDs: pins 6 (red), 7 (yellow), 8 (green)
// Button:  pin 2 (NS crossing request, INPUT_PULLUP)
// LCD:     I2C 0x27, 16 columns, 2 rows
 
static ButtonSensor    btn(2);
static TrafficLedBank  leds(3, 4, 5,   // EW: red, yellow, green
                            6, 7, 8);  // NS: red, yellow, green
static LCDDisplay      lcd(0x27, 16, 2);
 
// ── STDIO redirect to Serial ───────────────────────────────────────────────
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
 
void appLab62Setup() {
    Serial.begin(9600);
    fdev_setup_stream(&serial_stdio, serial_putchar, serial_getchar, _FDEV_SETUP_RW);
    stdout = &serial_stdio;
    stdin  = &serial_stdio;
 
    // LCD startup message
    lcd.begin();
    lcd.printLine(0, "Smart Traffic");
    lcd.printLine(1, "Starting...");
 
    // Shared data mutex
    xDataMutex = xSemaphoreCreateMutex();
 
    // Wire up tasks
    Task_Button_init(&btn);
    Task_TrafficFSM_init(&leds);
    Task_TrafficReport_init(&lcd);
 
    // Create FreeRTOS tasks
    // Task_Button      — highest priority: must catch button presses fast
    // Task_TrafficFSM  — controls LEDs and runs FSM
    // Task_TrafficReport — lowest priority: display only
    xTaskCreate(Task_Button,        "BTN",    256,  NULL, 3, NULL);
    xTaskCreate(Task_TrafficFSM,    "FSM",    512,  NULL, 2, NULL);
    xTaskCreate(Task_TrafficReport, "REPORT", 512,  NULL, 1, NULL);
 
    printf("=== Lab 7 Part 2: Smart Traffic Light ===\n");
    printf("EW direction has priority by default.\n");
    printf("Press button on pin 2 to request NS crossing.\n");
    printf("==========================================\n");
 
    vTaskStartScheduler();
}
 
void appLab62Loop() {}
 
#endif