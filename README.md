
Overview
--------------------------------------------
* Name: timer_arduino
* Title : Countdown Timer, arduino based. 
* Description: Countdown Timer: Range 1-99 minutes. 
Output time (mm:ss) to seven segment display(TM1637) and Audio to Buzzer.
Input: Push button to start.  10K Pot used for time select.
* Author: Gavin Lyons

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
> Arduino based board with 4 digital pins and 1 analog pin. (eg nano)
>
> Resistors: 220ohms 
>
> tm1637 seven segment module
>
> one 10 k pot
>
> one pushbutton
>
> two on/off SPST switches
>
> One buzzer
>

Features
----------------------

![ScreenShot schematic](https://github.com/gavinlyonsrepo/timer_arduino/blob/master/documentation/eagle/tm1637.jpg)

The user selects the countdown time (1-99 minutes) with the pot then starts with the pushbutton.
Time remaining is displayed on seven segment display. When finished the buzzer is activated and done displayed on 7-seg.A switch can be used if user wishes to switch on/off display to save battery power.

 
Copyright
---------
Copyright (C) 2018 Gavin Lyons 
see LICENSE.md in documentation section 
for more details

