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

[![Homework 1 - Video](https://img.youtube.com/vi/odUR5Z-gZcE/0.jpg)](https://www.youtube.com/watch?v=odUR5Z-gZcE)

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

[![Homework 2 - Video](https://img.youtube.com/vi/TJ6v7SmZhKY/0.jpg)](https://www.youtube.com/watch?v=TJ6v7SmZhKY)

</details>
