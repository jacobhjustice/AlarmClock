#include "Arduino.h"
#include "display.h"
#include "memory_access.h"
#include "clock.h"

//Mode _activeMode;
//View _activeView;

void setup() {  
  Serial.begin(9600);
  initializeDisplay();
}

void loop() {
  display();
}
