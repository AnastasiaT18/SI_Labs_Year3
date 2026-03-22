#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class LCDDisplay {
private:
    LiquidCrystal_I2C _lcd;
public:
    LCDDisplay(uint8_t address, uint8_t cols, uint8_t rows);
    void begin();
    void clear();
    void printLine(uint8_t row, const char* text);
    void printLine(uint8_t row, String text);
};

#endif