// #ifdef RUN_LAB5
// #include "Task_DS18B20.h"
// #include "SharedData5.h"
// #include <Arduino_FreeRTOS.h>
// #include <semphr.h>

// #define THRESHOLD_HIGH   26.0
// #define THRESHOLD_LOW    24.0
// #define DEBOUNCE_MAX     5

// // DS18B20 fix: requestTemperatures() blocks for ~750ms internally
// // This is too long for a FreeRTOS task with vTaskDelayUntil.
// // Solution: call requestTemperatures() then wait 1000ms, THEN read the value.
// // We use a simple state machine: 
// //   state 0 = send request, then wait
// //   state 1 = read result, process it, then wait again

// static DS18B20Sensor* _sensor;
// static int debounceCounter = 0;
// static bool confirmedAlert = false;

// void Task_DS18B20_init(DS18B20Sensor* sensor) {
//     _sensor = sensor;
// }

// void Task_DS18B20(void* pvParameters) {
//     TickType_t xLastWakeTime = xTaskGetTickCount();

//     while (true) {
//         // --- ACQUISITION ---
//         // readTempC() calls requestTemperatures() + getTempCByIndex()
//         // We give it a full 1000ms period so the blocking read doesn't cause issues
//         float tempC = _sensor->readTempC();

//         // Safety check: -127 means sensor failed to respond
//         if (tempC < -100.0) {
//             // skip this reading, don't update shared data
//             vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
//             continue;
//         }

//         // --- THRESHOLD WITH HYSTERESIS ---
//         bool rawAlert;
//         if      (tempC > THRESHOLD_HIGH) rawAlert = true;
//         else if (tempC < THRESHOLD_LOW)  rawAlert = false;
//         else                             rawAlert = confirmedAlert;

//         // --- DEBOUNCE COUNTER ---
//         if (rawAlert) debounceCounter = min(debounceCounter + 1, DEBOUNCE_MAX);
//         else          debounceCounter = max(debounceCounter - 1, 0);

//         if      (debounceCounter >= DEBOUNCE_MAX) confirmedAlert = true;
//         else if (debounceCounter == 0)             confirmedAlert = false;

//         // --- WRITE TO SHARED DATA ---
//         xSemaphoreTake(xDataMutex, portMAX_DELAY);
//         g_dsTempC       = tempC;
//         g_dsAlertActive = confirmedAlert;
//         xSemaphoreGive(xDataMutex);

//         vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
//     }
// }
// #endif