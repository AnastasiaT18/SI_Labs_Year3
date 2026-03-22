#include "LCDDisplay.h"

LCDDisplay::LCDDisplay(uint8_t address, uint8_t cols, uint8_t rows)
    : _lcd(address, cols, rows) {}

void LCDDisplay::begin() {
    _lcd.init();
    _lcd.backlight();
    _lcd.clear();
}

void LCDDisplay::clear() {
    _lcd.clear();
}

void LCDDisplay::printLine(uint8_t row, const char* text) {
    _lcd.setCursor(0, row);
    // pad with spaces to clear previous content
    _lcd.print("                ");
    _lcd.setCursor(0, row);
    _lcd.print(text);
}

void LCDDisplay::printLine(uint8_t row, String text) {
    printLine(row, text.c_str());
}