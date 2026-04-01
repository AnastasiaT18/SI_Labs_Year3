#ifdef RUN_LAB8

#include "app_lab_4_2.h"
#include "SharedData.h"
#include "Task_Command.h"
#include "lab7/Task_Relay.h"
#include "Task_Motor.h"
#include "Task_Report.h"
#include "lab7/RelayDriver.h"
#include "MotorDriver.h"
#include "lab7/LCDDisplay.h"
#include <stdio.h>

// hardware objects
static RelayDriver relay(7);
static MotorDriver motor(6, 4, 5); // ENA=9, IN1=4, IN2=5
static LCDDisplay  lcd(0x27, 16, 2);

// STDIO redirect
int serial_putchar(char c, FILE* f) {
    if (c == '\n') Serial.write('\r');
    return Serial.write(c);
}

int serial_getchar(FILE* f) {
    while (!Serial.available()) {
        vTaskDelay(pdMS_TO_TICKS(50));
    }
    return Serial.read();
}

FILE serial_stdout;

void appLab42Setup() {
    Serial.begin(9600);
    fdev_setup_stream(&serial_stdout, serial_putchar, serial_getchar, _FDEV_SETUP_RW);
    stdout = &serial_stdout;
    stdin  = &serial_stdout;

    // init hardware
    relay.begin();
    motor.begin();
    lcd.begin();
    lcd.printLine(0, "System Ready");
    lcd.printLine(1, "Waiting cmd...");

    // create mutex
    xDataMutex = xSemaphoreCreateMutex();

    // inject dependencies
    Task_Command_init();
    Task_Relay_init(&relay);
    Task_Motor_init(&motor);
    Task_Report_init(&lcd);

    // create tasks
    xTaskCreate(Task_Command, "CMD",    256, NULL, 1, NULL);
    xTaskCreate(Task_Relay,   "RELAY",  256, NULL, 2, NULL);
    xTaskCreate(Task_Motor,   "MOTOR",  256, NULL, 2, NULL);
    xTaskCreate(Task_Report,  "REPORT", 512, NULL, 1, NULL);

    printf("=== Lab 4 Part 2 Ready ===\n");
    printf("Commands: relay on/off, motor 0-100\n");
    printf("==========================\n");

    vTaskStartScheduler();
}

void appLab42Loop() {
    // intentionally empty
}

#endif