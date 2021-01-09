/*
Author: Tyler Griggs
Board: Arduino Pro Micro (Leonardo)
Designed for use with Microsoft Flight Simulator (MFS) 2020
*/
#include <Joystick.h>

// Toggle Switches
#define pinToggle4 2
#define pinToggle0 3
#define pinToggle1 4
#define pinToggle2 5
#define pinToggle3 6
// Rotary Encoder
#define pinRotaryButton 7
#define DT              8
#define CLK             9
// LED
#define pinLED1    19

// Initialize Joystick Object from Library
Joystick_ Joystick;

// Current and Previous States for each Toggle Switch
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

// Current and Previous States for Rotary Encoder
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
  // Initialize Rotary Encoders
  pinMode(pinRotaryButton, INPUT_PULLUP); //set the button pin as INPUT
  pinMode(CLK,INPUT);  // Set encoder pins as inputs
  pinMode(DT,INPUT);
  // Initialize LEDs
  pinMode(pinLED1, OUTPUT);

  // Record Current States
  lastStateToggle0 = digitalRead(pinToggle0);
  lastStateToggle1 = digitalRead(pinToggle1);
  lastStateToggle2 = digitalRead(pinToggle2);
  lastStateToggle3 = digitalRead(pinToggle3);
  lastStateToggle4 = digitalRead(pinToggle4);
  lastStateRotaryButton = digitalRead(pinRotaryButton);
  lastStateCLK     = digitalRead(CLK);

  // Start the Joystick (Gamepad) Object
  Joystick.begin();
}

void loop() {
  
  // Toggle Switch Logic, essentially holds down the button according to the switch position
  stateToggle0 = digitalRead(pinToggle0); //read the state of pin
  if(stateToggle0 != lastStateToggle0) { //if switch is toggled
     Joystick.setButton(0, stateToggle0); // Gamepad Button 1
  }
  stateToggle1 = digitalRead(pinToggle1);
  if(stateToggle1 != lastStateToggle1) { 
     Joystick.setButton(1, stateToggle1); // Gamepad Button 2
  }
  stateToggle2 = digitalRead(pinToggle2); 
  if(stateToggle2 != lastStateToggle2) { 
     Joystick.setButton(2, stateToggle2); // Gamepad Button 3
  }
  stateToggle3 = digitalRead(pinToggle3); 
  if(stateToggle3 != lastStateToggle3) { 
     Joystick.setButton(3, stateToggle3); // Gamepad Button 4
  }

  
  // Autopilot On/Off with LED Indicator
  // MFS2020 Requires seperate buttons for Autopilot On/Off in Controls 
  stateToggle4 = digitalRead(pinToggle4);
  if(stateToggle4 != lastStateToggle4) { //if switch has been changed
    if(stateToggle4 == HIGH) {      // Toggle is UP
      digitalWrite(pinLED1, HIGH);  // Turn on LED
      Joystick.pressButton(5);      // Gamepad Button 6
      delay(50);                    // Keep the "button" held for brief period
      Joystick.releaseButton(5);
      } 
    else {                      // Toggle is DOWN
      digitalWrite(pinLED1, LOW); // Turn off LED
      Joystick.pressButton(4); // Gamepad Button 5
      delay(50);
      Joystick.releaseButton(4);
      }
  }


  // Rotary Encoder Logic 
  stateRotaryButton = digitalRead(pinRotaryButton); 
  if(stateRotaryButton != lastStateRotaryButton) { // Rotary Button is pressed
     Joystick.setButton(8, stateRotaryButton); // Gamepad Button 9
  }
  stateCLK = digitalRead(CLK);
  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (stateCLK != lastStateCLK  && stateCLK == 1){
    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(DT) != stateCLK) {
      // Positive
      Joystick.pressButton(7); // Gamepad Button 8
      delay(15);
      Joystick.releaseButton(7);
    } else {
      // Negative
      Joystick.pressButton(6); // Gamepad Button 7
      delay(15);
      Joystick.releaseButton(6);
    }
  }
  
  // Remember Last States for next loop
  lastStateToggle0 = stateToggle0;
  lastStateToggle1 = stateToggle1;
  lastStateToggle2 = stateToggle2;
  lastStateToggle3 = stateToggle3;
  lastStateToggle4 = stateToggle4;
  lastStateRotaryButton = stateRotaryButton;
  lastStateCLK     = stateCLK;

  delay(5);
}
