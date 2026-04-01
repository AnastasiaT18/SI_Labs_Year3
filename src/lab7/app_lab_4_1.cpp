#ifdef RUN_LAB7

#include "app_lab_4_1.h"
#include "SharedData.h"
#include "Task_Command.h"
#include "Task_Relay.h"
#include "Task_Servo.h"
#include "Task_Report.h"
#include "RelayDriver.h"
#include "ServoDriver.h"
#include "LCDDisplay.h"
#include <stdio.h>

// hardware objects
static RelayDriver relay(7);
static ServoDriver servo(6);
static LCDDisplay  lcd(0x27, 16, 2);

// STDIO redirect — both input and output through Serial
int serial_putchar(char c, FILE* f) {
    if (c == '\n') Serial.write('\r');
    return Serial.write(c);
}

int serial_getchar(FILE* f) {
    while (!Serial.available()) {
        vTaskDelay(pdMS_TO_TICKS(50)); // yield while waiting
    }
    return Serial.read();
}


FILE serial_stdout;

void appLab41Setup() {
    Serial.begin(9600);
    fdev_setup_stream(&serial_stdout, serial_putchar, serial_getchar, _FDEV_SETUP_RW);
    stdout = &serial_stdout;
    stdin  = &serial_stdout;  // same stream for both

    // init hardware
    relay.begin();
    servo.begin();
    lcd.begin();
    lcd.printLine(0, "System Ready");
    lcd.printLine(1, "Waiting cmd...");

    // create mutex
    xDataMutex = xSemaphoreCreateMutex();

    // inject dependencies
    Task_Command_init();
    Task_Relay_init(&relay);
    Task_Servo_init(&servo);
    Task_Report_init(&lcd);

    // create tasks
    xTaskCreate(Task_Command, "CMD",    256, NULL, 1, NULL);
    xTaskCreate(Task_Relay,   "RELAY",  256, NULL, 2, NULL);
    xTaskCreate(Task_Servo,   "SERVO",  256, NULL, 2, NULL);
    xTaskCreate(Task_Report,  "REPORT", 512, NULL, 1, NULL);

    printf("=== Lab 4 Part 1 Ready ===\n");
    printf("Commands: relay on/off, servo 0-1\n");
    printf("==========================\n");

    vTaskStartScheduler();
}

void appLab41Loop() {
    // intentionally empty
}

#endif
