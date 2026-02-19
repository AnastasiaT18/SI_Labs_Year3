#include "LCD.h"

// Constructor: initialize the LCD using the pins we specify
// rs, en, d4, d5, d6, d7 are the digital pins connected to the LCD
LCD::LCD(int rs, int en, int d4, int d5, int d6, int d7) 
    : lcd(rs, en, d4, d5, d6, d7) 
{
    lcd.begin(16, 2); // Start the LCD with 16 columns and 2 rows
}

// Prints a single character at the current cursor position
void LCD::printChar(char c) {
    lcd.print(c);        
}   

// Clears the LCD screen and resets the cursor
void LCD::clear() {
    lcd.clear(); 
}

// Moves the cursor to a specific column and row
// col = column index (0-based), row = row index (0-based)
void LCD::setCursor(int col, int row) {
    lcd.setCursor(col, row); 
}
