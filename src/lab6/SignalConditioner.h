#ifndef SIGNAL_CONDITIONER_H
#define SIGNAL_CONDITIONER_H

#include <Arduino.h>

#define MEDIAN_BUFFER_SIZE 5

class SignalConditioner {
private:
    // Saturation limits
    int _satMin;
    int _satMax;

    // Median filter buffer
    int _buffer[MEDIAN_BUFFER_SIZE];
    int _bufferIndex;
    bool _bufferFull;

    // Weighted average weights (must sum to 100)
    // Index 0 = most recent, index N = oldest
    static const int WEIGHTS[MEDIAN_BUFFER_SIZE];

public:
    SignalConditioner(int satMin, int satMax);

    // Step 1: clamp raw value between satMin and satMax
    int saturate(int raw);

    // Step 2: push saturated value into circular buffer,
    //         return median of last N samples
    int medianFilter(int saturated);

    // Step 3: weighted average of buffer (newest = highest weight)
    //         returns a float so it can be used before or after °C conversion
    float weightedAverage();
};

#endif