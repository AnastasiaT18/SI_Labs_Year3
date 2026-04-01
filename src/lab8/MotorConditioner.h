#ifndef MOTOR_CONDITIONER_H
#define MOTOR_CONDITIONER_H

#include <Arduino.h>

#define MC_BUF_SIZE 5

class MotorConditioner {
private:
    int _satMin, _satMax, _rampStep;
    int _buf[MC_BUF_SIZE];
    int _bufIndex;
    int _bufCount;

public:
    MotorConditioner(int satMin, int satMax, int rampStep);

    int   saturate(int value);
    int   medianFilter(int value);
    float weightedAverage(int value);
    int   ramp(int current, int target);

    // last intermediate values for reporting
    int   lastSaturated;
    int   lastMedian;
    float lastWeighted;
};

#endif