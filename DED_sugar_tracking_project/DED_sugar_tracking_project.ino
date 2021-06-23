/**
 * Data Enabled Design Project (Sugar Tracking)
 * Author: T.Miao
 * Date:  June 23,  2021
 * Version: v1.0
 */
  // ***************
  // *** IMPORTs ***
  // ***************
  #include "Arduino.h"
  
  // *** import LCD I2C Interface class
  #include "Wire.h" 
  #include "LiquidCrystal_I2C.h"
  
  // *** import DFHelper class
  #include "DFHelper.h"
  
  // *** import Push Button class
  #include "PushButton.h"
  
  // *** import Slider class
  #include "Slider.h"
  
  // **********************************************************************
  // *** OOCSI can be used to send data but also check acknowledgement  ***   
  // *** when data uploaded to a OOCSI channel                          ***
  // *** IMMPORT OOCSI CLASS                                            ***
  // **********************************************************************
  #include "OOCSI.h"
  
  OOCSI oocsi = OOCSI();
  
  const char* SUGAR_TRACK_2_NOTIFY_CHANNEL  = "personal_sugar_track_notifier_channel";  // *** channel for subscribing dataset in DF IoT dataset ***
  const char* dataUploadedAckSubscriber1    = "data_sent_ack_tracker1";                 // *** SUBSCRIBER CLIENT NAME

  // *****************************
  // *** SPECIFIED PINS IN USE ***
  // *****************************
  // *** PUSHBUTTON 1 FOR SENDING DATA
  #define SEND_BUTTON_1_PIN             12
  
  // *** PUSHBUTTON 1 FOR TRACKING ITEM1 
  #define USER_BUTTON_1_PIN             14
  
  // *** PUSHBUTTON 1 FOR TRACKING ITEM2
  #define USER_BUTTON_2_PIN             25
  
  // *** PUSHBUTTON 1 FOR TRACKING ITEM3
  #define USER_BUTTON_3_PIN             26
  
  
  // *** ALERT STATUS LED #1 (WHITE LED) (ALERT LEVEL 1) *** 
  #define ALERT_STATUS_LED_1_PIN        16

  
  // *** DATA SUBMISSIOIN STATUS LED #1 (GREEN LED)*** 
  #define DATA_UPLOAD_ACK_STATE_LED_1_PIN   27 

  
  // **************************
  // *** Slider Analog Pins ***
  // **************************
  // *** Linear slider1 (LONG)
  #define SLIDER_1_ANALOG_PIN1     32   
  
  // *** Linear slider2 (SMALL)
  #define SLIDER_2_ANALOG_PIN2     35

    // *** Linear slider3 (SMALL)
  #define SLIDER_3_ANALOG_PIN3     34

      
  // *****************************
  // *** GLOBAL VARIABLES     ****
  // *****************************  
  // *** NOTE: leave the function of button1, button2, button3 
  // *** tracking three items, each can be specified by the user
  // *** In the Dataset, the item would be 
  // *** user_item1_btn1, user_item2_btn2, user_item3_btn3.
  int buttonNr1PressedCount         = 0;
  int buttonNr2PressedCount         = 0;
  int buttonNr3PressedCount         = 0;
  
  // *** (OPTIONAL) Data sending button pressed count
  // *** not necessarily mean the number of data reported
  int sendButton1PressedCount       = 0;
  
  // *** INITIALIZE TO -1 & REPORTED MAPPED SLIDER VALUE SHOULD BE >=1 ***
  int slider1MappedVal              = -1;
  int slider2MappedVal              = -1;
  int slider3MappedVal              = -1;

  int supportLevelLikeToOffer            = 0;
  int supportLevelBeenActuallyPerceived  = 0;
  int tbd_track_item                     = 0;
  
  // *** SET MINIMUM VALUE FOR GENERATING USER ALERT ABOUT TRACKED ITEM ***
  const int ALERT_MIN_THRESHOLD = 6;
  const int ALERT_MAX_THRESHOLD = 10;

  // *****************************
  // *** CLASS INITIALIZATION  ***
  // *****************************
  // *** Initialize DataFoundry Helper Object ***
  DFHelper dfHelper(
      DF_BASE_URL,        // Data Foundry server
      IOT_DS,             // DATASET type
      IOT_DATASET_1_ID,   // IoT Dataset particular ID
      IOT_DATASET_1_TOKEN // IoT Dataset particular Access Token
  );

  // *** Initialize Slider Object 1 ***
  Slider slider1(SLIDER_1_ANALOG_PIN1);
  
  // *** Initialize Slider Object 2 ***
  Slider slider2(SLIDER_2_ANALOG_PIN2);

  // *** Initialize Slider Object 3 *** 
  Slider slider3(SLIDER_3_ANALOG_PIN3);
  
  // *** Initialize PushButton Object for sending data ***
  PushButton sendBtn1(SEND_BUTTON_1_PIN);
  
  // *** Initialize PushButton Object for tracking user item1 ***
  PushButton userBtn1(USER_BUTTON_1_PIN);
  
  // *** Initialize PushButton Object for tracking user item2 ***
  PushButton userBtn2(USER_BUTTON_2_PIN);
  
  // *** Initialize PushButton Object for tracking user item3 ***
  PushButton userBtn3(USER_BUTTON_3_PIN);

  // **************************
  // *** HD44780 LCD Pins   ***
  // *** CONNECT LCD I2C SDA pin to ESP32 DEV Module GPIO 21 (Wire SDA) ***
  // *** CONNECT LCD I2C SCL pin to ESP32 DEV Module GPIO 22 (Wire SCL) ***
  // **************************
  // *** set the LCD number of columns and row"s
  // *** declare the lcd object
  // *** Note: The i2c address must match the backpack address
  // *** and the library only works with certain backpacks
  // *** IMPORTANT !!Run i2c_scanner program to check the i2cAddr when you rerun this program!!
  const uint8_t i2cAddr = 0x27;
  #define LCD_COLS 16
  #define LCD_ROWS 2
  // *** Initialize LCD I2C Object for display ***
  LiquidCrystal_I2C LCD_I2C_obj_1(i2cAddr, LCD_COLS, LCD_ROWS);

// *********************************
// *** LCD SMILEYS   ***
// *********************************
  byte happy_mood[8] = {
      B00000,
      B00000,
      B01010,
      B00000,
      B11111,
      B10001,
      B01110,
      B00000
  };
  byte good_mood[8] = {
      B00000,
      B00000,
      B01010,
      B00000,
      B10001,
      B01110,
      B00000,
      B00000
  };
   byte neutral_mood[8] = {
      B00000,
      B00000,
      B01010,
      B00000,
      B00000,
      B11111,
      B00000,
      B00000
  };
  byte bad_mood[8] = {
      B00000,
      B00000,
      B01010,
      B00000,
      B01110,
      B10001,
      B10001,
      B00000
  };
  byte heart[8] = {
      B00000,
      B01010,
      B11111,
      B11111,
      B01110,
      B00100,
      B00000,
      B00000
  };
  byte rightArrow[8] = {
      B00000,
      B00100,
      B00100,
      B00110,
      B00111,
      B00110,
      B00100,
      B00000
  };
  byte leftArrow[8] = {
      B00000,
      B00100,
      B01100,
      B11100,
      B01100,
      B00100,
      B00000,
      B00000
  };
  byte emptyHeart[8] = {
      B00000,
      B00000,
      B01010,
      B10101,
      B10001,
      B01010,
      B00100,
      B00000
    };

// *** DEFINE STRING FOR MOOD VALUES ***
 char* HAPPY_MOOD   = "happy"; 
 char* GOOD_MOOD    = "good";
 char* NEUTRAL_MOOD = "neutral";
 char* BAD_MOOD     = "sad";

 
 // *** A BOOLEAN VAR FOR CHECK STATUS BEFORE/AFTER DATA UPLOADING ***
 boolean post_message_sent_flag = false;
 
  // *************************************************************
  // *** CHARACTERS FOR DISPLAY BUTTON ITEM TAGS IN LCD SCREEN ***
  // *************************************************************
  #define BUTTON_NUM 3
  const char* btn_1_head_letter = "B1:";
  const char* btn_2_head_letter = "B2:";
  const char* btn_3_head_letter = "B3:";
  
  // *** BUTTON  TRACKING HEADERS ***
  const char* btn_head_letters[BUTTON_NUM];

  // *** BUTTON  TRACKING COUNTS ***
  int btn_counts[BUTTON_NUM];

  // *** a flag to track a LCD row has been written data or not
  boolean row0OccupiedFlag = false; // 1st row in LCD
  boolean row1OccupiedFlag = false; // 2nd row in LCD
 
// *********************************
// *** SET UP DEVICES & CONFIGS  ***
// *********************************
void setup() {
  Serial.begin(115200); // setup serial monitoring freq 9600, 115200

  // *****************************
  // *** PUSH BUTTON(s) Config ***
  // *****************************
  // *** FOR SENDING DATA PUSHBUTTON ***
  sendBtn1.pushButtonConfig();
  
  // *** FOR USER TRACKING ITEM1 PUSHBUTTON ***
  userBtn1.pushButtonConfig();

  // *** FOR USER TRACKING ITEM2 PUSHBUTTON ***
  userBtn2.pushButtonConfig();

  // *** FOR USER TRACKING ITEM3 PUSHBUTTON ***
  userBtn3.pushButtonConfig();

  // ************************
  // *** Slider(s) Config ***
  // ************************
  // *** FOR USER TRACKING ITEM OF ITEM4 SLIDER ***
  slider1.sliderConfig(SLIDER_1_MIN_RANGE, SLIDER_1_MAX_RANGE, SLIDER_1_OUTPUT_MAPPED_MIN_RANGE, SLIDER_1_OUTPUT_MAPPED_MAX_RANGE);//1~10
  
  // *** FOR USER TRACKING ITEM OF ITEM5 SLIDER ***
  slider2.sliderConfig(SLIDER_2_MIN_RANGE, SLIDER_2_MAX_RANGE, SLIDER_2_OUTPUT_MAPPED_MIN_RANGE, SLIDER_2_OUTPUT_MAPPED_MAX_RANGE); // 1~6//

  // *** FOR USER TRACKING ITEM OF ITEMx SLIDER ***
  slider3.sliderConfig(SLIDER_3_MIN_RANGE, SLIDER_3_MAX_RANGE, SLIDER_3_OUTPUT_MAPPED_MIN_RANGE, SLIDER_3_OUTPUT_MAPPED_MAX_RANGE); // 1~6//

  // *******************************
  // *** ALERT STATUS LED Config ***
  // *******************************
  pinMode(ALERT_STATUS_LED_1_PIN, OUTPUT);

  // *****************************************************
  // *** DATA SEND BUTTON#1 PRESSED STATE LED#1 Config ***
  // *****************************************************
  pinMode(DATA_UPLOAD_ACK_STATE_LED_1_PIN, OUTPUT); 
  
  // *** TURN OFF ALERT LED AT BEGINNING ***
  digitalWrite(ALERT_STATUS_LED_1_PIN, LOW);

  // *** TURN OFF DATA SUBMISSION LED AT BEGINNING ***
  digitalWrite(DATA_UPLOAD_ACK_STATE_LED_1_PIN, LOW);

  // *****************************************
  // *** LCD I2C Execution Initial Setting ***
  // *****************************************
  LCD_I2C_obj_1.init();
  LCD_I2C_obj_1.backlight();//*** enable backlight
  LCD_I2C_obj_1.noBlink();// ***NOT SURE WETHER IT NEED HERE?
  
  // *** CREATE SMILEY FACE CHARACTERS ***
  LCD_I2C_obj_1.createChar(1, happy_mood);
  LCD_I2C_obj_1.createChar(2, good_mood);
  LCD_I2C_obj_1.createChar(3, neutral_mood);
  LCD_I2C_obj_1.createChar(4, bad_mood);
  LCD_I2C_obj_1.createChar(5, heart);
  LCD_I2C_obj_1.createChar(6, rightArrow);
  LCD_I2C_obj_1.createChar(7, leftArrow);
  LCD_I2C_obj_1.createChar(8, emptyHeart);
  
  
  // *** CLEAR THE LCD SCREEN ***
  LCD_I2C_obj_1.clear();
  // ***
  LCD_I2C_obj_1.setCursor(0, 0);//1st col, 1st row
  LCD_I2C_obj_1.print("Start a daily");
  LCD_I2C_obj_1.setCursor(0, 1);//1st col, 2nd row
  LCD_I2C_obj_1.print("sugar report ");
  LCD_I2C_obj_1.write(1); // *** a smile face at end of end row

  // *** update row occupied state to true after writing above 
  // *** "Start a daily sugar report..."
  row0OccupiedFlag = true;
  row1OccupiedFlag = true;

  delay(500);

  // ***************************
  // *** Data Foundry helper ***
  // *************************** 
  // *** setup local wifi connection through ESP32
  dfHelper.wifiConnectConfig();
  
  // *** ARRAY INITIALIZATION ***
  btn_head_letters[0] = btn_1_head_letter;
  btn_head_letters[1] = btn_2_head_letter;
  btn_head_letters[2] = btn_3_head_letter; 

  // ****************************************************************************************
  // *** CONNECT OOCSI WITH A CLIENT TO CHECK ACKNOWLEDGEMENT FOR NEW DATA UPLOADED TO DF ***
  // ****************************************************************************************
  oocsi.connect(dataUploadedAckSubscriber1, "oocsi.id.tue.nl", WIFI_SSID, WIFI_PIN,  processOOCSI);

  // *** SUBSCRIBE TO OOCSI NOTIFY CHANNEL FOR CHECK ACKNOWLEDGEMENT OF NEW DATA UPLOADED ***
  oocsi.subscribe(SUGAR_TRACK_2_NOTIFY_CHANNEL);
  // ****************************************************************************************
}


 
void loop() {

  // ****************************
  // *** Slider Event Handler ***
  // ****************************
  // *** Use slider1 output for support level report ***
  // *** supportLevelLikeToOffer: 1~10
  supportLevelExpectedToOfferHandler();
    
  // ****************************
  // *** Slider Event Handler ***
  // ****************************
  // *** Use slider2 output for experienced support level report ***
  // *** supportLevelBeenActuallyPerceived: 1~10
  supportLevelBeenPerceivedHandler();

  // ****************************
  // *** Slider Event Handler ***
  // ****************************
  // *** GET MAPPED VALUE ***
  slider3MappedVal  = slider3.sliderEventHandler();
  // *** TO BE DECIDED e.g., how much effort do you perceive when offering support to others!!
  tbd_track_item = slider3MappedVal;

  // **********************************************
  // *** SENDING DATA PUSH BUTTON Event Handler ***
  // **********************************************
  // *** RUN BUTTON PRESS EVENT HANDLER ***
  sendBtn1.pushButtonEventHanlder();
  // *** RUN BUTTON #1 PRESS EVENT HANDLER ***
  sendButton1PressedCount  = sendBtn1.getButtonPushedCount();

  // ****************************************************
  // *** USER DATA TRACKING PUSH BUTTON Event Handler ***
  // ****************************************************
  buttonEventsReportHandler();

  // *********************************
  // *** LCD DISPLAY Handler ***
  // *********************************
  // *** HANDLE LCD I2C #1 DISPLAY BEFORE DATA SUBMISSION ***
  if (!post_message_sent_flag) {
    lcdI2C1DisplayHandler();
     
  } else {
    // *** RESET AFTER EACH ROUND OF DATA SUBMISSION ***
    resetAfterDataSubmit();
    //***  
  } 
   
  // *********************************
  // *** PUSH BUTTON Event Handler ***
  // *********************************
  // *** TO UPLOAD DATA into DF
  uploadSelfLoggingToDF();

  // *** CHECK OOCSI INCOMING DATA ***
  oocsi.check();
  // ***
}

// **********************************************************************
// *** CALLBACK TO ACKNOWLEGEMENT OF NEW DATA UPLOADING SUCCESS TO DF ***
// **********************************************************************
void processOOCSI() {
  Serial.println("Debug-@processOOCSI() for new message:");
  
  // *** CHECK IF THE RECIPIENT OF NOTIFIER OOCSI CHANNEL RECEIVE NEW DATA UPLOADED ***
  if (oocsi.getRecipient() == (String) SUGAR_TRACK_2_NOTIFY_CHANNEL
  
  ) {
    Serial.println("Debug-@processOOCSI(): notifier channel received data.");
    // *** LIT GREEN LED WHEN DATA UPLOADED TO DF SUCCESSFULLY ***
    digitalWrite(DATA_UPLOAD_ACK_STATE_LED_1_PIN, HIGH);
  

    // *** LCD ****************************
    // *** DISPLAY DATA SUBMISSION FEEDBACK MESSAGE AFTER DATA SUBMITTED ***
      LCD_I2C_obj_1.clear();                 // *** clear LCD screen content and ready to display new messages
      LCD_I2C_obj_1.setCursor(0, 0);         // *** display character from 1st column and 1st row
      LCD_I2C_obj_1.print("Data submitted"); // *** message displayed when data submitted successfully ***
      LCD_I2C_obj_1.print(" ");              // *** add a space right after previous characters ("Data submitted")
      LCD_I2C_obj_1.write(1);                // *** followed by a smiling face (represented by number 1(check that in setup() customized characters)) in first line
      LCD_I2C_obj_1.setCursor(0, 1);         // *** then switchh cursor to beginning of second line of LCD screen
      LCD_I2C_obj_1.print("Thank you");      // *** display "Thank you" message in second line
      LCD_I2C_obj_1.write(5);                // *** display heart icon after previous message of "Thank you"
      delay(1000);
    // ****************************************
    // *** SET FLAG TO TRUE WHEN DATA SUBMITTED ***
    post_message_sent_flag = true;
    
  }
  
}  
  
