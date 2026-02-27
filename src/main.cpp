
//lab1
// #include <stdio.h> 
// #include <Arduino.h> 
// #include "LedControl.h" 
// #include "SerialHandler.h" 
// int serial_putchar(char c, FILE *f) { 
// Serial.write(c); 
// return c; 
// } 
// FILE serial_stdout; 
// LedControl led(13); 
// SerialHandler serialHandler(&led); 
// void setup() { 
// Serial.begin(9600); 
// fdev_setup_stream(&serial_stdout, serial_putchar, NULL, 
// _FDEV_SETUP_WRITE); 
// stdout = &serial_stdout; 
// printf("System ready, with STDIO.\n"); 
// } 
// void loop() { 
// serialHandler.checkCommands(); 
// } 


#include <stdio.h>
#include <Arduino.h>

// #include "lab1/LedControl.h"
// #include "lab2/KeypadController.h"
// #include "lab2/LCD.h"

// // Create instances of peripherals
// KeypadController keypad;                // Keypad input
// LCD lcd(A0, A1, A2, A3, A4, A5);       // LCD output (pins A0–A5)
// LedControl redLed(12);                  // Red LED for wrong code
// LedControl greenLed(11);                // Green LED for correct code

// // Function to send characters to the LCD, used by STDIO
// int LcdPutChar(char c, FILE *f) {
//     static int col = 0;
//     static int row = 0;

//     // Handle newline: move to next row
//     if (c == '\n') {
//         row = (row + 1) % 2;
//         col = 0;
//         return 0;
//     }

//     lcd.setCursor(col, row);
//     lcd.printChar(c);   
//     col++;

//     // Move to next row if end of line reached
//     if (col >= 16) {
//         col = 0;
//         row = (row + 1) % 2;
//     }

//     return c;
// }

// // Function to read a character from the keypad, used by STDIO
// int KeypadGetChar(FILE *f) {
//     char key;
//     do {
//         key = keypad.getKeyPressed();  // Wait until a key is pressed
//     } while (!key);

//     if (key == '#') {
//         key = '\n'; // Treat '#' as the Enter key
//     }

//     LcdPutChar(key, f); // Show the pressed key on the LCD

//     return key;
// }

// void setup() {
//     keypad.init(); // Initialize keypad hardware

//     // Connect STDIO streams to LCD and Keypad
//     FILE *my_stream = fdevopen(LcdPutChar, KeypadGetChar);
//     stdin = stdout = my_stream;

//     lcd.clear();
//     printf("System ready.\n");  // Initial message on LCD
//     delay(1000);
//     lcd.clear();
// }

// void loop() {
//     char input[5];  // Buffer to store 4-digit code

//     lcd.clear();
//     printf("Enter Code:\n");    // Prompt user

//     scanf("%4s", input);        // Read up to 4 characters from keypad
//     delay(1000);
//     lcd.clear();

//     printf("Received input: %s\n", input);  // Echo entered code

//     // Verify the code
//     if (strcmp(input, "1234") == 0) {
//         printf("Access Granted\n");
//         greenLed.turnOn();
//         redLed.turnOff();
//     } else {
//         printf("Access Denied\n");
//         greenLed.turnOff();
//         redLed.turnOn();
//     }

//     delay(2000);        // Keep LED on for a short period
//     greenLed.turnOff(); // Turn off LEDs before next input
//     redLed.turnOff();
// }


//lab2.1
#include "lab3/app_lab_2_1.h"

void setup() {
    // appLab1Setup();
    // appLab21Setup();
    appLab21Setup();
}

void loop() {
    // appLab1Loop();
    // appLab21Loop();
    appLab21Loop();
}


