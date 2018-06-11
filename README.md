
Overview
--------------------------------------------
* Name: timer_arduino
* Title : Countdown Timer, arduino based. 
* Description: Countdown Timer: 1-99 minutes. Output(mm:ss) to seven segment display(TM1637) and Buzzer.
Push button to start.  10K Pot, time select input. 
* Author: Gavin Lyons

libraries
--------------------------
* https://github.com/avishorp/TM1637
*  Version 1.1.0
*  TM1637Display.h // Tm1637 module

*  https://github.com/JChristensen/JC_Button
*  Version 2.0-1
*  JC_Button.h // push button lib

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
> 1 10 k pot
>
> one pushbutton
>
> two on/off SPST switches
>
> One buzzer
>

Features
----------------------

![ScreenShot schematic](https://github.com/gavinlyonsrepo/timer_arduino/blob/master/documentation/images/tm1637.jpg)

The user selects the time form 1-99 with minutes with the pot then starts with the pushbutton.
Time remaining is displayed on seven segment display. When finished the buzzer is activated and done displayed on 7-seg
A switch can be used if user wishes to switch on/off display to save battery power.

 
Copyright
---------
Copyright (C) 2018 Gavin Lyons 
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public license published by
the Free Software Foundation, see LICENSE.md in documentation section 
for more details

