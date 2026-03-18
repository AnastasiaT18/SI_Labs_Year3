#include "SignalConditioner.h"
#include <string.h> // for memcpy

// Weights: most recent sample gets 40, then 30, 15, 10, 5
// Must sum to 100
const int SignalConditioner::WEIGHTS[MEDIAN_BUFFER_SIZE] = {40, 30, 15, 10, 5};

SignalConditioner::SignalConditioner(int satMin, int satMax)
    : _satMin(satMin), _satMax(satMax), _bufferIndex(0), _bufferFull(false) {
    memset(_buffer, 0, sizeof(_buffer));
}

int SignalConditioner::saturate(int raw) {
    if (raw < _satMin) return _satMin;
    if (raw > _satMax) return _satMax;
    return raw;
}

int SignalConditioner::medianFilter(int saturated) {
    // Insert into circular buffer
    _buffer[_bufferIndex] = saturated;
    _bufferIndex = (_bufferIndex + 1) % MEDIAN_BUFFER_SIZE;
    if (_bufferIndex == 0) _bufferFull = true;

    // Copy buffer for sorting (don't sort in place)
    int count = _bufferFull ? MEDIAN_BUFFER_SIZE : _bufferIndex;
    int temp[MEDIAN_BUFFER_SIZE];
    memcpy(temp, _buffer, count * sizeof(int));

    // Bubble sort (small buffer, fine for embedded)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                int swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

    return temp[count / 2]; // middle element
}

float SignalConditioner::weightedAverage() {
    int count = _bufferFull ? MEDIAN_BUFFER_SIZE : _bufferIndex;
    if (count == 0) return 0.0f;

    // Buffer is circular — reconstruct newest-first order
    float weightedSum = 0.0f;
    int totalWeight = 0;

    for (int i = 0; i < count; i++) {
        // Walk backwards from last written position
        int idx = (_bufferIndex - 1 - i + MEDIAN_BUFFER_SIZE) % MEDIAN_BUFFER_SIZE;
        weightedSum += _buffer[idx] * WEIGHTS[i];
        totalWeight += WEIGHTS[i];
    }

    return weightedSum / totalWeight;
}