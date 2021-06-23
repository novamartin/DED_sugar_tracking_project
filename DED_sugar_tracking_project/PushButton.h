/***
 * PushButton.h Header file
 */
 class PushButton {
  
  private:
    int _pushButtonPin;
    
    // button pressed counts
    int _buttonPushCounter = 0;
    
    // latest state of the button
    // reading the pushbutton status
    int pushButtonLatestState = 0;
    // storing the pushbutton previous status 
    int pushButtonPrevState = 0;
    
  public:
    // *** constructor ***
    PushButton(const int buttonPin);

    // *** methods ***
    void pushButtonConfig();

    void pushButtonEventHanlder(); 
    
    bool checkPushButtonPressed();

    void resetCounter();

    int getButtonPushedCount();

    bool isPushed;
  
 };
