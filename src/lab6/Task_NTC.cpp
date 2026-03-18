#ifdef RUN_LAB6

#include "Task_NTC.h"
#include "SharedData6.h"
#include "SignalConditioner.h"
#include "lab5/NTCSensor.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#define THRESHOLD_HIGH  26.0f
#define THRESHOLD_LOW   24.0f
#define DEBOUNCE_MAX    5

// Saturation limits for NTC ADC range (0-1023, we clamp to valid range)
#define SAT_MIN  100
#define SAT_MAX  900

static NTCSensor*        _sensor;
static SignalConditioner _conditioner(SAT_MIN, SAT_MAX);

static int  debounceCounter = 0;
static bool confirmedAlert  = false;

void Task_NTC_init(NTCSensor* sensor) {
    _sensor = sensor;
}

void Task_NTC(void* pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (true) {
        // --- STEP 1: RAW ACQUISITION ---
        int raw = _sensor->readRaw();


        // INJECT FAKE NOISE for demonstration (remove on real hardware)
        // every ~10th sample, add a big spike to simulate salt-and-pepper noise
        // static int noiseCounter = 0;
        // noiseCounter++;
        // if (noiseCounter % 10 == 0) {
        //     raw = raw + 400;  // big spike — median filter should kill this
        //     if (raw > 1023) raw = 1023;
        // }
        // // add small random-ish jitter every sample to simulate white noise
        // // (use noiseCounter as a simple pseudo-random source)
        // raw = raw + ((noiseCounter % 7) - 3);  // adds -3 to +3 jitter
      

        // --- STEP 2: SATURATION ---
        int saturated = _conditioner.saturate(raw);

        // --- STEP 3: MEDIAN FILTER (removes spike/salt-and-pepper noise) ---
        int median = _conditioner.medianFilter(saturated);

        // --- STEP 4: WEIGHTED AVERAGE (smooths uniform/white noise) ---
        float weighted = _conditioner.weightedAverage();

        // --- STEP 5: CONVERT WEIGHTED ADC VALUE TO TEMPERATURE ---
        // We convert the weighted average (still in ADC units) to °C
        float resistance = (10000.0f * weighted) / (1023.0f - weighted);
        float steinhart   = log(resistance / 10000.0f) / 3950.0f;
        steinhart        += 1.0f / 298.15f;
        float tempC       = (1.0f / steinhart) - 273.15f;

        // --- STEP 6: HYSTERESIS THRESHOLD ---
        bool rawAlert;
        if      (tempC > THRESHOLD_HIGH) rawAlert = true;
        else if (tempC < THRESHOLD_LOW)  rawAlert = false;
        else                             rawAlert = confirmedAlert;

        // --- STEP 7: DEBOUNCE COUNTER ---
        if (rawAlert) debounceCounter = min(debounceCounter + 1, DEBOUNCE_MAX);
        else          debounceCounter = max(debounceCounter - 1, 0);

        if      (debounceCounter >= DEBOUNCE_MAX) confirmedAlert = true;
        else if (debounceCounter == 0)            confirmedAlert = false;

        // --- STEP 8: WRITE ALL STAGES TO SHARED DATA ---
        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        g_ntcRaw          = raw;
        g_ntcSaturated    = saturated;
        g_ntcMedian       = median;
        g_ntcWeighted     = weighted;
        g_ntcTempC        = tempC;
        g_ntcAlertActive  = confirmedAlert;
        xSemaphoreGive(xDataMutex);

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(50));
    }
}



#endif