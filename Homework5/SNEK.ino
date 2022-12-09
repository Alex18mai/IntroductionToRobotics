// SNEK - Snake with a twist

#include "Constants.h"
#include "Menu.h"
#include "Joystick.h"
#include "Matrix.h"
#include "Lcd.h"
#include "Memory.h"
#include "Game.h"
#include "StateManager.h"
#include "Buzzer.h"


void setup() {
  memorySetup();

  menuSetup();
  joystickSetup();
  matrixSetup();
  lcdSetup();
  gameSetup();
  stateSetup();
  buzzerSetup();
  
  Serial.begin(9600);
}

void loop() {
  manageCurrentState();
  executeCurrentState();  
  playSong();
}
