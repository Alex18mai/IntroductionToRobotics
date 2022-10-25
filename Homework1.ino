// Analog-In signal from potentiometers
const int potRedPin = A2,
          potGreenPin = A1,
          potBluePin = A0;

// PWM-enabled pins in order to emulate Analog-Out
const int redPin = 9,
          greenPin = 10,
          bluePin = 11;

// value constants
const int minAnalogValue = 0,
          maxAnalogValue = 255,
          minPotValue = 0, 
          maxPotValue = 1023;

// semicolon string used for printing to the Serial Monitor
const String semicolon = "; ";

// set true if the led has a common anode and false if the led has a common cathode
const bool commonAnode = false;

// variables used for the pot and led values
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
  
  Serial.begin(9600);
}

// function for mapping a pot value (0, 1023) to an analog value (0, 255) 
int mapPotAnalog(int value){
  return map(value, minPotValue, maxPotValue, minAnalogValue, maxAnalogValue);
}

// function for setting the color of the RGB led
void setColor(int redValue, int greenValue, int blueValue) {
  if (commonAnode) {
    redValue = maxAnalogValue - redValue;
    greenValue = maxAnalogValue - greenValue;
    blueValue = maxAnalogValue - blueValue;
  }
  analogWrite(redPin, redValue); 
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

void loop() {
  // read the potentiometer values
  potRedValue = analogRead(potRedPin);
  potGreenValue = analogRead(potGreenPin);
  potBlueValue = analogRead(potBluePin);

  // calculate the led values  
  redValue = mapPotAnalog(potRedValue);
  greenValue = mapPotAnalog(potGreenValue);
  blueValue = mapPotAnalog(potBlueValue);

  // print the led values
  Serial.println(redValue + semicolon + greenValue + semicolon + blueValue);
  
  // set the led color
  setColor(redValue, greenValue, blueValue);
}
