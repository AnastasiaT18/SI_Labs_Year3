#include "KeypadController.h"

KeypadController::KeypadController() {
    // Constructor can be used to initialize any variables if needed
}

void KeypadController::init() {
    // No specific initialization needed for the Keypad library
}

char KeypadController::getKeyPressed() {
    char key = keypad.getKey();
    if (key) {
        return key; // return the key that was pressed
    }
    return '\0'; // return null character if no key is pressed
}