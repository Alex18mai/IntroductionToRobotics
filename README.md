# Introduction To Robotics (2022 - 2023)

Introduction to Robotics laboratory homework, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each homework includes requirements, implementation details, code and image files.


<hr>


### [Homework #1](../master/Homework1.ino) 

<details><summary> <b>Task Requirements</b> </summary></br>

Control a RGB led using 3 potentiometers.

</details>

<details><summary> <b>Picture</b> </summary></br>

![Homework 1](assets/Homework1.jpg)

</details>

<details><summary> <b>Video</b> </summary></br>

[![Homework 1 - Video](https://img.youtube.com/vi/odUR5Z-gZcE/0.jpg?)](https://www.youtube.com/watch?v=odUR5Z-gZcE)

</details>


<hr>


### [Homework #2](../master/Homework2.ino)

<details><summary> <b>Task Requirements</b> </summary></br>

Build the traffic lights for a crosswalk using: 
* 2 LEDs to represent the traffic lights for people (red and green)
* 3 LEDs to represent the traffic lights for cars (red, yellow and green)

</br>

The system will go through 4 states:
* STATE 1
  + Trigger : None (default state)
  + Cars : GREEN
  + People : RED
  + Sound : None
  + Duration : inf
  
* STATE 2
  + Trigger: 8 seconds after the push button is presses while in STATE 1
  + Cars : YELLOW
  + People : RED
  + Sound : None
  + Duration : 3 seconds
  
* STATE 3
  + Trigger : after STATE 2 has ended
  + Cars : RED
  + People : GREEN
  + Sound : Buzzer beeping
  + Duration : 8 seconds
  
* STATE 4
  + Trigger : after STATE 3 has ended
  + Cars : RED
  + People : GREEN BLINKING
  + Sound : Buzzer beeping faster
  + Duration : 4 seconds

</br>

Additional info:
* After STATE 4 has ended, the default state (STATE 1) is reinstated.
* Pressing the button in any state other than state 1 should NOT yield any actions.
* The program is implemented without using delay().

</details>

<details><summary> <b>Picture</b> </summary></br>

![Homework 2](assets/Homework2.jpg)

</details>

<details><summary> <b>Video</b> </summary></br>

[![Homework 2 - Video](https://img.youtube.com/vi/TJ6v7SmZhKY/0.jpg?)](https://www.youtube.com/watch?v=TJ6v7SmZhKY)

</details>


<hr>


### [Homework #3](../master/Homework3.ino) 

<details><summary> <b>Task Requirements</b> </summary></br>

Draw on a 7-segment display using a joystick.

</br>

The system will go through 2 states:
* STATE 1
  + Trigger : Default state (also initiated after a button press in STATE 2)
  + Current position : Blinking
  + Joystick movement (X and Y axis) : Move current position to one of the neighbors
  + Short button press : Toggle STATE 2
  + Long button press : Reset the system - segments turn OFF and current position goes to decimal point
  
* STATE 2
  + Trigger: Initiated after a button press in STATE 1
  + Current position : The value of the segment
  + Joystick movement (X axis) : Change the value of the segment (from ON to OFF or from OFF to ON)
  + Short button press : Exit back to STATE 1
  + Long button press : No action

</br>

Neighbors based on the current segment and joystick movement:

| Current segment |  UP | DOWN | LEFT | RIGHT |
|:---------------:|:---:|:----:|:----:|:-----:|
|      **a**      | N/A |   g  |   f  |   b   |
|      **b**      |  a  |   g  |   f  |  N/A  |
|      **c**      |  g  |   d  |   e  |   dp  |
|      **d**      |  g  |  N/A |   e  |   c   |
|      **e**      |  g  |   d  |  N/A |   c   |
|      **f**      |  a  |   g  |  N/A |   b   |
|      **g**      |  a  |   d  |  N/A |  N/A  |
|      **dp**     | N/A |  N/A |   c  |  N/A  |

</details>

<details><summary> <b>Picture</b> </summary></br>

![Homework 3](assets/Homework3.jpg)

</details>

<details><summary> <b>Video</b> </summary></br>

[![Homework 3 - Video](https://img.youtube.com/vi/f73uFziqNx4/0.jpg?)](https://www.youtube.com/watch?v=f73uFziqNx4)

</details>



<hr>


### [Homework #4](../master/Homework4.ino) 

<details><summary> <b>Task Requirements</b> </summary></br>

Move through a 4 digit 7-segment display and increment/decrement the numbers using a joystick.

</br>

The system will go through 2 states:
* STATE 1
  + Trigger : Default state (also initiated after a button press in STATE 2)
  + Current position : Dp segment of digit blinking
  + Joystick movement (Y axis) : Cycle through digits
  + Short button press : Toggle STATE 2
  + Long button press : Reset the system - digits reset to zero and current position goes to the first digit
  
* STATE 2
  + Trigger: Initiated after a button press in STATE 1
  + Current position : Dp segment of digit stays on
  + Joystick movement (X axis) : Increment/decrement the number of the current digit in HEX (from 0 to F)
  + Short button press : Exit back to STATE 1
  + Long button press : No action

</details>

<details><summary> <b>Picture</b> </summary></br>

![Homework 4](assets/Homework4.jpg)

</details>

<details><summary> <b>Video</b> </summary></br>

[![Homework 4 - Video](https://img.youtube.com/vi/JqRFzsFz0iI/0.jpg?)](https://www.youtube.com/watch?v=JqRFzsFz0iI)

</details>



<hr>


### [Homework #5](../master/Homework5) 

<details><summary> <b>Task Requirements</b> </summary></br>

</details>

<details><summary> <b>Picture</b> </summary></br>

![Homework 5](assets/Homework5.jpg)

</details>

<details><summary> <b>Video</b> </summary></br>

[![Homework 5 - Video](https://img.youtube.com/vi/JqRFzsFz0iI/0.jpg?)](https://www.youtube.com/watch?v=JqRFzsFz0iI)

</details>

