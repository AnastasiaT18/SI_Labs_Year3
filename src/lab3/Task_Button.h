#ifndef TASK_BUTTON_H
#define TASK_BUTTON_H

#include "ButtonSensor.h"
#include "lab1/LedControl.h"

// Called once in setup to give Task1 its hardware objects
void Task_Button_init(ButtonSensor* btn,
                      LedControl* ledG,
                      LedControl* ledR);

// Called every 20ms by scheduler
void Task_Button(void);

#endif