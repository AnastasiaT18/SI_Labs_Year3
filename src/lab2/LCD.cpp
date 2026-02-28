#include "LCD.h"

// Constructor for I2C LCD
LCD::LCD(uint8_t address)
    : lcd(address, 16, 2)   // address, columns, rows
{
    lcd.init();        // Initialize LCD
    lcd.backlight();   
}

void LCD::printChar(char c) {
    lcd.print(c);
}

void LCD::clear() {
    lcd.clear();
}

void LCD::setCursor(int col, int row) {
    lcd.setCursor(col, row);
}