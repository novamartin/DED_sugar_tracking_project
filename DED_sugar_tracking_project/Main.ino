/***
 * Methods 
 * 
 */
  // *** Use slider 1 to report support level that the participant expect to give the other!
  void supportLevelExpectedToOfferHandler() {

      // *** GET MAPPED VALUE ***
      slider1MappedVal  = slider1.sliderEventHandler();
      
      // *** Update support level the participant likes to offer ***
      supportLevelLikeToOffer = slider1MappedVal;
  }

  // *** Use slider 3 to report support level that the participant experienced how much support he/she gave in practice!
  void supportLevelBeenPerceivedHandler() {
    // *** GET MAPPED VALUE ***
    slider2MappedVal  = slider2.sliderEventHandler();

    // *** Update support level that the participant actually offered to and was perceived by others ***
    supportLevelBeenActuallyPerceived = slider2MappedVal;
  }
  
  // *** HANDLE BUTTON CLICK REPORT FROM THREE PUSH BUTTONS ***
  void buttonEventsReportHandler() {

      // *** RUN BUTTON #1 PRESS EVENT HANDLER ***
      userBtn1.pushButtonEventHanlder();
      buttonNr1PressedCount  = userBtn1.getButtonPushedCount();
    
      // *** RUN BUTTON #2 PRESS EVENT HANDLER ***
      userBtn2.pushButtonEventHanlder();
      buttonNr2PressedCount = userBtn2.getButtonPushedCount();

      // *** RUN BUTTON #3 PRESS EVENT HANDLER ***
      userBtn3.pushButtonEventHanlder();
      buttonNr3PressedCount = userBtn3.getButtonPushedCount();

     // *** SUM ALL COUNTS AND GENERATE ALERT LEVEL BASED ON THE TOTAL COUNTS ***
     int totalCounter = userBtn1.getButtonPushedCount() + 
                     userBtn2.getButtonPushedCount() +
                     userBtn3.getButtonPushedCount();
 
      // *** ALERT LEVEL 1 HANDLER ***
      if (totalCounter >= ALERT_MIN_THRESHOLD && 
          totalCounter <= ALERT_MAX_THRESHOLD
      ) {
         // *** TURN ON ALERT LED #1 
         digitalWrite(ALERT_STATUS_LED_1_PIN, HIGH); // TURN ON WHITE LED
         
      } else if (totalCounter > ALERT_MAX_THRESHOLD) {// *** ALERT LEVEL 2 HANDLER ***
         // *** TURN OFF ALERT LED #1 & #3
         digitalWrite(ALERT_STATUS_LED_1_PIN, HIGH);
         delay(300);
         digitalWrite(ALERT_STATUS_LED_1_PIN, LOW);
      }
      // ***
  }

  // *** HANDLE LCD I2C #1 DISPLAY BEFORE DATA SUBMISSION ***
  void lcdI2C1DisplayHandler() {

    // *** WAKE UP LCD WITH BACKLIGHT FOR NEW ROUND OF DATA REPORTING WHEN ANY BUTTON CLICKED *** 
    if (buttonNr1PressedCount > 0 ||
        buttonNr2PressedCount > 0 ||
        buttonNr3PressedCount > 0 ||
        sendButton1PressedCount > 0
    ) {
      // *** Lit backlight of LCD if any button input detected ***
      LCD_I2C_obj_1.backlight();
    }
  
    // *****************************************************************
    // *** ALTERNATIVE TO DISPLAY INFO AT FIRST ROW OF LCD SCREEN #1 ***
    // *****************************************************************
    btn_counts[0] = userBtn1.getButtonPushedCount();
    btn_counts[1] = userBtn2.getButtonPushedCount();
    btn_counts[2] = userBtn3.getButtonPushedCount();
  
    // *************************************************
    // *** LOOP TO DISPLAY BUTTON REPORT DATA TO LCD ***
    // *** B1: 0 B2: 0 B3: 0                         ***
    // ************************************************* 
    // *** INIT COLUMN START INDEX ***
    int colStartIndex = 0;

    if (row0OccupiedFlag) {
      clearLCDByRowIndex(0, LCD_ROWS, LCD_COLS);// int rowIndex, int totalRowNum, int totalColumnNum
      // *** Reset row1 occupied state to false again
      row0OccupiedFlag = false;
    }
    
    // *** LOOPING TO DISPLAY (B1: 0 B2: 0 B3: 0 ) ***
    for (int i = 0; i < BUTTON_NUM; i++) {
      LCD_I2C_obj_1.setCursor(colStartIndex, 0);// first column, first row
      LCD_I2C_obj_1.print(btn_head_letters[i]);
        
      colStartIndex +=  strlen(btn_head_letters[i]);
      
      LCD_I2C_obj_1.setCursor(colStartIndex, 0);// *** x column, first row
      LCD_I2C_obj_1.print(btn_counts[i]);
      LCD_I2C_obj_1.print(" ");
      colStartIndex += 2;
    }
    // *** FOR REMAINING COLUMNS AFTER DISPLAY (B1: 0 B2: 0 B3: 0 ) IN FIRST ROW, SET " " TO ALL OF THEM ***
    String idle_column_char = " ";
      for (int i=colStartIndex; i < LCD_COLS; i++) {
         idle_column_char += " ";
      }  
    LCD_I2C_obj_1.setCursor(colStartIndex, 0);// *** SET CURRENT INDEX TO 2 AFTER PREVIOUS BUTTON REPORT VALUE ***
    LCD_I2C_obj_1.print(idle_column_char); // *** SET EMPTY CHARACTER
    
    // ***********************************************************
    // *** FIRST ROW IN LCD SCREEN: "support level: 0"        ***
    // *** ATTENTION LEVEL TO HEALTH MANAGEMENT               ***
    // *** DISPLAY CONCERN LEVEL AT RIGHT END SIDE OF 2nd ROW ***
    // **********************************************************
    int colStartIndexRow2 = 0;

    // *** Before display new data to row#2, clear all previous caches written to LCD row2!!
    int rowIndexToClear = 1; // indicate second row
    if (row1OccupiedFlag) {
      clearLCDByRowIndex(1, LCD_ROWS, LCD_COLS);// int rowIndex, int totalRowNum, int totalColumnNum
      // *** Reset row1 occupied state to false again
      row1OccupiedFlag = false;
    }
    // ****************************************
    // *** DISPLAY supportLevelLikeToOffer ****
    // ****************************************
    LCD_I2C_obj_1.setCursor(colStartIndexRow2, 1); // start from beginning of column in row 2
    LCD_I2C_obj_1.write(5);// display heart (concern) emoji
    LCD_I2C_obj_1.write(6); // display "=>" icon
    LCD_I2C_obj_1.print(":");// insert ":" after emoji

    // *** then display colStartIndexRow2 value (interger) (1~9)//slider1MappedVal
    LCD_I2C_obj_1.print(supportLevelLikeToOffer);

    // **************************************************
    // *** DISPLAY supportLevelBeenActuallyPerceived ****
    // **************************************************
    // *** Update column start index at row 2 after display supportLevelLikeToOffer ***
    colStartIndexRow2 = 5; // 5 characters have been occupied by heart_icon & ":" & value & space
    LCD_I2C_obj_1.setCursor(colStartIndexRow2, 1); // start from beginning of column in row 2
    LCD_I2C_obj_1.write(5);// display heart (concern) emoji
    LCD_I2C_obj_1.write(7); // display "<=" icon
    LCD_I2C_obj_1.print(":");// insert ":" after emoji

    // *** then display colStartIndexRow2 value (interger) (1~9)//slider1MappedVal
    LCD_I2C_obj_1.print(supportLevelBeenActuallyPerceived);

    // **************************************************
    // *** DISPLAY ITEM T.B.D ****
    // **************************************************
    // *** Update column start index at row 2 after display supportLevelLikeToOffer ***
    colStartIndexRow2 = 10; // 5 characters have been occupied by heart_icon & ":" & value & space
    LCD_I2C_obj_1.setCursor(colStartIndexRow2, 1); // start from beginning of column in row 2
    LCD_I2C_obj_1.write(8);// display empty heart emoji
    LCD_I2C_obj_1.print(":");// insert ":" after emoji
    LCD_I2C_obj_1.print(tbd_track_item);
  }
  // *** Clear particular row ***
  void clearLCDByRowIndex(int rowIndex, int totalRowNum, int totalColumnNum) {
    if (rowIndex < totalRowNum) {
      for (int j = 0; j < totalColumnNum; j++) {
        LCD_I2C_obj_1.setCursor(j, rowIndex);//0, 1//1,1
        LCD_I2C_obj_1.print(" ");
      }
    }
  }

  // ************************************
  // *** DATA UPLOADING Event Handler ***
  // ************************************
  void uploadSelfLoggingToDF() {  
    
    // *** IF SENDING BUTTON PRESSED, UPLOAD DATA TO DF ***
    // *** IF SUBMIT BUTTON PRESSED AND IF AT LEAST ONE BUTTON REPORT ITEM REPORTED AND 
    // *** IF MOOD DATA REPORTED AND IF ATTENTION LEVEL REPORTED, SENDING DATA TO DF...
    // *** ANY OTHER CONDITIONS? SUCH AS TIMER OR VALUE CHECK??
    // *** 
    if (sendBtn1.checkPushButtonPressed() &&
        (buttonNr1PressedCount > 0       ||
         buttonNr2PressedCount > 0       ||
         buttonNr3PressedCount > 0)      &&        
        supportLevelLikeToOffer          != -1   &&
        supportLevelBeenActuallyPerceived    != -1   &&
        tbd_track_item                   != -1
    ) {
      
      // *** Execute DF data uploading ***
      dfHelper.uploadIoTSelfReportOfSugar(
          SUGAR_TRACKER_DEVICE_ID,
          LOGGING_ACT, 
          buttonNr1PressedCount, // user_item1(btn1)      
          buttonNr2PressedCount, // user_item2(btn2)
          buttonNr3PressedCount, // user_item3(btn3)
          supportLevelLikeToOffer,   
          supportLevelBeenActuallyPerceived,
          tbd_track_item      
      );
  
      delay(200);
  
    }  
    // *** IN CASE OF SUBMIT BUTTON CLICKED BUT NO PUSH BUTTON ITEM REPORTED
    // *** THEN WARNING MESSAGE WILL BE DISPLAYED IN LCD SCREEN ***
    else if (  
        sendBtn1.checkPushButtonPressed() &&
        (0 == buttonNr1PressedCount       ||
         0 == buttonNr2PressedCount       ||
         0 == buttonNr3PressedCount
        )       
      ) {
      // *** TURN ON LCD BACKLIGHT ***  
      LCD_I2C_obj_1.backlight();
      // *** DISPLAY DATA SUBMISSION FEEDBACK MESSAGE AFTER DATA SUBMITTED ***
      LCD_I2C_obj_1.clear();                 // *** clear LCD screen content and ready to display new messages
      LCD_I2C_obj_1.setCursor(0, 0);         // *** display character from 1st column and 1st row
      LCD_I2C_obj_1.print("No button item"); // *** message displayed when user not reports any button clicking item data ***
      
      LCD_I2C_obj_1.setCursor(0, 1);         // *** then switchh cursor to beginning of second line of LCD screen
      LCD_I2C_obj_1.print("reported ");      // *** continue display messages following end of 1st row
      LCD_I2C_obj_1.write(4);                // *** followed by a saf face (represented by number 4(check that in setup() customized characters)) in 2nd line
      delay(1500);

      // *** Clear up the data written to the LCD ***
      LCD_I2C_obj_1.clear();
      // ***
      // *** TURN OFF LCD BACKLIGHT ***
      LCD_I2C_obj_1.noBacklight();
    }
  }

  // **********************************************************
  // *** APPLY SETTINGS AFTER EACH ROUND OF DATA SUBMISSION ***
  // **********************************************************
  void resetAfterDataSubmit() {

      // *** RESET USER BUTTON CLICK COUNTS ***
      userBtn1.resetCounter();
      userBtn2.resetCounter();
      userBtn3.resetCounter();

      // *** RESET DATA SENDING BUTTON PRESSED COUNTS ***
      sendBtn1.resetCounter();
      
      // *** RESET ALERT LED #1  && ACK LED TO OFF STATE ***
      digitalWrite(ALERT_STATUS_LED_1_PIN, LOW);
      digitalWrite(DATA_UPLOAD_ACK_STATE_LED_1_PIN, LOW);

      // *** RESET FLAG TO STATE OF BEFORE DATA UPLOADING ***
      post_message_sent_flag = false;

      // *** RESET REPROTED PARAMETERS AFTER EACH ROUND SUBMISSION ***
      slider1MappedVal = -1;
      slider2MappedVal = -1;
      slider3MappedVal = -1;
      
      // *** DISPLAY MESSAGE BEFORE TURNING OFF LCD SCREEN FOR 'sleep' mode ***
      // *** NOTE: this is not really the sleep mode. we just turn off the LCD screen to give user impression of LCD 'sleeps'!!
      // *** ONLY WHEN USER clicks button for next round reporting, the LCD screen wil turn on again!!
      LCD_I2C_obj_1.clear();              // *** clear LCD screen with existing characters
      LCD_I2C_obj_1.setCursor(0, 0);      // *** ready to display character from 1st column in 1st row
      LCD_I2C_obj_1.print("Enter sleep"); // *** message displayed at first row when data submitted successfully ***
      LCD_I2C_obj_1.setCursor(0, 1);      // *** ready to display character from 1st column in 2nd row
      LCD_I2C_obj_1.print("mode in 2 sec...");// *** message displayed at 2nd row of 1st column ***
      
      delay(2000);

      // *** Clear up the data written to the LCD ***
      LCD_I2C_obj_1.clear();
      

      // *** TURN OFF BACK LIGHT OF LCD FOR FAKE SLEEP MODE OF LCD ***
      // *** THE  TRUE SLEEP MODE OF LCD IN ESP32 DEV MODULE DID NOT WORK (NO CONTENT SHOW IT WHEN CONNECT TO A PIN THAT SET TO OUTPUT PIN)
      // *** DONT KNOW WHY MAY BE DUE TO LOWER VOLTAGE FROM THAT PIN?
      LCD_I2C_obj_1.noBacklight();
    
  }
