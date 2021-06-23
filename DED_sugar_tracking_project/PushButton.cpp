/**
 * PushButton cpp implementation
 */
 // *** include PushButton header file ***
 #include "PushButton.h"
 
 // *** include Arduino header in order to use methods of pinMode(), digitalWrite() etc.
 #include "Arduino.h"
 
 PushButton::PushButton(const int buttonPin) {
     _pushButtonPin = buttonPin;
     isPushed       = false;
 }

 // *** config push button . ***
 void PushButton::pushButtonConfig() {
  // initialize the pushbutton pin as an input:
  pinMode(_pushButtonPin, INPUT);  
  
}

bool PushButton::checkPushButtonPressed() {
  
  // read the state of the pushbutton 1 value:
  pushButtonLatestState = digitalRead(_pushButtonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (HIGH  == pushButtonLatestState && LOW == pushButtonPrevState)  {
    isPushed = true;
    // *** update previous state
    pushButtonPrevState = pushButtonLatestState;
    
  } else if (LOW  == pushButtonLatestState && HIGH == pushButtonPrevState) {
    isPushed = false;
    // *** update previous state
    pushButtonPrevState = pushButtonLatestState; 
  }
   return isPushed;
}
// *** handle push button press event and return a total number of press act ***
void PushButton::pushButtonEventHanlder() {
  // read the state of the pushbutton 1 value:
  pushButtonLatestState = digitalRead(_pushButtonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (HIGH  == pushButtonLatestState && LOW == pushButtonPrevState)  {
    // increase button press counter
    _buttonPushCounter++;
    isPushed = true;
    // *** update previous state
    pushButtonPrevState = pushButtonLatestState;
    
  } else if (LOW  == pushButtonLatestState && HIGH == pushButtonPrevState) {
    isPushed = false;
    // *** update previous state
    pushButtonPrevState = pushButtonLatestState;
  } 
  // *** avoid overflow
  if (_buttonPushCounter >= 32767) {
    _buttonPushCounter = 0;
  }
}  

 void PushButton::resetCounter() {
    _buttonPushCounter = 0;
 }

 int PushButton::getButtonPushedCount() {
  return _buttonPushCounter;
 }
