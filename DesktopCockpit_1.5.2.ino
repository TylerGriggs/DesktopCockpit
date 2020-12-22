#include <Joystick.h>

// Toggle Switch Setup
#define NUM_SWITCHES 5
#define pinToggle4 2
#define pinToggle0 3
#define pinToggle1 4
#define pinToggle2 5
#define pinToggle3 6
// Rotary Switch Setup
#define pinRotaryButton 7
#define DT              8
#define CLK             9


#define pinLED1    19

Joystick_ Joystick;

int stateToggle0;
int stateToggle1;
int stateToggle2;
int stateToggle3;
int stateToggle4;
int lastStateToggle0;
int lastStateToggle1;
int lastStateToggle2;
int lastStateToggle3;
int lastStateToggle4;
// Rotary Encoder
int stateRotaryButton;
int stateCLK;
int lastStateRotaryButton;
int lastStateCLK;

void setup() {
  // Initialize Button Pins
  pinMode(pinToggle0, INPUT); //set the button pin as INPUT
  pinMode(pinToggle1, INPUT); //set the button pin as INPUT
  pinMode(pinToggle2, INPUT); //set the button pin as INPUT
  pinMode(pinToggle3, INPUT); //set the button pin as INPUT
  pinMode(pinToggle4, INPUT); //set the button pin as INPUT
  
  pinMode(pinRotaryButton, INPUT_PULLUP); //set the button pin as INPUT
  pinMode(CLK,INPUT);  // Set encoder pins as inputs
  pinMode(DT,INPUT);
  
  pinMode(pinLED1, OUTPUT);

  // Remember last Toggle states
  lastStateToggle0 = digitalRead(pinToggle0);
  lastStateToggle1 = digitalRead(pinToggle1);
  lastStateToggle2 = digitalRead(pinToggle2);
  lastStateToggle3 = digitalRead(pinToggle3);
  lastStateToggle4 = digitalRead(pinToggle4);
  lastStateRotaryButton = digitalRead(pinRotaryButton);
  lastStateCLK     = digitalRead(CLK);

  // Initialize Joystick Library
  Joystick.begin();
}

void loop() {
  
  // Toggle Switch Logic ///////////////////////////////////
  stateToggle0 = digitalRead(pinToggle0); //read the state of Toggle Switch 1
  if(stateToggle0 != lastStateToggle0) { //if switch is toggled
     Joystick.setButton(0, stateToggle0);
  }
  stateToggle1 = digitalRead(pinToggle1); //read the state of Toggle Switch 1
  if(stateToggle1 != lastStateToggle1) { //if switch is toggled
     Joystick.setButton(1, stateToggle1);
  }
  stateToggle2 = digitalRead(pinToggle2); //read the state of Toggle Switch 1
  if(stateToggle2 != lastStateToggle2) { //if switch is toggled
     Joystick.setButton(2, stateToggle2);
  }
  stateToggle3 = digitalRead(pinToggle3); //read the state of Toggle Switch 1
  if(stateToggle3 != lastStateToggle3) { //if switch is toggled
     Joystick.setButton(3, stateToggle3);
  }

  
  // Autopilot ToggleSwitch On/Off with LED Indicator
  // MFS2020 Requires seperate buttons for Autopilot On/Off in Controls 
  stateToggle4 = digitalRead(pinToggle4);
  if(stateToggle4 != lastStateToggle4) { //if switch has been changed
    if(stateToggle4 == HIGH) {
      digitalWrite(pinLED1, HIGH);
      Joystick.pressButton(5);
      delay(50);
      Joystick.releaseButton(5);
      } 
    else {
      digitalWrite(pinLED1, LOW);
      Joystick.pressButton(4);
      delay(50);
      Joystick.releaseButton(4);
      }
  }


  // Rotary Encoder Logic /////////////////////////////
  stateRotaryButton = digitalRead(pinRotaryButton); 
  if(stateRotaryButton != lastStateRotaryButton) { // Rotary Button is pressed
     Joystick.setButton(8, stateRotaryButton);
  }
  stateCLK = digitalRead(CLK);
  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (stateCLK != lastStateCLK  && stateCLK == 1){
    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(DT) != stateCLK) {
      // Positive
      Joystick.pressButton(7);
      delay(25);
      Joystick.releaseButton(7);
    } else {
      // Negative
      Joystick.pressButton(6);
      delay(25);
      Joystick.releaseButton(6);
    }
  }
  
  // Remember Last States /////////////////////////////
  lastStateToggle0 = stateToggle0;
  lastStateToggle1 = stateToggle1;
  lastStateToggle2 = stateToggle2;
  lastStateToggle3 = stateToggle3;
  lastStateToggle4 = stateToggle4;
  lastStateRotaryButton = stateRotaryButton;
  lastStateCLK     = stateCLK;

  delay(10);
}
