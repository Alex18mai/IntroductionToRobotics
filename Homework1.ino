// Introduction to Robotics - Homework 1 - Control a RGB led using 3 potentiometers

// Analog-In signal from potentiometers
const int potRedPin = A2,
          potGreenPin = A1,
          potBluePin = A0;

// PWM-enabled pins in order to emulate Analog-Out
const int redPin = 9,
          greenPin = 10,
          bluePin = 11;

// value constants
const int minLedValue = 0,
          maxLedValue = 255,
          minPotValue = 0, 
          maxPotValue = 1023;

// the data rate for the Serial port in bps
const int serialDataRate = 9600;

// semicolon string used for printing to the Serial Monitor
const String semicolon = "; ";

// set true if the led has a common anode and false if the led has a common cathode
const bool commonAnode = false;

// variables used for the potentiometer and led values
int potRedValue = 0, 
    potGreenValue = 0, 
    potBlueValue = 0,
    
    redValue = 0, 
    greenValue = 0, 
    blueValue = 0;

void setup() {
  // pins for the 3 potentiometers
  pinMode(potRedPin, INPUT);
  pinMode(potGreenPin, INPUT);
  pinMode(potBluePin, INPUT);
  
  // pins for the RGB led
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  // Serial port
  Serial.begin(serialDataRate);
}

void loop() {
  // read the potentiometer values
  potRedValue = analogRead(potRedPin);
  potGreenValue = analogRead(potGreenPin);
  potBlueValue = analogRead(potBluePin);

  // compute the led values  
  redValue = mapPotToLed(potRedValue);
  greenValue = mapPotToLed(potGreenValue);
  blueValue = mapPotToLed(potBlueValue);

  // print the led values
  Serial.println(redValue + semicolon + greenValue + semicolon + blueValue);
  
  // set the led color
  setColor(redValue, greenValue, blueValue);
}

// function for mapping a potentiometer value (0, 1023) to a led value (0, 255) 
int mapPotToLed(int value){
  return map(value, minPotValue, maxPotValue, minLedValue, maxLedValue);
}

// function for setting the color of the RGB led
void setColor(int redValue, int greenValue, int blueValue) {
  if (commonAnode) {
    redValue = maxLedValue - redValue;
    greenValue = maxLedValue - greenValue;
    blueValue = maxLedValue - blueValue;
  }
  analogWrite(redPin, redValue); 
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
