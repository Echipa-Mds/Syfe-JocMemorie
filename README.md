# Syfe-MemoryGame
Name of the project: Syfe
Description:
In the first 2 seconds, a Welcome message will be displayed on the lcd display, and after that a menu will be shown.

 * Menu(You can go through the menu using the joystick.There will be a cursor in the shape of ">" in front of several menu options: 
   * Play (while playing, the LCD will display the score, time, level and lives)
   * High score (displays the highest score of the player for each of the three levels)
   * Settings (where you can set the level for the game and leave feedback)

# The game: #

* Before the game, a map with bombs will be randomly chosen
* In the first 5 seconds, bombs will be displayed on the screen for 5 seconds, time in which the player cannot move. The player must remember their location because they disapper after 5 seconds.
* Then, you will be placed in the upper left corner and you will have to reach the opposite corner without hitting too many bombs
* The number of bombs depends on the level.
* if you hit a bomb, you will lose 5 points from your score but you will be shown the location of the bombs for 3 seconds on the display.
* The player has 20 seconds to finish the level.
# The levels: #

There are 3 levels, and each level has 5 more bombs than the previous one.
* level 1: 10 bombs
* level 2: 15 bombs
* level 3: 20 bombs.

You can set the level from the settings.
# The feedback: #
In the settings menu you can give a feedback to the game from 1 to 5.
# The RGB led: #

* If you are one step away from a bomb, the LED becomes red
* If you are two or more steps away from a bomb, the LED becomes green
# The distance sensor: #

Detects your distance and turns of the red/green option if you are too close to the screen.
The score:

* In order to make a high score, you must go through as many boxes and as few bombs as possible until you reach the bottom right corner
you will receive a point on each box
* Score is obtained by going through as many boxes but as few bombs as possible until you reach the bottom right corner. The player will recieve a point for each box.
* Each box is unique, so you cannot get two points for the same box.
* If you step on a bomb, you will lose 5 points. If your score is less than 5, the score becomes 0.
* At the end of te game, the remaining seconds will be transformed into points(each second representing one additional point)
high score for each level will be stored in EEPROM
# End of the game: #

* At the end of the game, the player will be greeted with a "Congratulations" message and a "You made a new high score" if the player has gotten more points than his previous highscore. After that, the final score and number of seconds he spent will be displayed on top of the LCD.At the bottom a Play again and a Menu with the ">" cursor.



# Structura UML #
![f5f051e1-0580-43d2-890f-5c34ea8aa0cd](https://user-images.githubusercontent.com/62382833/82090876-0bfa4780-96ff-11ea-8691-048855d14597.jpg)


# User Stories #


| # | Comments | Notes | Priority | Status |
| ------------- | ------------- | ------------- |------------- | ------------- |
| 1  | I would like to see my highest score.  | Highscores should be saved and and should remain even after the device is restarted. | Required | Done |
| 2  | I want to play multiplayer with other people and see who finishes fasterwhen we rush to the end point.| A multiplayer mode would be require player interaction. In the current iteration competition is achieved through comparing each player scores in different gaming sessions and mesured through highscore.| Unnecessary | Cancelled |
| 3  | I have played with the game for quite a bit and the proximity light is too bright. Can it be toned down ?  | On the initial game, lenght expose to the bright light led to reduced player satisfaction.We have installed a distance sensor that turns on the led only when the player is at a reasonable distance from the game.| Optional | Done |
| 4  | The circuitry is exposed and can be easily messed up.| We have built a casing that houses the hardware. | Highly recommended(but not required) | Done |
| 5  | The game is too easy and boring.. | We have added 2  more levels each with increased number of bombs. | Recommended | Done |
| 6  | The game runs slowly and has moments when it stops running.  | The game has a low duration and a save&load feature would be impractical. | Highly recommended | Done |
| 7  | I would like to save and load the game.| The game has a low duration and a save&load feature would be impractical. | Very Low Priority | Cancelled |
| 8  | Does this game have sound ?  | Sound could create a pleasant environment for playing the game. | Recommended | Canceled due to time retraints |
| 9  |So the game has no story? That is very bad.  | A story was added. It night creatge immersion(probably not).| Low priority | Done |
| 10  | The game is unforgiving if you are distracted even for a second at the beginning.| We have added a second life as an error margin. | Low priority | Done |

*Video link: https://youtu.be/ZYHMe5cUwU4

Used materials: 8x8 LED matrix, LCD display, Joystick, MAX7219 Driver, RGB led, arduino board, breadboards, distance sensor, potentiometer, wires, resistors, electrolytic capacitor of 10 μF, ceramic capacitor of 104 pF




# Design & Arhitecture



![Design](https://user-images.githubusercontent.com/62382833/84704184-1ad45400-af62-11ea-8597-5a7863ee5c4a.png)

​	Model - The software component which represents the conceptual assets the application offers, such as a database. For this project, we used EEPROM, a portion inside the arduino board that saves data even when it is turned off.

● View - Creates the interface the user sees, with respect to the actions sent by the controller or directly interrogating the models. The final information will be displayed on the LCD display as text.

● Controller - Logical component of the application, that intercepts the user's requests, interrogates the data base using the model, constructs an answer using the view and then returns to the client as a text on the LCD Display. The joystick will be the controller.



#                                   Automatic Testing



## Testare LCD display

​	The first test we took care of is checking the LCD screen. The reason it represented a priority is because without it, all the other functions become unusable.
​	

#### 	The test consists of checking if:	  

* The LCD display lights up and displays the text correctly on the screen (brightness, contrast) 

* The LCD display displays the menu on the screen

* The LCD display responds correctly when a joystick is used for navigation between menu commands

  

 #### Following the test we found:    

* The screen lit up each time, but the brightness and contrast weren't always adequate, causing the letters to become unreadable sometimes. The problem was caused by the cable connection on the breadboard (the board that connects the LCD display and the arduino uno board )

  > Solution: The wires were changed with higher quality ones.

* The menu was displayed correctly on the screen each time (after changing the affected wires)    

* Most of the time, the joystick behaves correctly, but there were times when the joystick was too sensitive and would jump from an option to another.

  > Solution: we modified the movement perimeter of the joystick so that it is more precise.



## Matrix testing

​		The second test we did was for the 8x8 matrix on which the game is displayed 

#### 	The test consists of checking if :

* all pixels work

* the pixels have the corresponding brightness

* the bombs are displayed correctly on the matrix

  


####	Following the tests we found :

 * Sometimes a part of the pixels would not work, making the game impossible to play. The problem was due to the connection of the matrix with the breadboard and the resistors.

  > Solution: We replaced the affected wires and we reconnected both the matrix on the breadboard and the resistors.

 * The pixels did not always have the same intensity, the problem being caused by the connection of the matrix with the breadboard and by the connection of the resistors with the breadboard

  > Solution: We disconnected both components and re-connected them better

 * As long as all the pixels worked on the matrix, the bombs were displayed correctly.



## Testing the RGB LED



​	The third test I did was for the RGB LED near the matrix.

#### The test consists of checking if:

   * the LED works
   * the light intensity is appropriate
   * the two colors I use go (green & red)

#### Following the test we found:

   * The LED worked every time (no connection problems with the breadboard)

   * The two colors have always worked

   * In the first phase the light intensity was too high and you could not look at the LED.

     > Solution: We replaced the initial resistance with a stronger one and the intensity was adjusted.

     

## Distance sensor testing



​	We performed the fourth test to decide if the distance sensor works properly, ie if it approximates well the distance from it to the first object in front of it.

#### 	Following the tests performed, we found that the sensor works properly.



## EEPROM (Arduino external memory) testing

​	We performed the fifth test to determine if the best 3 scores are stored correctly in the external memory of the arduino uno board.
​	This means that if the game is stopped (with and without power) the 3 scores will be stored and will be displayed when the game starts again, without differences from the initial information.
​	To test this external memory, EEPROM, we have to play long enough to achieve the 3 best scores. After we have these 3 scores, we can close the game and turn it on again, entering the High Score option in the menu to see if the 3 scores have remained the same as before.

####		After performing the test we found that this feature works correctly (can be seen in the video presentation of the game).




Bug reporting:

* Navigation arrow: remained on the screen next to the last option when we switched to a new menu option, duplicating.

  > Solution: each time we switched to a new option, we delete the text from all the boxes where the arrow can be found and display it again in the box corresponding to the current option.

 * Joystick sensitivity: while wanting to select a menu option, due to inaccurate perimeter and sensitivities other options were selected. 

   > Solution: We reduced the perimeter of movement in the joystick, making it more precise     

 * Navigation arrow: when entering an option, the navigation arrow remains in place.

   > Solution: we have used the function to delete the text from each position where the arrow can be found when we enter a new option.



