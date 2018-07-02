
Overview
--------------------------------------------
* Name: timer_arduino
* Title: Micro-controller Countdown Timer
* Description: Countdown Timer: Range 1-99 minutes. 
Output time (mm:ss) to seven segment display(TM1637) and Audio to Buzzer.
Input: Push button to start.  10K Pot used for time select.
* Author: Gavin Lyons
* Note: Two alternative designs, two different ino files.

libraries
--------------------------
* https://github.com/avishorp/TM1637
*  Version 1.1.0
*  TM1637Display.h // to drive the Tm1637 module


Software Used
------------------
Arduino 1.8.5

Eagle 9.0.1


Parts List
------------------------------
The schematic drawn in eagle is in documents section. 

You will need following parts.

>
> Arduino based board with 4 digital pins and 1 analog pin. (In this case nano or Attiny85)
>
> Resistor: 220ohms 
>
> tm1637 seven segment module
>
> one 10 k pot
>
> one pushbutton
>
> One on/off SPST switches
>
> One piezo buzzer
>

Features
----------------------
The user selects the countdown time (1-99 minutes) with the pot then starts with the pushbutton.
Time remaining is displayed on seven segment display. When finished the buzzer is activated and done displayed on 7-seg.
Two alternative designs, two different ino files and schematics. Design one uses the nano, design two the attiny85. 

Design number one :  file:  timer_arduino.ino based on arduino nano.

![ScreenShot schematic one ](https://github.com/gavinlyonsrepo/timer_arduino/blob/master/documentation/eagle/tm1637.jpg)

Design number two :  file:  timer_attiny85_arduino.ino based on attiny85.
The current consumption of this circuit is 9mA in countdown state and 11mA in alarm state.
The brightness if display is set to a low setting in the program.

![ScreenShot schematic two ](https://github.com/gavinlyonsrepo/timer_arduino/blob/master/documentation/eagle/timer16372.jpg)
 
Copyright
---------
Copyright (C) 2018 Gavin Lyons 
see LICENSE.md in documentation section 
for more details

