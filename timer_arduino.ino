//******************* HEADER ***********************************
/*
  Name : Timer_arduino
  Desc: Countdown Timer, arduino based.
  Title : Countdown Timer: 1-99 minutes. Output(mm:ss) to seven segment display(TM1637) and Buzzer. 
  Push button start.  10K  Pot time select input. 
  Author: Gavin Lyons
  URL:https://github.com/gavinlyonsrepo/timer_arduino
*/

//*************************** LIBRARIES ********************

// https://github.com/avishorp/TM1637
// Version 1.1.0
#include <TM1637Display.h> // Tm1637 module

// https://github.com/JChristensen/JC_Button
// Version 2.0-1
#include <JC_Button.h> // push button lib

//*************************** GLOBALS ********************

// TM1637 Module connection pins (Digital Pins)
#define CLK 5
#define DIO 4
TM1637Display display(CLK, DIO);

//buzzer pin
int buzzer = 9;//the pin of the active buzzer

// Button
#define btn_start_pin 2
Button btn_start(btn_start_pin);
int count_start = 0;

//pot pin Analog A0
int potPin = 0;

// time calc
#define numberOfSeconds(_time_) ((_time_ / 1000) % 60)
#define numberOfMinutes(_time_) ((_time_ / 1000) / 60)
// hold time selected in ms.
unsigned long timeLimit = 0;


//*************************** SETUP ************************
void setup() {
  // put your setup code here, to run once:

  // Setup serial
  Serial.begin(9600);
  delay(50);
  Serial.println("-----------Timer Arduino Comms up------------");

  // button setup
  // Setup pins for button enable internal pull-up resistors
  digitalWrite(btn_start_pin, HIGH);
  btn_start.begin();

  //display setup
  display.setBrightness(0x0c);
  display.showNumberDecEx(0, 0x40, true);
  //buzzer
  pinMode(buzzer, OUTPUT); //initialize the buzzer pin as an output
  digitalWrite(buzzer, LOW);
}

//******************* MAIN LOOP *****************
void loop() {
  if (count_start == 0)
  {
    potRead();
  }

  // start button press
  if (btn_start.read()) {
    if (btn_start.wasPressed())
    {
      TestButton();
    }
  }
  delay(5);
}

// ********************* FUNCTIONS *************************

// TestButton:  Function to handle button press 
void TestButton()
{
  Serial.print("Count: ");
  Serial.println(count_start);
  count_start ++;
  if (count_start ++ == 1)
  {
    countdown();
    my_buzzer();
  }
}

// potRead: Function to read analog pin connected to pot and display it in 7-seg
void potRead()
{
    unsigned long val = 0;
    val = map(analogRead(potPin), 0, 1023, 1, 99);
    Serial.println(val);
    timeLimit = ((val * 60) * 1000);
    val = val * 100 ;
    display.showNumberDecEx(val, 0x40, true);
    delay(500);
}

//my_buzzer: function to switch on buzzer and display "done" on 7-seg
void my_buzzer (void)
{
  unsigned char i;
  unsigned char j;
  
 const uint8_t SEG_DONE[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
  };
  display.setSegments(SEG_DONE);
  // run for 250*1400ms = 3.5 minutes
  for (j = 0; j < 250; j++)
  {   
     Serial.println(j);
    //output an frequency
    for (i = 0; i < 100; i++)
    {   
      digitalWrite(buzzer, HIGH);
      delay(1);//wait for 1ms
      digitalWrite(buzzer, LOW);
      delay(1);//wait for 1ms
    }
    //output another frequency
    for (i = 0; i < 100; i++)
    {
      digitalWrite(buzzer, HIGH);
      delay(2);//wait for 2ms
      digitalWrite(buzzer, LOW);
      delay(2);//wait for 2ms
    }
  } 
}

// countdown: function to handle and display the countdown time
void countdown() {
  // Calculate the time remaining
  unsigned long  runTime = 0;
  Serial.println(timeLimit);
  runTime = millis();
  unsigned long timeRemaining = timeLimit - (millis() - runTime);
  Serial.println("Countdown started..: ");
  Serial.println(timeRemaining);
  while (timeRemaining > 50 )
  {
    // To display the countdown in mm:ss format, separate the parts
    int seconds = numberOfSeconds(timeRemaining);
    int minutes = numberOfMinutes(timeRemaining);
    Serial.println(timeRemaining);
    // This displays the seconds in the last two places
    display.showNumberDecEx(seconds, 0, true, 2, 2);
    // Display the minutes in the first two places, with colon
    display.showNumberDecEx(minutes, 0x80 >> 3, true, 2, 0);

    // Update the time remaining
    timeRemaining = timeLimit - (millis() - runTime);
  }
  Serial.println("Countdown Finshed..: ");
}

//******************* EOF *****************

