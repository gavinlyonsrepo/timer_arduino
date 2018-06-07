/*
  Name : Timer_arduino
  Title : 
  Author: Gavin Lyons
  URL: 
*/

//*************************** GLOBALS ********************

// Libraries
//https://github.com/avishorp/TM1637
// 
// https://github.com/madleech/Button
#include <Button.h> // push buttons

//buzzer
int buzzer = 8;//the pin of the active buzzer

// Buttons
#define btn_start_pin 13
#define btn_time_pin 12
Button btn_start(btn_start_pin);
Button btn_time(btn_time_pin );


// RGB
const int redPin = 11;  // R petal on RGB LED module connected to digital pin 11
const int greenPin = 10;  // G petal on RGB LED module connected to digital pin 9
const int bluePin = 9;  // B petal on RGB LED module connected to digital pin 10



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

  //rgb setup
  pinMode(redPin, OUTPUT); // sets the redPin to be an output
  pinMode(greenPin, OUTPUT); // sets the greenPin to be an output
  pinMode(bluePin, OUTPUT); // sets the bluePin to be an output

  //buzzer
  pinMode(buzzer, OUTPUT); //initialize the buzzer pin as an output
  digitalWrite(buzzer, LOW);
}

//******************* MAIN LOOP *****************
void loop() {
  // put your main code here, to run repeatedly:
  
  

  if (btn_start.pressed()) {
    TestButton(1);
    // my_buzzer();
  }
  // *** TEST 2 ***
  if (btn_time.pressed()) {
    TestButton(2);
  }

  color(0, 0, 50); // turn the RGB LED blue
}

// ********************* Functions *************************
// Function to handle button press start display to OLED and serial Mon
void TestButton(int which_button)
{
  count ++;
  Serial.print("Count: ");
  Serial.println(count);
  Serial.print("Buttonpressed: ");
  Serial.println(which_button);
}

void color (unsigned char red, unsigned char green, unsigned char blue)     // the color generating function
{
  analogWrite(redPin, red);
  analogWrite(bluePin, blue);
  analogWrite(greenPin, green);
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
//******************* EOF *****************

