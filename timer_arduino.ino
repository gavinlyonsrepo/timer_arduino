/*
  Name : Timer_arduino
  Title :
  Author: Gavin Lyons
  URL:
*/

//*************************** GLOBALS ********************

// Libraries
// https://github.com/avishorp/TM1637
// Version 1.1
#include <TM1637Display.h>
// https://github.com/JChristensen/JC_Button
// Version 2.0-1
#include <JC_Button.h> // push buttons


// Module connection pins (Digital Pins)
#define CLK 4
#define DIO 5
TM1637Display display(CLK, DIO);
int reset = 0;

// CONSTANTS
const int onDuration = 1000;
const int periodDuration = 6000;
const uint8_t OFF[] = {0, 0, 0, 0};
// In this library, the byte order is .GFEDCBA
const uint8_t SEG_DONE[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};

// 1000ms in 1sec, 60secs in 1min, 60mins in 1hr. So, 1000x60x60 = 3600000ms = 1hr
unsigned long timeLimit;
unsigned long lastPeriodStart;
int stop;
int start;

//buzzer
int buzzer = 8;//the pin of the active buzzer

// DEFINES
#define numberOfSeconds(_time_) ((_time_ / 1000) % 60)
#define numberOfMinutes(_time_) ((_time_ / 1000) / 60)

// Buttons
#define btn_start_pin 2
#define btn_time_pin 3
Button btn_start(btn_start_pin);
Button btn_time(btn_time_pin );
int count_start = 0;
int count_timer = 0;


//*************************** SETUP ************************
void setup() {
  // put your setup code here, to run once:

  // Setup serial
  Serial.begin(9600);
  delay(50);
  Serial.println("-----------Comms up------------");

  // buttons setup
  // Setup pins for button enable internal pull-up resistors
  digitalWrite(btn_start_pin, HIGH);
  digitalWrite(btn_time_pin, HIGH);
  btn_start.begin();
  btn_time.begin();

  //display
  display.setBrightness(0x0c);
  uint8_t data[] = { 0x0f, 0x0f, 0x0f, 0x0f };
  display.setSegments(data);
  //buzzer
  pinMode(buzzer, OUTPUT); //initialize the buzzer pin as an output
  digitalWrite(buzzer, LOW);
}

//******************* MAIN LOOP *****************
void loop() {
  // start button press
  if (btn_start.read()) {
    if (btn_start.wasPressed())
    {
      TestButton("start");
      if (count_start == 0);
        stopwatch();
      else
        countdown();
    }
  }

// *** timer button press ***
if (btn_time.read()) {
  if (btn_time.wasPressed())
  {
    count_start == 1;
    TestButton("time");
    SetTime();
  }
}
delay(5);
}

// ********************* Functions *************************
// Function to handle button press start display to OLED and serial Mon
void TestButton(String which_button)
{
  Serial.print("Count: ");
  if (which_button == "start")
  {
    Serial.println(count_start);
    count_start ++;
  }
  else if (which_button == "time")
  {
    Serial.println(count_timer);
    count_timer ++;
  }
  Serial.print("Buttonpressed: ");
  Serial.println(which_button);
}


void my_buzzer (void)
{
  unsigned char i;
  while (1)
  {
    //output an frequency
    for (i = 0; i < 80; i++)
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

void countdown() {
  // Calculate the time remaining

  unsigned long timeRemaining = timeLimit - millis();
  Serial.println("Countdown started..: ");


  Serial.println(timeRemaining);
  // To display the countdown in mm:ss format, separate the parts
  int seconds = numberOfSeconds(timeRemaining);
  int minutes = numberOfMinutes(timeRemaining);

  // This displays the seconds in the last two places
  display.showNumberDecEx(seconds, 0, true, 2, 2);
  // Display the minutes in the first two places, with colon
  display.showNumberDecEx(minutes, 0x80 >> 3, true, 2, 0);

  // Update the time remaining
  timeRemaining = timeLimit - millis();
  if (timeRemaining < 50) {
    Serial.println("BREAK!!");
    stop = 1;
    start = 0;

  }
}

void SetTime();
{
//
}

void stopwatch()
{
  int v = 1;
  while (reset == 0 &&  v <= 9999) {
    display.showNumberDec(v);
    delay(1000);
    v = v + 1;
    if (btn_start.read()) {
      if (btn_start.wasPressed()) {
        TestButton("start");
        reset = 1;
      }
    }
  }
}
//******************* EOF *****************

