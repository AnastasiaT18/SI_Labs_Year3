#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal.h>

class LCD {
public:
    // Constructor: initialize the LCD with the given pins
    // rs, en, d4, d5, d6, d7: digital pins connected to the LCD
    LCD(int rs, int en, int d4, int d5, int d6, int d7);

    // Print a single character at the current cursor position
    void printChar(char c);

    // Clear the entire LCD display and reset the cursor to (0,0)
    void clear();

    // Set the cursor to a specific column and row
    // col: column index (0-based)
    // row: row index (0-based)
    void setCursor(int col, int row);

private:
    // LiquidCrystal object that handles low-level communication with the LCD
    LiquidCrystal lcd;
};

#endif
