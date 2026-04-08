#ifdef RUN_LAB9

#include "TaskSensor.h"
#include "SharedData.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <math.h>
#include <stdio.h>

static DHTSensor* _dht;

void Task_Sensor_init(DHTSensor* dht) {
    _dht = dht;
}

void Task_Sensor(void* pvParameters) {
    // DHT11 needs ~1 s after power-on before first valid read
    vTaskDelay(pdMS_TO_TICKS(1500));

    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (true) {
        // DHT11 minimum sample period is 2 s
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(2000));

        float temp = _dht->readTempC();
        float hum  = _dht->readHumidity();
        bool  err  = isnan(temp) || isnan(hum);

        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        if (!err) {
            g_temperature = temp;
            g_humidity    = hum;
        }
        g_sensorError = err;
        xSemaphoreGive(xDataMutex);

        if (err) {
            printf("SENSOR ERR: DHT read failed\n");
        }
    }
}

#endif