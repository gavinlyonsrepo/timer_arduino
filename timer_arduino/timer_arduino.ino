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


//*************************** GLOBALS ********************

// TM1637 Module connection pins (Digital Pins)
#define CLK 5
#define DIO 4
TM1637Display display(CLK, DIO);

//buzzer pin
int buzzer = 9;//the pin of the active buzzer

// Button
#define buttonPin 2
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin
// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
int count_start = 0;


// time calc
#define numberOfSeconds(_time_) ((_time_ / 1000) % 60)
#define numberOfMinutes(_time_) ((_time_ / 1000) / 60)
// hold time selected in ms.
unsigned long timeLimit = 0;

//pot pin Analog A0
int potPin = 0;
// Varibles to Sample and smooth the A0 input from pot to reduce gitter on display
// Define the number of samples to keep track of. The higher the number, the
const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total

//*************************** SETUP ************************
void setup() {
  // put your setup code here, to run once:

  // Setup serial
  Serial.begin(9600);
  delay(50);
  Serial.println("-----------Timer Arduino Comms up------------");

  // button setup
  // Setup pins for button enable internal pull-up resistors
  digitalWrite(buttonPin, HIGH);

  //display setup
  display.setBrightness(0x0c);
  display.showNumberDecEx(0, 0x40, true);
  //buzzer
  pinMode(buzzer, OUTPUT); //initialize the buzzer pin as an output
  digitalWrite(buzzer, LOW);

  // initialize all the readings in array to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

//******************* MAIN LOOP *****************
void loop() {
  // read the pot
  if (count_start == 0)
  {
    potRead();
  }

  // read and debounce push button.
  int reading = digitalRead(buttonPin);
  // If the switch changed?
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      // start timer if the new button state is low
      if (buttonState == LOW) {
        TestButton();
      }
    }
  }

  // save the reading.
  lastButtonState = reading;
  delay(5);
}

// ********************* FUNCTIONS *************************

// TestButton:  Function to handle button press
void TestButton()
{
  Serial.print("Count: ");
  Serial.println(count_start);
  count_start ++;
  if (count_start == 1)
  {
    countdown();
    my_buzzer();
  }
}

// potRead: Function to read analog pin connected to pot and display it in 7-seg
// includes smoothing the analog sample by taking avergae of 10 readings
void potRead()
{
  unsigned long average = 0;
  // subtract the last reading:
  total = total - readings[readIndex];
  readings[readIndex] = map(analogRead(potPin), 0, 1023, 1, 99);
  // increment total and array
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  // check for end of array, wrap to start if yes
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;
  Serial.println(average);
  timeLimit = ((average * 60) * 1000);
  average = average * 100 ;
  display.showNumberDecEx(average, 0x40, true);
  delay(100);
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

