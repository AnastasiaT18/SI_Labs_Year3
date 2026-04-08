#ifdef RUN_LAB9

#include "app_lab_5_1.h"
#include "SharedData.h"
#include "TaskCommand.h"
#include "TaskSensor.h"
#include "TaskControl.h"
#include "TaskReport.h"
#include "lab5/DHTSensor.h"
#include "lab7/RelayDriver.h"
#include "lab7/LCDDisplay.h"
#include <stdio.h>

// ── Hardware objects ──────────────────────────────────────────────
static DHTSensor   dht(18);              // DHT11 data pin D2
static RelayDriver relay(7);            // Relay IN pin D3
static LCDDisplay  lcd(0x27, 16, 2);   // I2C LCD 16x2

// ── STDIO → Serial ────────────────────────────────────────────────
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

void appLab51Setup() {
    Serial.begin(9600);
    fdev_setup_stream(&serial_stdio, serial_putchar, serial_getchar, _FDEV_SETUP_RW);
    stdout = &serial_stdio;
    stdin  = &serial_stdio;

    // Init hardware
    dht.begin();
    relay.begin();
    lcd.begin();
    lcd.printLine(0, "System Ready");
    lcd.printLine(1, "Waiting...");

    // Create mutex
    xDataMutex = xSemaphoreCreateMutex();

    // Inject dependencies
    Task_Command_init();
    Task_Sensor_init(&dht);
    Task_Control_init(&relay);
    Task_Report_init(&lcd);

    // Create tasks
    //                              name     stack  param  prio  handle
    xTaskCreate(Task_Command, "CMD",     512,  NULL,  1,    NULL);
    xTaskCreate(Task_Sensor,  "SENSOR",  512,  NULL,  1,    NULL);
    xTaskCreate(Task_Control, "CONTROL", 512,  NULL,  2,    NULL);
    xTaskCreate(Task_Report,  "REPORT",  768,  NULL,  1,    NULL);

    printf("=== Lab 9: ON-OFF Hysteresis Control ===\n");
    printf("Sensor: DHT11  Actuator: Relay\n");
    printf("Default SP=%.1f C  HYS=%.1f C\n", (double)g_setPoint, (double)g_hysteresis);
    printf("========================================\n");

    vTaskStartScheduler();
}

void appLab51Loop() {
    // intentionally empty — FreeRTOS scheduler takes over
}

#endif