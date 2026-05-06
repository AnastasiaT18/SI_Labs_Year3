#ifndef TASK_SENSOR_LAB10_H
#define TASK_SENSOR_LAB10_H

#include "lab5/DHTSensor.h"

void Task_Sensor_init(DHTSensor* dht);
void Task_Sensor(void* pvParameters);

#endif