#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <LedControl.h>

LedControl lc = LedControl(13, 12, 11, 1); //DIN, CLK, LOAD, No. DRIVER
// pin 13 is connected to the MAX7219 pin 1
// pin 12 is connected to the CLK pin 13
// pin 11 is connected to LOAD pin 12

// declare all the joystick pins
const int pinSW = 0; // digital pin connected to switch output
const int pinX = A5; // A4 - analog pin connected to X output
const int pinY = A4; // A5 - analog pin connected to Y output

// declare pins of distance senzor
const int trigPin = 9;
const int echoPin = 10;


// declare pins for RGB led
const int redPin = A0; 
const int greenPin = A1;
const int bluePin = A2; 

// states of the button press
int swState = LOW;
int lastSwState = LOW;
int switchValue = 0;
int xValue = 0;
int yValue = 0;
bool joyMovedy = false;
bool joyMovedx = false;
bool joyMoved = false;
int minThreshold = 400;
int maxThreshold = 600;

// function for set the joyMove
void joyMovedFun() {joyMovedx = false; joyMovedy = false;}

// here is a function for set the menu
void setMenu() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Play");
  lcd.setCursor(10, 0);
  lcd.print("HighS"); 
  lcd.setCursor(1, 1);
  lcd.print("Settings");
  lcd.setCursor(11, 1);
  lcd.print("Info"); 
  joyMovedFun();
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
          setMenu();
          // choose the option from menu
                 
       }   
}
