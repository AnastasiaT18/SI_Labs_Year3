
#include "Task_DHT.h"
#include "SharedData5.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <math.h>   // for isnan()

#define THRESHOLD_HIGH   26.0
#define THRESHOLD_LOW    24.0
#define DEBOUNCE_MAX     3    // lower than NTC since reads are slower

static DHTSensor* _sensor;
static int debounceCounter = 0;
static bool confirmedAlert = false;

void Task_DHT_init(DHTSensor* sensor) {
    _sensor = sensor;
}

void Task_DHT(void* pvParameters) {

    vTaskDelay(pdMS_TO_TICKS(1500));


    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (true) {
        // DHT22 minimum sampling period is 2 seconds
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(2000));
        taskYIELD(); // give scheduler a breath before blocking read



        float tempC    = _sensor->readTempC();
        float humidity = _sensor->readHumidity();

        // isnan() check — DHT22 returns NaN on read failure
        if (isnan(tempC) || isnan(humidity)) {
            printf("DHT22: read fail\n");
            continue;  // skip bad reading
        }

        // --- THRESHOLD WITH HYSTERESIS ---
        bool rawAlert;
        if      (tempC > THRESHOLD_HIGH) rawAlert = true;
        else if (tempC < THRESHOLD_LOW)  rawAlert = false;
        else                             rawAlert = confirmedAlert;

        // --- DEBOUNCE ---
        if (rawAlert) debounceCounter = min(debounceCounter + 1, DEBOUNCE_MAX);
        else          debounceCounter = max(debounceCounter - 1, 0);

        if      (debounceCounter >= DEBOUNCE_MAX) confirmedAlert = true;
        else if (debounceCounter == 0)             confirmedAlert = false;

        // --- WRITE SHARED DATA ---
        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        g_dhtTempC       = tempC;
        g_dhtHumidity    = humidity;
        g_dhtAlertActive = confirmedAlert;
        xSemaphoreGive(xDataMutex);
    }
}

