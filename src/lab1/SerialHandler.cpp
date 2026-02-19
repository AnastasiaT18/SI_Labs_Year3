#include "SerialHandler.h"

SerialHandler::SerialHandler(LedControl* ledModule) {
    led = ledModule;
}

void SerialHandler::checkCommands(){
    if (Serial.available() > 0) {

        String command = Serial.readStringUntil('\n'); 
        command.trim();
    
        if (command == "led on"){
          led->turnOn();
          printf("LED turned ON\n");
        } 
        else if(command == "led off"){
          led->turnOff();
          printf("LED turned OFF\n");
      }
      else{
        printf("Unknown command.\n");
      }
    }
}