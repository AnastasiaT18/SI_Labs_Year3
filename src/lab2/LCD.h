#ifndef LCD_H
#define LCD_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class LCD {
public:
    // Constructor only needs I2C address now
    LCD(uint8_t address);

    void printChar(char c);
    void clear();
    void setCursor(int col, int row);

private:
    LiquidCrystal_I2C lcd;
};

#endif