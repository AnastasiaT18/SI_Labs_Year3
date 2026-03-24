#ifdef RUN_LAB8

#include "ServoConditioner.h"
#include <string.h>

static const float WEIGHTS[SC_BUF_SIZE] = {40, 30, 15, 10, 5};

ServoConditioner::ServoConditioner(int satMin, int satMax, int rampStep)
    : _satMin(satMin), _satMax(satMax), _rampStep(rampStep),
      _bufIndex(0), _bufCount(0),
      lastSaturated(0), lastMedian(0), lastWeighted(0.0f) {
    memset(_buf, 0, sizeof(_buf));
}

int ServoConditioner::saturate(int value) {
    if (value < _satMin) value = _satMin;
    if (value > _satMax) value = _satMax;
    lastSaturated = value;
    return value;
}

int ServoConditioner::medianFilter(int value) {
    _buf[_bufIndex] = value;
    _bufIndex = (_bufIndex + 1) % SC_BUF_SIZE;
    if (_bufCount < SC_BUF_SIZE) _bufCount++;

    int tmp[SC_BUF_SIZE];
    for (int i = 0; i < _bufCount; i++) tmp[i] = _buf[i];

    // bubble sort
    for (int i = 0; i < _bufCount - 1; i++)
        for (int j = 0; j < _bufCount - i - 1; j++)
            if (tmp[j] > tmp[j+1]) { int t = tmp[j]; tmp[j] = tmp[j+1]; tmp[j+1] = t; }

    lastMedian = tmp[_bufCount / 2];
    return lastMedian;
}

float ServoConditioner::weightedAverage(int value) {
    // value is already inserted by medianFilter, reuse buffer
    if (_bufCount == 0) { lastWeighted = 0.0f; return 0.0f; }

    float weightedSum = 0.0f;
    float totalWeight = 0.0f;
    int idx = (_bufIndex - 1 + SC_BUF_SIZE) % SC_BUF_SIZE;

    for (int i = 0; i < _bufCount; i++) {
        weightedSum += _buf[idx] * WEIGHTS[i];
        totalWeight += WEIGHTS[i];
        idx = (idx - 1 + SC_BUF_SIZE) % SC_BUF_SIZE;
    }

    lastWeighted = weightedSum / totalWeight;
    return lastWeighted;
}

int ServoConditioner::ramp(int current, int target) {
    if (current < target) {
        current += _rampStep;
        if (current > target) current = target;
    } else if (current > target) {
        current -= _rampStep;
        if (current < target) current = target;
    }
    return current;
}

#endif