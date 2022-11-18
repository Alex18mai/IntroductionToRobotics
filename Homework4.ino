// Introduction to Robotics - Homework 4 - Move through a 4 digit 7-segment display and increment/decrement the numbers using a joystick

// joystick movement
#define NONE -1
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// switch clicks
#define NO_BUTTON_CLICK 0
#define SHORT_BUTTON_CLICK 1
#define LONG_BUTTON_CLICK 2

// declare all the joystick pins
const int pinSW = 2, // digital pin connected to switch output
          pinX = A0, // A0 - analog pin connected to X output
          pinY = A1; // A1 - analog pin connected to Y output

// declare all the Shift Register pins
const int latchPin = 11, // STCP ([ST]orage [C]lock [P]in latch)
          clockPin = 10, // SHCP ([SH]ift register [C]lock [P]in clock)
          dataPin = 12; // DS ([D]ata [S]torage)

// declare all the display pins
const int segD1 = 7,
          segD2 = 6,
          segD3 = 5,
          segD4 = 4;

// constants for register size, number of display digits and number of encodings
const int regSize = 8,
          displayCount = 4,
          encodingsNumber = 16;

// the multiplexer delay in ms
const int muxDelay = 2;

// constants for initial display digit, initial number and bit order of the dp segment in encodings
const int startDisplayDigit = 0,
          startNumber = 0,
          dpBit = 0;

// constants for the minimum and maximum thresholds for the joystick + median value
const int minThreshold = 300,
          maxThreshold = 700,
          medianValue = 516;

// the data rate for the Serial port in bps
const int serialDataRate = 9600;

// delay for debounce and blink
const unsigned long debounceDelay = 25,
                    dpBlinkDelay = 300,
                    longButtonClickDelay = 3000;

const int displayDigits[displayCount] = {
  segD1, segD2, segD3, segD4
};

const byte byteEncodings[encodingsNumber] = {
//A B C D E F G DP 
  B11111100, // 0 
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};

// the hex display values (between 0 and 15)
int displayValues[displayCount];

int currDisplayDigit = startDisplayDigit;

bool displayLocked = false;

void setup() {
  // initialize the Shift Register pins
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  // initialize the display
  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], HIGH);
    displayValues[i] = startNumber;
  }

  // initialize the switch pin
  pinMode(pinSW, INPUT_PULLUP);

  Serial.begin(serialDataRate);
}

void loop() {
  determineResetAndDisplayLocked();
  if (displayLocked) {
    setDisplayValue();        
  }  
  else {
    moveDisplayDigit();
  }
  writeOnDisplay();
}

// function that checks the switch action and resets the display / locks in the display
void determineResetAndDisplayLocked() {
  int switchAction = checkSwitchAction();
  if (switchAction == SHORT_BUTTON_CLICK) { // lock display
    displayLocked = !displayLocked;
  }  
  else if (switchAction == LONG_BUTTON_CLICK) { // reset
    for (int i = 0; i < displayCount; i++) {
      displayValues[i] = startNumber;
    }
    currDisplayDigit = startDisplayDigit;
    displayLocked = false;
  }
}

// function that checks if the switch is pressed using debounce + checks if the switch is pressed for a long time
int checkSwitchAction() {
  static int lastSwitchValue = HIGH, switchState = HIGH;
  static unsigned long long lastSwitchDebounceTime = 0, lastSwitchChange = 0;
  static bool ignoreNextRelease = false;
  
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

  if (!displayLocked && millis() - lastSwitchChange > longButtonClickDelay) {
    if (switchState == LOW) {
      ignoreNextRelease = true;
      return LONG_BUTTON_CLICK;          
    }
  }

  return NO_BUTTON_CLICK;
}

// function that changes the locked in digit's value based on the joystick movement (X axis)
void setDisplayValue() {
  int joystickMovement = checkJoystickMovement();

  if (joystickMovement == UP) {
    displayValues[currDisplayDigit]++;
    if (displayValues[currDisplayDigit] > encodingsNumber - 1) {
      displayValues[currDisplayDigit] = 0;      
    }    
  } 
  else if (joystickMovement == DOWN) {
    displayValues[currDisplayDigit]--;
    if (displayValues[currDisplayDigit] < 0) {
      displayValues[currDisplayDigit] = encodingsNumber - 1;      
    }  
  }
}

// function that moves the display digit based on the joystick movement (Y axis)
void moveDisplayDigit() {
  int joystickMovement = checkJoystickMovement();
  
  if (joystickMovement == LEFT) {
    currDisplayDigit++;
    if (currDisplayDigit > displayCount - 1) {
      currDisplayDigit = 0;
    }
  } 
  else if (joystickMovement == RIGHT) {
    currDisplayDigit--;
    if (currDisplayDigit < 0) {
      currDisplayDigit = displayCount - 1;
    }
  }
}

// function that checks if the joystick was moved using debounce and returns the corresponding value (NONE, UP, DOWN, LEFT, RIGHT)
int checkJoystickMovement() {
  static int lastXValue = medianValue, lastYValue = medianValue;
  static int joystickDebounceState = NONE;
  static unsigned long long lastJoystickDebounceTime = 0;
  
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
      if (xValue < minThreshold) {
        joystickDebounceState = DOWN;
        return DOWN;
      }
      if (xValue > maxThreshold) {
        joystickDebounceState = UP;
        return UP;
      }
    }
    else { // the Y coordinate has a bigger change
      if (yValue < minThreshold) {
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

// function that writes the current configuration of the 4 digit 7-segment display using a Shift Register
void writeOnDisplay() {
  static int dpBlinkState = HIGH;
  static unsigned long long lastDpBlinkTime = 0;

  // blinking
  if (millis() - lastDpBlinkTime > dpBlinkDelay) {
    dpBlinkState = !dpBlinkState;
    lastDpBlinkTime = millis();
  }

  for (int i = 0; i < displayCount; i++) {
    byte encoding = byteEncodings[displayValues[i]];

    if (i == currDisplayDigit && (displayLocked || dpBlinkState)) {
      bitSet(encoding, dpBit);        
    }
    
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, encoding);
    digitalWrite(latchPin, HIGH);
    
    digitalWrite(displayDigits[i], LOW);
    delay(muxDelay);
    digitalWrite(displayDigits[i], HIGH);
  }
}
