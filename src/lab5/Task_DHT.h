#ifndef TASK_DHT_H
#define TASK_DHT_H

#include "DHTSensor.h"

void Task_DHT_init(DHTSensor* sensor);
void Task_DHT(void* pvParameters);

#endif