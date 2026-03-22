#ifdef RUN_LAB6
#include "app_lab_3_2.h"
#include "SharedData6.h"
#include "Task_NTC.h"
#include "lab5/Task_DHT.h"
#include "Task_Report.h"
#include "lab5/NTCSensor.h"
#include "lab5/DHTSensor.h"
#include <stdio.h>

// Hardware objects
static NTCSensor     ntcSensor(A0);   // NTC on analog pin A0
static DHTSensor dhtSensor(18); 

static LedControl ledNTC(7);
static LedControl ledDHT(8);


// STDIO redirect to Serial
int serial_putchar(char c, FILE* f) {
    Serial.write(c);
    return c;
}
FILE serial_stdout;

void appLab32Setup() {
    Serial.begin(9600);
    fdev_setup_stream(&serial_stdout, serial_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &serial_stdout;

    // initialize sensors
    ntcSensor.begin();
    // dsSensor.begin();
    dhtSensor.begin();


    // create synchronization primitive
    xDataMutex = xSemaphoreCreateMutex();

    // inject hardware into tasks
    Task_NTC_init(&ntcSensor);
    // Task_DS18B20_init(&dsSensor);
    Task_DHT_init(&dhtSensor);

    Task_Report_init(&ledNTC, &ledDHT);

    // create FreeRTOS tasks
    xTaskCreate(Task_NTC,      "NTC",      256, NULL, 2, NULL);
    xTaskCreate(Task_DHT,    "DHT11",   1024, NULL, 2, NULL);

    xTaskCreate(Task_Report,   "Report",   256, NULL, 1, NULL);

    printf("=== Lab 5 Part 2 Ready ===\n");
    printf("Sensors: NTC (A0) + DHT11 (pin 18)\n");
    printf("Threshold: LOW=24.0C  HIGH=26.0C\n");
    printf("Report every: 500ms\n");
    printf("==========================\n");

    vTaskStartScheduler();
}

void appLab32Loop() {
    // intentionally empty — FreeRTOS takes over
}
#endif