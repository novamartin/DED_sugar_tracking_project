/**
 * Rotary Encoder cpp implementation
 */

 #include "RotaryEncoder.h"
 #include "Arduino.h"

 RotaryEncoder::RotaryEncoder(
      const int rotaryEncoderPinA, 
      const int rotaryEncoderPinB,
      const int LED1PinOfPinA,
      const int LED2PinOfPinB,
      bool testingEnabled
 ) {
     _rotaryEncoderPinA = rotaryEncoderPinA;
     _rotaryEncoderPinB = rotaryEncoderPinB;  
     LEDTestingEnabled  = testingEnabled;
     
     if(LEDTestingEnabled) {
        _LED1PinOfPinA     = LED1PinOfPinA;
        _LED2PinOfPinB     = LED2PinOfPinB;
     }
     
     isChanged          = false;
 }

 void RotaryEncoder::rotaryEncoderConfig() {
    // ************************************
    // *** Rotary Encoder Contact A & B *** 
    // ************************************
    pinMode(_rotaryEncoderPinA, INPUT); // set pinA as input pin
    pinMode(_rotaryEncoderPinB, INPUT); // set pinB as input pin in order to read signal from it

    resetRECounter();

    if(LEDTestingEnabled) {
        pinMode(_LED1PinOfPinA, OUTPUT); // set led1 pin as output pin (to lit led)
        pinMode(_LED2PinOfPinB, OUTPUT); // set led2 pin as output pin (to lit led) 
     }
 }

 int RotaryEncoder::rotaryEncoderEventHandler() {
    // ************************************
    // ** READ ROTARY ENCODER PIN STATE ***
    // ************************************
    // READ pinA STATE
    _rotaryEncoderPinALatestState = digitalRead(_rotaryEncoderPinA);
    // READ pinB STATE
    _rotaryEncoderPinBLatestState = digitalRead(_rotaryEncoderPinB);
  
    /** CHECK PULSE STATE CHANGE
     *  Case1: When pinA contacts with conductive segment (dark part) first  in clock wise rotation
     *  while pinB not yet contacts with conductive segment (but being close to)
     *  when BOTH pinA and pinB contact with same conductive segament, pulse counter increases with 1;
     */
    if ( (LOW  == _rotaryEncoderPinAPrevState)   && 
         (HIGH == _rotaryEncoderPinALatestState) &&
         (LOW  == _rotaryEncoderPinBLatestState)
     ) { // pinA pulse changing from LOW to HIGH && pinB in LOW
  
        // **************************
        // *** ACTIVATE COUNTER   ***
        // **************************
        if (CLOCK_WISE_ROTATION_PREF) {

          // *** update last count value
          _prevCount  = _rotaryEncoderRotateNumCount;
          
          // Alternative: update counter with decrease when clockwise rotated
          _rotaryEncoderRotateNumCount--;

          // *** update state of value change
          isChanged = true;

          

          
        } else {
          // *** update last count value
          _prevCount  = _rotaryEncoderRotateNumCount;
          
          // update counter clockwise
          _rotaryEncoderRotateNumCount++;
          
          // *** update state of value change
          isChanged = true;
        }
        // **************************
        // *** UPDATE STATE LED   ***
        // **************************
        if(LEDTestingEnabled) {
          // LIT ON & OFF LED1 (for rotatory encoder pinA) AFTER 300ms (BLINK ONCE EFFECT)
          ledBlink(_LED1PinOfPinA, 70);  
  
          // LIT ON & OFF LED2 (for rotatory encoder pinA) AFTER 300ms (BLINK ONCE EFFECT)
          ledBlink(_LED2PinOfPinB, 70);  
        }
        
  
        // *************************************
        // *** INTERNAL BUTTON EVENT HANDLER ***
        // *************************************
        //TODO
        
      
    } else if ( (LOW  == _rotaryEncoderPinAPrevState)   && 
                (HIGH == _rotaryEncoderPinALatestState) &&
                (HIGH == _rotaryEncoderPinBLatestState)
     ) { // pinA pulse changing from LOW to HIGH &&  pinB in HIGH (both pinA and pinB output HIGH)
        // **************************
        // *** ACTIVATE COUNTER   ***
        // **************************
        if (CLOCK_WISE_ROTATION_PREF) {

          // *** update last count value
          _prevCount  = _rotaryEncoderRotateNumCount;
          
          // Alternative: update counter with increase when anti-clockwise rotated
          _rotaryEncoderRotateNumCount++;

           // *** update state of value change
          isChanged = true;
          
        } else {

          // *** update last count value
          _prevCount  = _rotaryEncoderRotateNumCount;
          
          // update counter Anti-clockwise with decrease
          _rotaryEncoderRotateNumCount--;
          
           // *** update state of value change
          isChanged = true;
        }
        // **************************
        // *** UPDATE STATE LED   ***
        // **************************
        if(LEDTestingEnabled) {
            // LIT ON & OFF LED1 (for rotatory encoder pinA) AFTER 300ms (BLINK ONCE EFFECT)
            ledBlink(_LED1PinOfPinA, 10);
  
            // LIT ON & OFF LED2 (for rotatory encoder pinA) AFTER 300ms (BLINK ONCE EFFECT)
            ledBlink(_LED2PinOfPinB, 10);
        }
        
  
        // *************************************
        // *** INTERNAL BUTTON EVENT HANDLER ***
        // *************************************
        //TODO
        
    } 
 
    // update rotEncoder1PinAPrevState before next loop stars
    _rotaryEncoderPinAPrevState  = _rotaryEncoderPinALatestState;
  
     // output counter value
  //  delay(5);//OPTIONAL DELAY
  //  Serial.print(_rotaryEncoderRotateNumCount);
  //  Serial.print("/");
  
    // RESET _rotaryEncoderRotateNumCount to init value when clockwise rotation is prefered to count
    if (_rotaryEncoderRotateNumCount >= 32767) {
      _rotaryEncoderRotateNumCount = 0;
    }
  
    // *************************************
    // *** INTERNAL BUTTON EVENT HANDLER ***
    // *************************************
      //TODO
      
    return _rotaryEncoderRotateNumCount;
  
 }

 void RotaryEncoder::resetREState(bool state) {
    isChanged = state;
 }

 void RotaryEncoder::setPrevCount(int val) {
    _prevCount = val;
 }

 void RotaryEncoder::setCurrentCount(int val) {
  _rotaryEncoderRotateNumCount = val;
 }
 
 int RotaryEncoder::getPrevCount() {
    return _prevCount;
 }
 
 int RotaryEncoder::getCurrentCount() {
    return _rotaryEncoderRotateNumCount;
 }


 void RotaryEncoder::resetRECounter() {
    _rotaryEncoderRotateNumCount = 0;
 }

 void RotaryEncoder::setSemanticVal(const char* semanticVal) {
    _semanticVal = semanticVal;
 }

 const char* RotaryEncoder::getSemanticVal() {
    return _semanticVal; 
 }

 void RotaryEncoder::ledBlink(int ledPin, int delaytime) {
    digitalWrite(ledPin, HIGH);
    delay(delaytime);
    digitalWrite(ledPin, LOW);
}
