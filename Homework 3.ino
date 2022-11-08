
// Introduction to Robotics - Homework 3 - Draw on the display of a 7-segment display using a joystick

#define NONE -1
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define NO_BUTTON_CLICK 0
#define SHORT_BUTTON_CLICK 1
#define LONG_BUTTON_CLICK 2

// declare all the joystick pins
const int pinSW = 2, // digital pin connected to switch output
          pinX = A0, // A0 - analog pin connected to X output
          pinY = A1; // A1 - analog pin connected to Y output

// declare all the segments pins
const int pinA = 9,
          pinB = 8,
          pinC = 5,
          pinD = 6,
          pinE = 7,
          pinF = 10,
          pinG = 11,
          pinDP = 4;

// constant for the number of segments
const int segSize = 8;

// the pins for each segment
const int segments[segSize] = { 
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

// the move matrix based on the joystick actions
const int moveMatrix[segSize][4] = {
// UP DOWN LEFT RIGHT  
  {0,   6,   5,   1}, //a
  {0,   6,   5,   1}, //b
  {6,   3,   4,   7}, //c
  {6,   3,   4,   2}, //d
  {6,   3,   4,   2}, //e
  {0,   6,   5,   1}, //f
  {0,   3,   6,   6}, //g
  {7,   7,   2,   7}, //dp
};

// constants for the minimum and maximum thresholds for the joystick + median value
const int minThreshold = 300,
          maxThreshold = 700,
          medianValue = 516;

// the data rate for the Serial port in bps
const int serialDataRate = 9600;

// semicolon string used for printing to the Serial Monitor
const String semicolon = "; ";

// delay for debounce and blink
const unsigned long debounceDelay = 25,
                    blinkDelay = 300,
                    longButtonClickDelay = 3000;

// modify if you have common anode
const bool commonAnode = false; 

// array where the value for each segment is kept
int segValues[segSize];

int currSegment = 7, // the current segment - initialized with dp

    blinkState = HIGH,

    lastXValue = medianValue,
    lastYValue = medianValue,
    joystickDebounceState = NONE,
    
    lastSwitchValue = HIGH,
    switchState = HIGH;

unsigned long long lastBlinkTime = 0,
                   lastJoystickDebounceTime = 0,
                   lastSwitchDebounceTime = 0,
                   lastSwitchChange = 0;

bool segmentLocked = false,
     ignoreNextRelease = false;

void setup() {
  // initialize all the segment pins
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
    segValues[i] = LOW; // initialize the segment values with LOW
  }

  // initialize the switch pin
  pinMode(pinSW, INPUT_PULLUP);

  Serial.begin(serialDataRate);
}

void loop() {
  determineResetAndSegmentLocked();
  if (segmentLocked) {
    setSegmentValue();        
  }  
  else {
    moveSegment();
  }
  displaySegments();
}

// function that checks the switch action and resets the display / locks in the segment
void determineResetAndSegmentLocked(){
  int switchAction = checkSwitchAction();
  if (switchAction == SHORT_BUTTON_CLICK) {
    segmentLocked = !segmentLocked;
  }  
  else if (switchAction == LONG_BUTTON_CLICK) {
    for (int i = 0; i < segSize; i++) {
      segValues[i] = LOW;
    }    
    currSegment = 7;
    segmentLocked = false;
  }
}

// function that checks if the switch is pressed using debounce + checks if the switch is pressed for a long time
int checkSwitchAction(){
  int switchValue = digitalRead(pinSW);

  if (switchValue != lastSwitchValue) {
    lastSwitchDebounceTime = millis();
  }
  lastSwitchValue = switchValue;

  if (millis() - lastSwitchDebounceTime > debounceDelay) {
    if (switchValue != switchState) {
      switchState = switchValue;

      if (switchState == HIGH) {
        if (ignoreNextRelease) {
          ignoreNextRelease = false;
        }
        else {
          return SHORT_BUTTON_CLICK;
        }
      }

      lastSwitchChange = millis();
    }
  }

  if (millis() - lastSwitchChange > longButtonClickDelay) {
    if (switchState == LOW) {
      ignoreNextRelease = true;
      return LONG_BUTTON_CLICK;          
    }
  }

  return NO_BUTTON_CLICK;
}

// function that changes the locked in segment's value based on the joystick movement (X axis)
void setSegmentValue(){
  int joystickMovement = checkJoystickMovement();
  if (joystickMovement == UP || joystickMovement == DOWN) {
    segValues[currSegment] = !segValues[currSegment];
  } 
}

// function that moves the segment based on the joystick movement
void moveSegment(){
  int joystickMovement = checkJoystickMovement();
  if (joystickMovement != NONE) {
    currSegment = moveMatrix[currSegment][joystickMovement];
  } 
}

// function that checks if the joystick was moved using debounce and returns the corresponding value (NONE, UP, DOWN, LEFT, RIGHT)
int checkJoystickMovement(){
  int xValue = analogRead(pinX);
  int yValue = analogRead(pinY);
  // Serial.println(xValue + semicolon + yValue);

  if ((xValue < minThreshold || xValue > maxThreshold) || (yValue < minThreshold || yValue > maxThreshold)) {
    if ((lastXValue >= minThreshold && lastXValue <= maxThreshold) && (lastYValue >= minThreshold && lastYValue <= maxThreshold)) {
      lastJoystickDebounceTime = millis();
      joystickDebounceState = NONE;
    }
  }
  lastXValue = xValue;
  lastYValue = yValue;

  if (millis() - lastJoystickDebounceTime > debounceDelay && joystickDebounceState == NONE) {
    if (abs(xValue - medianValue) > abs(yValue - medianValue)) { // the X coordinate has a bigger change
      if (xValue < minThreshold){
        joystickDebounceState = DOWN;
        return DOWN;
      }
      if (xValue > maxThreshold) {
        joystickDebounceState = UP;
        return UP;
      }
    }
    else { // the Y coordinate has a bigger change
      if (yValue < minThreshold){
        joystickDebounceState = LEFT;
        return LEFT;
      }
      if (yValue > maxThreshold) {
        joystickDebounceState = RIGHT;
        return RIGHT;
      }
    }
  }

  return NONE;  
}

// function that displays the segments
void displaySegments() {
  for (int i = 0; i < segSize; i++) {
    if (!segmentLocked && i == currSegment) {
      if (millis() - lastBlinkTime > blinkDelay) {
        blinkState = !blinkState;
        lastBlinkTime = millis();
      }
      digitalWrite(segments[i], blinkState);    
      continue;
    }
    digitalWrite(segments[i], segValues[i]);    
  }
}
