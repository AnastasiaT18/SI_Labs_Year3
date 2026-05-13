#ifndef TASK_BUTTON_H
#define TASK_BUTTON_H

#include "lab3/ButtonSensor.h"

// Initialise with a ButtonSensor instance.
// The task polls the button and sets g_nsRequest when a valid press occurs.
void Task_Button_init(ButtonSensor* btn);
void Task_Button(void* pvParameters);

#endif