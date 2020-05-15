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

// variable for different functions
int highScoreAddressLevel1 = 0;
int highScoreAddressLevel2 = 4;
int highScoreAddressLevel3 = 8;
int highScoreLevel1 = 0;
int highScoreLevel2 = 0;
int highScoreLevel3 = 0;
int itsHighScore = 0;
int startingLevelValue = 1;
int level = 0;
int lives = 0;
int remainingTime = 0;
int calScore = 0;
int row = 0;
int col = 0;
long randNumber;
int redVal;
int greenVal; 
int blueVal;


// variable for time
unsigned long previousMillis = 0;

// varibale for lcd display
const int RS = 7;
const int enable = 6;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

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

// this function delete the last >
void clearPosition() {
  lcd.setCursor(2, 0);
  lcd.print(" ");
  lcd.setCursor(9, 0);
  lcd.print(" ");  
  lcd.setCursor(10, 1);
  lcd.print(" ");   
  lcd.setCursor(0, 1);
  lcd.print(" ");     
}

// this is a function who show on lcd display end message when the game is done
void showEndMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Congratulations!");
  previousMillis = millis();
  int localStay = openOption();
  int choose = 0;

  // here, after Congratulations, I will show a "you made a new high score", if it is
  for (int i = 1; i == localStay;) { 
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= 3000) {
           previousMillis = currentMillis;
           if (itsHighScore == 1) {
                lcd.clear();
                lcd.setCursor(1, 0);
                lcd.print("You made a new");
                lcd.setCursor(3, 1);
                lcd.print("high score!");
           }
           // here I will show the player's achievements
           for (int i = 1; i == localStay;) { 
              unsigned long currentMillis = millis();
              if (currentMillis - previousMillis >= 3000) {
                  previousMillis = currentMillis;
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("Score: ");
                  lcd.setCursor(6, 0);
                  lcd.print(calScore);
                  lcd.setCursor(9, 0);
                  lcd.print("Time: ");
                  lcd.setCursor(14, 0);
                  lcd.print(20 - remainingTime);

                  lcd.setCursor(2, 1);
                  lcd.print("Again");
                  lcd.setCursor(10, 1);
                  lcd.print("Menu");
                  choose = 1;
                    
                  
              }
              // here is a mini menu in the end of the game
              if (choose == 1) {
                  xValue = analogRead(pinX);
                 
                  if (xValue < minThreshold && joyMoved == false) {
                      if (digit > 1) {
                          digit--;
                      } else {
                          digit = 2;
                      }
                      joyMoved = true;
                  }
              
                  if (xValue > maxThreshold && joyMoved == false) {
                      if (digit < 2) {
                          digit++;
                      } else {
                          digit = 1;
                      }
                      joyMoved = true;
                  } 
                
                  if (xValue >= minThreshold && xValue <= maxThreshold) {
                      joyMoved = false;
                  }


                  yValue = analogRead(pinY);
                  // if the > are in front of Again and yValue is high, I will start the game again
                  if (digit == 1) {
                      if(digit != lastDigit) {
                          lcd.setCursor(9, 1);
                          lcd.print(" ");
                          lastDigit = digit;
                      }
                      lcd.setCursor(1, 1);
                      lcd.print(">");
                      if (yValue > maxThreshold) {
                          startGame();
                      }  
                  }
                  
                  // if the > are in front of Menu and yValue is high, I will show the first menu
                  if (digit == 2) {
                      if(digit != lastDigit) {
                          lcd.setCursor(1, 1);
                          lcd.print(" ");
                          lastDigit = digit;
                      }
                      lcd.setCursor(9, 1);
                      lcd.print(">"); 
                      if (yValue > maxThreshold) {
                          setMenu();
                          chooseOption();
                      }
                  }
              }
    
           }
      }
     
   }
}

// Seting the color
void setColor(int color) {
  if (color == 1){
      redVal = 255;
      greenVal = 0;
      blueVal = 0;
      
      analogWrite(redPin, redVal); 
      analogWrite(greenPin, greenVal); 
      analogWrite(bluePin, blueVal);   
  } else if (color == 2) {
      redVal = 0;
      greenVal = 255;
      blueVal = 0;
      
      analogWrite(redPin, redVal); 
      analogWrite(greenPin, greenVal); 
      analogWrite(bluePin, blueVal); 
    } 
}

// Checking if one step away from a bomb.
void checkBombs(int row, int col) {
      if (row == 0 && col == 0) {
             if (currentMap[0][1] == 1 || currentMap[1][1] == 1 || currentMap[1][0] == 1) {
                 setColor(1);
             } else {
                 setColor(2);
             }
      } else if (row == 0 && col == 7) {
            if (currentMap[0][6] == 1 || currentMap[1][6] == 1 || currentMap[1][7] == 1) {
                setColor(1);
            } else {
                setColor(2);
            }
       } else if (row == 7 && col == 7) {
            if (currentMap[7][6] == 1 || currentMap[6][6] == 1 || currentMap[6][7] == 1) {
                setColor(1);
            } else {
                setColor(2);
              }
       } else if (row == 7 && col == 0) {
            if (currentMap[6][0] == 1 || currentMap[6][1] == 1 || currentMap[7][1] == 1) {
                setColor(1);
            } else {
                setColor(2);
              }
       } else if (row == 0) {
            if (currentMap[row][col-1] == 1 || currentMap[row][col+1] == 1 || currentMap[row + 1][col] == 1) {
                setColor(1);
            } else {
                setColor(2);
              }
       } else if (row == 7) {
            if (currentMap[row][col-1] == 1 || currentMap[row][col+1] == 1 || currentMap[row - 1][col] == 1) {
                setColor(1);
            } else {
                setColor(2);
            }
       } else if (col == 0) {
            if (currentMap[row - 1][col] == 1 || currentMap[row + 1][col] == 1 || currentMap[row][col + 1] == 1) {
                setColor(1);
            } else {
                setColor(2);
            }
       } else if (col == 7) {
            if (currentMap[row - 1][col] == 1 || currentMap[row + 1][col] == 1 || currentMap[row][col - 1] == 1) {
                setColor(1);
            } else {
                setColor(2);
            }
       } else {
            if (currentMap[row - 1][col] == 1 || currentMap[row + 1][col] == 1 || currentMap[row][col + 1] == 1 || currentMap[row][col - 1]) {
                setColor(1);
            } else {
                setColor(2);
            }
       }
}

// this is a function who set the variables for game and set the
// display for game, the key words
void setGame() {
  int localStay = openOption();
  level = startingLevelValue;
  previousMillis = millis();
  itsHighScore = 0;
  calScore = 0;
  lives = 2;
  remainingTime = 20;
  row = 0;
  col = 0;
  lcd.setCursor(0, 0);
  lcd.print("Level:");
  lcd.setCursor(6, 0);
  lcd.print(startingLevelValue); 
  lcd.setCursor(9, 0);
  lcd.print("Lives: ");
  lcd.setCursor(15, 0);
  lcd.print(lives);
  lcd.setCursor(0, 1);
  lcd.print("Score:");
  lcd.setCursor(6, 1);
  lcd.print(calScore);
  lcd.setCursor(9, 1);
  lcd.print("Time:");
  lcd.setCursor(14, 1);
  lcd.print(remainingTime);
  joyMovedFun();
  randNumber = random(5);
  // here I will show the bombs for 5 seconds on matrix and I will set currentMap and pointsMap
  for (int i = 1; i == localStay;) {
      for (int row = 0; row < 8; row++) {
          for (int col = 0; col < 8; col++) {
            if (level == 1) {
                lc.setLed(0, row, col, mapLevel1[randNumber][row][col]);
                currentMap[row][col] = mapLevel1[randNumber][row][col];
                pointsMap[row][col] = 0;
            } else if (level == 2) {
                lc.setLed(0, row, col, mapLevel2[randNumber][row][col]);
                currentMap[row][col] = mapLevel2[randNumber][row][col];
                pointsMap[row][col] = 0;
              } else {
                lc.setLed(0, row, col, mapLevel3[randNumber][row][col]);
                currentMap[row][col] = mapLevel3[randNumber][row][col];
                pointsMap[row][col] = 0;
                }
          }
       }
       unsigned long currentMillis = millis();
       if (currentMillis - previousMillis >= 5000) {
          previousMillis = currentMillis;
          localStay = 0;
       }    
  }
}
// ------------------------------- GAME -----------------------------
void startGame() {
  lcd.clear();
  setGame();
  int localStay = openOption();
  previousMillis = millis();
  for (int i = 1; i == openOption();) { 
       
       if (joyMovedy != true) {
           xValue = analogRead(pinX);
           if (xValue < minThreshold && joyMovedx == false) {
                if (row > 0) {
                    row--;
                } 
                else {
                    row = 7;
                }
                joyMovedx = true;
          }
    
          if (xValue > maxThreshold && joyMovedx == false) {
               if (row < 7) {
                    row++;
                } 
                else {
                    row = 0;
                }
                joyMovedx = true;
          }
          if (xValue >= minThreshold && xValue <= maxThreshold) {
                joyMovedx = false;
          }
      }
     
      if (joyMovedx != true) {  
          yValue = analogRead(pinY);
          if (yValue < minThreshold && joyMovedy == false) {
              if (col < 7) {
                  col++;
              } 
              else {
                  col = 0;
            }
            joyMovedy = true;
          }
    
          if (yValue > maxThreshold && joyMovedy == false) {
              if (col > 0) {
                  col--;
              }
              else {
                  col = 7;
              }
              joyMovedy = true;
          }
          if (yValue >= minThreshold && yValue <= maxThreshold) {
              joyMovedy = false;
          }
      }
      
        lc.setLed(0, col, row, true);
        lc.clearDisplay(0);
        lc.setLed(0, 7, 7, true);
        lc.setLed(0, col, row, false);
      
        // if I have 0 lives or the time is done or I am at final, the game will end
        if (currentMap[col][row] == 1 || remainingTime == 0 || (col == 7 && row == 7)) {
            if (currentMap[col][row] == 1) {
                lives--;
                calScore = calScore - 5;
                if (calScore < 0){
                    calScore = 0;
                }
            }
            lcd.setCursor(15, 0);
            lcd.print(lives);
            // I will check if the playes makes a new high score and if he do, I will update the high score and I will put it in EEPROM memory
            if(lives == 0 || remainingTime == 0 || (col == 7 && row == 7)) {
              calScore = calScore + remainingTime;
              if (level == 1) { 
                   if (calScore > highScoreLevel1) {
                      highScoreLevel1 = calScore;
                      itsHighScore = 1;
                      EEPROM.put(highScoreAddressLevel1, highScoreLevel1);
                   }
              } else if (level == 2) { 
                   if (calScore > highScoreLevel2) {
                      highScoreLevel2 = calScore;
                      itsHighScore = 1;
                      EEPROM.put(highScoreAddressLevel2, highScoreLevel2);
                   }
               } else if (level == 3) { 
                   if (calScore > highScoreLevel3) {
                      highScoreLevel3 = calScore;
                      itsHighScore = 1;
                      EEPROM.put(highScoreAddressLevel3, highScoreLevel3);
                   }
               }
               lc.clearDisplay(0);// clear screen
               analogWrite(redPin, 0); 
               analogWrite(greenPin, 0); 
               analogWrite(bluePin, 0); 
               showEndMessage();
               openOp = 0;  
            }else {
                 previousMillis = millis();
                 currentMap[col][row] = 0;
                 for (int i = 1; i == localStay;) {
                     for (int row = 0; row < 8; row++) {    
                          for (int col = 0; col < 8; col++) {
                               lc.setLed(0, row, col, currentMap[row][col]);
                          }
                     }
                     unsigned long currentMillis = millis();
                     if (currentMillis - previousMillis >= 3000) {
                        previousMillis = currentMillis;
                        localStay = 0;
                     }    
                }
            }
        } else {
            if (pointsMap[col][row] != 1) {
                calScore++;
                lcd.setCursor(6, 1);
                lcd.print(calScore);
                pointsMap[col][row] = 1;
            }
            
              
          } 

    
         // here I do 2 things
         // 1. I decrease the seconds
         // 2. Every second I check if the player its at a safe distance from RGB led,
         // if he is not, I will turn off the rgb led     
         digitalWrite(trigPin, LOW);
         unsigned long currentMillis = millis();
         if (currentMillis - previousMillis >= 1000) {
              previousMillis = currentMillis;
              remainingTime--;
              if (remainingTime < 10) {
                  lcd.setCursor(14, 1);
                  lcd.print("0");  
                  lcd.setCursor(15, 1);
                  lcd.print(remainingTime);
              } else { 
                  lcd.setCursor(14, 1);
                  lcd.print(remainingTime);
              }
              digitalWrite(trigPin, HIGH);
              delayMicroseconds(10);
              digitalWrite(trigPin, LOW);
              duration = pulseIn(echoPin, HIGH);    
              distance = duration*0.034/2;
              if (distance >= 30) {
                    checkBombs(col, row);
              } else {
                    analogWrite(redPin, 0); 
                    analogWrite(greenPin, 0); 
                    analogWrite(bluePin, 0);
                }
         }
         
  }
 
  setMenu();
}
// -----------------------------------------------------------------

// TODO create function goToSettings()

// ------------------------ High Score --------------------------
void goToHighScore() {
    lcd.clear();
    for (int i = 1; i == openOption();) {
        lcd.setCursor(1, 0);
        lcd.print("HighS per level");
        lcd.setCursor(0, 1);
        lcd.print("1:");
        lcd.setCursor(2, 1);
        lcd.print(highScoreLevel1);
        lcd.setCursor(6, 1);
        lcd.print("2:");
        lcd.setCursor(8, 1);
        lcd.print(highScoreLevel2);
        lcd.setCursor(12, 1);
        lcd.print("3:");
        lcd.setCursor(14, 1);
        lcd.print(highScoreLevel3);
    }
    setMenu();
}

// ------------------------ Info --------------------------
void goToInfo() {
    int whichInfo = 0; 
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Creator Name");     
    lcd.setCursor(0, 1);
    lcd.print("Iordache Bogdan");
    previousMillis = millis();
    
    for (int i = 1; i == openOption();) {
         unsigned long currentMillis = millis();
         // every 3 second, I display a message
         if (currentMillis - previousMillis >= 3000) {
             previousMillis = currentMillis;
             whichInfo++;
             if (whichInfo == 1) {
                lcd.clear();
                lcd.setCursor(3, 0);
                lcd.print("Game name:");     
                lcd.setCursor(6, 1);
                lcd.print("Syfe");
             }
             if (whichInfo == 2) {
                lcd.clear();                                                 
                lcd.setCursor(1, 0);
                lcd.print("GitHub: github");     
                lcd.setCursor(1, 1);
                lcd.print(".com/BogdanICH");
             }
             if (whichInfo == 3) {
                lcd.clear();
                lcd.setCursor(3, 0);
                lcd.print("Powered by");     
                lcd.setCursor(1, 1);
                lcd.print("@UnibucRobotics");
             }
             if (whichInfo == 4) {
                lcd.clear();
                lcd.setCursor(2, 0);
                lcd.print("Creator Name");     
                lcd.setCursor(0, 1);
                lcd.print("Iordache Bogdan");
             }
                
             if (whichInfo == 4) {
                 whichInfo = 0;
             }
                  
         }
    }


// TODO create function openOption() 

// TODO create function chooseOption()

void welcomeMsg() {
  lcd.setCursor(4, 0);
  lcd.print("Welcome");  
}

void setup() {
   // put your setup code here, to run once:
  lcd.begin(16, 2);
  // here I will get the last highScore from eeprom memory
  EEPROM.get(highScoreAddressLevel1, highScoreLevel1);
  EEPROM.get(highScoreAddressLevel2, highScoreLevel2);
  EEPROM.get(highScoreAddressLevel3, highScoreLevel3);
  
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 2); // sets brightness (0~15 possible values)
  
  pinMode(pinSW, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode (echoPin, INPUT); // Sets the echoPin as an Input
  randomSeed(analogRead(0)); // use for random number
  Serial.begin(9600);
}


void loop() {
       welcomeMsg();
       unsigned long currentMillis = millis();
       if (currentMillis - previousMillis >= 2000) {
          previousMillis = currentMillis;
          setMenu();
          // choose the option from menu
          // TODO call function 'chooseOption();'
       }   
}
