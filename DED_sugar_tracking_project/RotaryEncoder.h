/***
 * Rotary Encoder header file
 */

 extern bool CLOCK_WISE_ROTATION_PREF;
 
 class RotaryEncoder {
  
    private:
      int _rotaryEncoderPinA;
      int _rotaryEncoderPinB;
      int _LED1PinOfPinA;
      int _LED2PinOfPinB;
      
      int _rotaryEncoderRotateNumCount   = 0; // user rotation counts ()
      int _rotaryEncoderPinAPrevState    = 0; // previous state of pinA
      int _rotaryEncoderPinALatestState  = 0; // latest state of pinA
      
      int _rotaryEncoderPinBPrevState    = 0; // previous state of pinB
      int _rotaryEncoderPinBLatestState  = 0; // latest state of pinB

      int _prevCount = 0;

      bool LEDTestingEnabled;

      const char* _semanticVal;

      void ledBlink(int ledPin, int delaytime);

    public:
      RotaryEncoder(
          const int rotaryEncoderPinA, 
          const int rotaryEncoderPinB,
          const int LED1PinOfPinA, 
          const int LED2PinOfPinB,
          bool testingEnabled
      );

      void rotaryEncoderConfig();

      int rotaryEncoderEventHandler();

      void resetREState(bool state);

      void setPrevCount(int val);

      void setCurrentCount(int val);

      int getPrevCount();

      int getCurrentCount();

      void resetRECounter();

      bool isChanged;

      void setSemanticVal(const char* semanticVal);

      const char* getSemanticVal();
  
 };
