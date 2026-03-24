#ifndef SIGNAL_CONDITIONER_H
#define SIGNAL_CONDITIONER_H

#include <Arduino.h>

#define SC_BUF_SIZE 5

class ServoConditioner {

private:
    int _satMin, _satMax, _rampStep;
    int _buf[SC_BUF_SIZE];
    int _bufIndex;
    int _bufCount;
;

public:
ServoConditioner(int satMin, int satMax, int rampStep);

    int  saturate(int value);
    int  medianFilter(int value);
    float weightedAverage(int value);
    int  ramp(int current, int target);

    // last intermediate values for reporting
    int   lastSaturated;
    int   lastMedian;
    float lastWeighted;
};

#endif