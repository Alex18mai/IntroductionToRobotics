// Introduction to Robotics - Homework 2 - Build the traffic lights for a crosswalk

#define STATE_CAR_GREEN 0 // idle state, waits for the people to press the push button, people have red light, cars have green light
#define STATE_CAR_GREEN_BUTTON_PRESSED 1 // push button was pressed and the timer has started, people have red light, cars have green light
#define STATE_CAR_YELLOW 2 // people have red light, cars have yellow light
#define STATE_PEOPLE_GREEN 3 // people have green light, cars have red light, buzzer beeping
#define STATE_PEOPLE_GREEN_BLINKING 4 // people have green blinking light, cars have red light, buzzer beeping faster

// the duration for each state in ms
const int stateDuration[] = {0, 8000, 3000, 8000, 4000};

// the pins for the button, buzzer and 5 leds
const int buttonPin = 2,
          buzzPin = 3,

          carRedPin = 5,
          carYellowPin = 6,
          carGreenPin = 7,
          
          peopleRedPin = 10,
          peopleGreenPin = 11;

// the data rate for the Serial port in bps
const int serialDataRate = 9600;

// the tone and delay constants
const int noBuzzTone = 0,

          greenBuzzTone = 300,
          blinkingBuzzTone = 700,

          greenBuzzDelay = 500,
          blinkingBuzzDelay = 200,
          ledBlinkingDelay = 200;
          
const unsigned long debounceDelay = 50;

// the variables used for current state, push button debounce, light blinking and buzzer beeping
int currentState = STATE_CAR_GREEN, 

    buttonState = HIGH,
    lastReading = HIGH,
    
    peopleGreenLed = HIGH,
    isBuzzOn = HIGH;    

// the variables used for keeping track of the last time an action was performed
unsigned long lastDebounceTime = 0,
              lastStateTime = 0,
              lastPeopleGreenLedTime = 0,
              lastBuzzTime = 0;

void setup() {
  // pins for the button and buzzer
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzPin, OUTPUT);
  
  // pins for the car lights
  pinMode(carRedPin, OUTPUT);
  pinMode(carYellowPin, OUTPUT);
  pinMode(carGreenPin, OUTPUT);
  
  // pins for the people lights
  pinMode(peopleRedPin, OUTPUT);
  pinMode(peopleGreenPin, OUTPUT);

  // Serial port
  Serial.begin(serialDataRate);
}

void loop() {
  manageCurrentState();
  executeCurrentState();
}

// function that checks if the current state should change and does so accordingly
void manageCurrentState() {
  bool isButtonPressed = buttonPressed();

  if (currentState == STATE_CAR_GREEN) {
    if (isButtonPressed) {
      currentState = STATE_CAR_GREEN_BUTTON_PRESSED;
      
      lastStateTime = millis();    
    }
  }
  else if (millis() - lastStateTime > stateDuration[currentState]) {
    switch (currentState) {
      case STATE_CAR_GREEN_BUTTON_PRESSED:                
        currentState = STATE_CAR_YELLOW;   
        break;

      case STATE_CAR_YELLOW:                
        currentState = STATE_PEOPLE_GREEN;  
        isBuzzOn = HIGH;
        lastBuzzTime = millis();  
        break;

      case STATE_PEOPLE_GREEN:                
        currentState = STATE_PEOPLE_GREEN_BLINKING; 
        isBuzzOn = HIGH;
        lastBuzzTime = millis(); 
        peopleGreenLed = HIGH;
        lastPeopleGreenLedTime = millis(); 
        break;
        
      case STATE_PEOPLE_GREEN_BLINKING:                
        currentState = STATE_CAR_GREEN; 
        break;
      
      default:
        break;
    }         
    
    lastStateTime = millis();
  }

  Serial.println(currentState);
}

// function that checks if the button was pressed using debounce
bool buttonPressed() {
  int reading = digitalRead(buttonPin);

  if (reading != lastReading) {
    lastDebounceTime = millis();
  }
  lastReading = reading;

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        return true;
      }
    }
  }

  return false;
}

// function that executes the current state
void executeCurrentState() {
  switch (currentState) {
      case STATE_CAR_GREEN: // red light for people, green light for cars, no buzzer tone              
        setPeopleLights(HIGH, LOW);
        setCarLights(LOW, LOW, HIGH);
        setBuzzer(noBuzzTone);
        break;
        
      case STATE_CAR_GREEN_BUTTON_PRESSED: // red light for people, green light for cars, no buzzer tone                
        setPeopleLights(HIGH, LOW);
        setCarLights(LOW, LOW, HIGH);
        setBuzzer(noBuzzTone);
        break;

      case STATE_CAR_YELLOW: // red light for people, yellow light for cars, no buzzer tone                 
        setPeopleLights(HIGH, LOW);
        setCarLights(LOW, HIGH, LOW);
        setBuzzer(noBuzzTone);
        break;

      case STATE_PEOPLE_GREEN: // green light for people, red light for cars, buzzer tone beeping           
        if (millis() - lastBuzzTime > greenBuzzDelay) {
          isBuzzOn = !isBuzzOn;   
          lastBuzzTime = millis();    
        }
        
        setPeopleLights(LOW, HIGH);
        setCarLights(HIGH, LOW, LOW);
        setBuzzer(greenBuzzTone * isBuzzOn); // if the buzzer is not on, the multiplication result will be 0 = noBuzzTone which marks that there should be no tone  
        break;
        
      case STATE_PEOPLE_GREEN_BLINKING: // green blinking light for people, red light for cars, buzzer tone beeping
        if (millis() - lastPeopleGreenLedTime > ledBlinkingDelay) {
          peopleGreenLed = !peopleGreenLed; 
          lastPeopleGreenLedTime = millis();           
        }             
        if (millis() - lastBuzzTime > blinkingBuzzDelay) {
          isBuzzOn = !isBuzzOn;    
          lastBuzzTime = millis();   
        }
        
        setPeopleLights(LOW, peopleGreenLed);
        setCarLights(HIGH, LOW, LOW); 
        setBuzzer(blinkingBuzzTone * isBuzzOn); // if the buzzer is not on, the multiplication result will be 0 = noBuzzTone which marks that there should be no tone
        break;
      
      default:
        break;
    }   
}

void setPeopleLights(int redValue, int greenValue) {
  digitalWrite(peopleRedPin, redValue);
  digitalWrite(peopleGreenPin, greenValue);
}

void setCarLights(int redValue, int yellowValue, int greenValue) {
  digitalWrite(carRedPin, redValue);
  digitalWrite(carYellowPin, yellowValue);
  digitalWrite(carGreenPin, greenValue);
}

void setBuzzer(int buzzTone) {
  if (buzzTone == noBuzzTone) {
    noTone(buzzPin);
  }
  else {
    tone(buzzPin, buzzTone);  
  }
}
