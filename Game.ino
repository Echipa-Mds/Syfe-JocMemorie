#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <LedControl.h>

LedControl lc = LedControl(13, 12, 11, 1); //DIN, CLK, LOAD, No. DRIVER
// pin 13 is connected to the MAX7219 pin 1
// pin 12 is connected to the CLK pin 13
// pin 11 is connected to LOAD pin 12

// declare pins of distance senzor
const int trigPin = 9;
const int echoPin = 10;


// declare pins for RGB led
const int redPin = A0; 
const int greenPin = A1;
const int bluePin = A2; 


void setMenu() {
  lcd.clear();
  // TODO 'Play' option
  // TODO 'High Score' option
  // TODO  'Settings' option
  // TOFO 'Info' option
  lc.clearDisplay(0);
}


void setup() {

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode (echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
}


void loop() {
        
       unsigned long currentMillis = millis();
       if (currentMillis - previousMillis >= 2000) {
          previousMillis = currentMillis;
          // choose the option from menu
         
       }   
}
