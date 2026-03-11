#ifndef TASK_DS18B20_H
#define TASK_DS18B20_H

#include "DS18B20Sensor.h"

void Task_DS18B20_init(DS18B20Sensor* sensor);
void Task_DS18B20(void* pvParameters);

#endif