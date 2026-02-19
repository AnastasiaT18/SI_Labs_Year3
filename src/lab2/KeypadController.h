#ifndef KEYPADCONTROL_H
#define KEYPADCONTROL_H

#include <Arduino.h>
#include <Keypad.h>

class KeypadController {
public:
    KeypadController();          // constructor
    void init();                 // initialize the keypad
    char getKeyPressed();        // returns the last key pressed, or '\0' if none

private:
    static const byte ROWS = 4;  
    static const byte COLS = 4;
    char keys[ROWS][COLS] = {
        {'1','2','3','A'},
        {'4','5','6','B'},
        {'7','8','9','C'},
        {'*','0','#','D'}
    };
    byte rowPins[ROWS] = {9, 8, 7, 6};  // connect keypad rows
    byte colPins[COLS] = {5, 4, 3, 2};  // connect keypad columns
    Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
};

#endif
