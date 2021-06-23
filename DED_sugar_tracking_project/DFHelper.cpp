 
#include "DFDataset.h"
#include "DFHelper.h"

// *** Data Foundry Helper Class **
 DFHelper::DFHelper (
  const char* dataFoundryURL, 
  const char* datasetType, 
  int  datasetID, 
  const char* datasetToken 
 ) {
      
      datasetType  = datasetType;
      datasetID    = datasetID;
      datasetToken = datasetToken;
      // *** Initialize a Data Foundry connection to a specific dataset
       
      if (IOT_DS == datasetType) {
        iotDS = new DFDataset(dataFoundryURL, datasetID, datasetToken);
        
      } else if (ENTITY_DS == datasetType) {
        entityDS = new DFDataset(dataFoundryURL, datasetID, datasetToken);
      }
      
  }
  // ***************
  // *** METHODS ***
  // ***************
  // *** Config WiFi network
  void DFHelper::wifiConnectConfig() {
    // *** connect to local wifi network with credential ***
    WiFi.begin(WIFI_SSID, WIFI_PIN);
//    Serial.println("\nDebug Connecting to local wifi network..."); //optional
    // *** check wifi connection status ***
    while(WiFi.status() != WL_CONNECTED) {
      delay(100);
//      Serial.print('.');
    }
//    Serial.println("\nDebug Local wifi connected!!"); //optional
    
  }
  
  const char* DFHelper::getDFDatasetType() {
    return datasetType;
  }

  int DFHelper::getDFDatasetID() {
    return datasetID;
  }

  DFDataset* DFHelper::getIoTDataset() {
      return iotDS; 
  }

  DFDataset* DFHelper::getEntityDataset() {
      return entityDS; 
  }
  // **********************
  // *** IOT DATASET OP ***
  // **********************
  void DFHelper::uploadIoTSelfReportOfSugar(
        const char* deviceID, 
        const char* activityType, 
        int btn1CountVal,
        int btn2CountVal,
        int btn3CountVal,
        int slider1MappedVal,
        int slider2MappedVal,
        int slider3MappedVal
    ) {
       // *** meta ***
      iotDS->device(deviceID);
      iotDS->activity(activityType);
      // *** fill integer data before uploading
      iotDS->addInt("user_item1(btn1)",                       btn1CountVal);
      iotDS->addInt("user_item2(btn2)",                       btn2CountVal);
      iotDS->addInt("user_item3(btn3)",                       btn3CountVal);
      iotDS->addInt("support_level_like_to_offer",            slider1MappedVal);
      iotDS->addInt("support_level_been_rated_in_perceive",   slider2MappedVal);
      iotDS->addInt("TBD_tracked_item",                       slider3MappedVal);

      // *** fill string data before uploading
      iotDS->addString("user_id", USER_ID);//testing

      // *** uploading added data ***
      iotDS->logItem();

    }
  // *** Upload Integer Data to DataFoundry IoT Dataset
  void DFHelper::uploadIoTDataOfInteger(
      const char* deviceID, 
      const char* activityType, 
      const char* dataTag, 
      int dataVal
   ) {
      // *** meta ***
      iotDS->device(deviceID);
      iotDS->activity(activityType);
      // *** fill integer data before uploading
      iotDS->addInt(dataTag, dataVal);
      // *** fill integer data before uploading
      iotDS->addString("user_id", USER_ID);//testing

      // *** uploading added data ***
      iotDS->logItem();
//      delay(3000);
  }
  // *** Upload String Data to DataFoundry IoT Dataset
  void DFHelper::uploadIoTDataOfString(
      const char* deviceID, 
      const char* activityType, 
      const char* dataTag,  
      const char* dataVal
   ) {
      // *** meta ***
      iotDS->device(deviceID);
      iotDS->activity(activityType);
      // *** fill string data before uploading ***
      iotDS->addString(dataTag, dataVal);
      iotDS->addString("user_id", USER_ID);//testing
      
      // *** uploading added data ***
      iotDS->logItem();
//      delay(3000);
    
  }

  // *** Upload Boolean Data to DataFoundry IoT Dataset
  void DFHelper::uploadIoTDataOfBoolean(
    const char* deviceID, 
    const char* activityType, 
    const char* dataTag, 
    bool dataVal
  ) {
      // *** meta ***
      iotDS->device(deviceID);
      iotDS->activity(activityType);
      // *** fill string data before uploading ***
      iotDS->addBool(dataTag, dataVal);
      iotDS->addString("user_id", USER_ID);//testing
      
      // *** uploading added data ***
      iotDS->logItem();
//      delay(3000);
   
  }

  // *************************
  // *** ENTITY DATASET OP ***
  // *************************
  // *** INTEGER DATA ***
  // *** Initial Upload Integer Data to DataFoundry Entity Dataset
  void DFHelper::initialUploadEntityDataOfInteger(
      const char* deviceID, 
      const char* entityToken, 
      const char* dataTag, 
      int dataVal
   ) {
      // *** meta ***
      // NOTE: id is used to identify the item
      entityDS->id(deviceID);//resource_id
      // NOTE:token cannot be empty, can act as a password if needed
      // use same string as id if password protection is not needed
      entityDS->token(entityToken);
      
      // *** fill integer data before uploading
      entityDS->addInt(dataTag, dataVal);
      entityDS->addString("user_id", USER_ID);//testing
     
      
      // *** uploading added data ***
      // NOTE: add the item (initially or after delete) //??
      entityDS->addItem();
 
//      delay(3000);
    
  }
  // *** Update with New Integer Data to DataFoundry Entity Dataset
  void DFHelper::updateEntityDataOfInteger(
      const char* deviceID, 
      const char* entityToken, 
      const char* existingDataTag, 
      int newDataVal
   ) {
      // *** meta ***
      // NOTE: id is used to identify the item
      entityDS->id(deviceID);
      // NOTE:token cannot be empty, can act as a password if needed
      // use same string as id if password protection is not needed
      entityDS->token(entityToken);
      
      // *** fill integer data before uploading
      entityDS->addInt(existingDataTag, newDataVal);
      entityDS->addString("user_id", USER_ID);//testing
      
      // *** uploading added data ***
      // NOTE: add the item (initially or after delete) //??
      entityDS->updateItem();
 
//      delay(3000);
    
  }

  // *** STRING DATA ***
  // *** Initial Upload String Data to DataFoundry Entity Dataset
  void DFHelper::initialUploadEntityDataOfString(
      const char* deviceID, 
      const char* entityToken, 
      const char* dataTag,  
      const char* dataVal
   ) {
      // *** meta ***
      // NOTE: id is used to identify the item
      entityDS->id(deviceID);
      // NOTE:token cannot be empty, can act as a password if needed
      // use same string as id if password protection is not needed
      entityDS->token(entityToken);
      
      
      // *** fill string data before uploading
      entityDS->addString(dataTag, dataVal);
      entityDS->addString("user_id", USER_ID);//testing
      
      // *** uploading added data ***
      // NOTE: add the item (initially or after delete) //??
      entityDS->addItem();
 
//      delay(3000);
    
  }
  // *** Update with New String Data to DataFoundry Entity Dataset
  void DFHelper::updateEntityDataOfString(
      const char* deviceID, 
      const char* entityToken,
      const char* existingDataTag, 
      const char* newDataVal
   ) {
      // *** meta ***
      // NOTE: id is used to identify the item
      entityDS->id(deviceID);
      // NOTE:token cannot be empty, can act as a password if needed
      // use same string as id if password protection is not needed
      entityDS->token(entityToken);
      
      
      // *** fill string data before uploading
      entityDS->addString(existingDataTag, newDataVal);
      entityDS->addString("user_id", USER_ID);//testing
      
      // *** uploading added data ***
      // NOTE: add the item (initially or after delete) //??
      entityDS->updateItem();
 
//      delay(3000);
    
  }

  // *** BOOLEAN DATA ***
  // *** Initial Upload String Data to DataFoundry Entity Dataset
  void DFHelper::initialUploadEntityDataOfBoolean(
      const char* deviceID, 
      const char* entityToken, 
      const char* dataTag, 
      bool dataVal
   ) {
      // *** meta ***
      // NOTE: id is used to identify the item
      entityDS->id(deviceID);
      // NOTE:token cannot be empty, can act as a password if needed
      // use same string as id if password protection is not needed
      entityDS->token(entityToken);
      
      
      // *** fill boolean data before uploading
      entityDS->addBool(dataTag, dataVal);
      entityDS->addString("user_id", USER_ID);//testing
      
      // *** uploading added data ***
      // NOTE: add the item (initially or after delete) //??
      entityDS->addItem();
 
//      delay(3000);
    
  }
  // *** Update with New Boolean Data to DataFoundry Entity Dataset
  void DFHelper::updateEntityDataOfBoolean(
      const char* deviceID, 
      const char* entityToken,
      const char* existingDataTag, 
      bool newDataVal
   ) {
      // *** meta ***
      // NOTE: id is used to identify the item
      entityDS->id(deviceID);
      // NOTE:token cannot be empty, can act as a password if needed
      // use same string as id if password protection is not needed
      entityDS->token(entityToken);
      
      // *** fill string data before uploading
      entityDS->addBool(existingDataTag, newDataVal);
      entityDS->addString("user_id", USER_ID);//testing
      
      // *** uploading added data ***
      // NOTE: add the item (initially or after delete) //??
      entityDS->updateItem();
 
//      delay(3000);
    
  }
  // ***************************************
  // *** RETRIEVE DATA FROM DATA FOUNDRY ***
  // ***************************************
  void DFHelper::extractEntityData(
    const char* deviceID, 
    const char* entityToken, 
    const char* dataTag, 
    const int  dataType
  ) {
    // *** meta ***
    // NOTE: id is used to identify the item
    entityDS->id(deviceID);
    // NOTE:token cannot be empty, can act as a password if needed
    // use same string as id if password protection is not needed
    entityDS->token(entityToken);

    // TESTING // GET ALL ITEMS??
    entityDS->getItem();

    // *** GET PARTICULAR ITEM WITH TYPE ***
    if (INTEGER == dataType) {
      entityDS->getInt(dataTag, -1);// ?-1: default
      
    } else if (STRING == dataType) {
      entityDS->getString(dataTag, "NO DATA Extracted");// ?"NO DATA Extracted" default message
      
    } if (BOOL == dataType) {
      entityDS->getBool(dataTag, false);// ? false: default in case no data retrieved
      
    }

//    delay(3000);
  }
   //********************
   //*** DELETE ITEMS ***
   //********************
  void DFHelper::removeItemFromDF(
    const char* deviceID, 
    const char* entityToken
  ) {
    // *** meta ***
    // NOTE: id is used to identify the item
    entityDS->id(deviceID);
    // NOTE:token cannot be empty, can act as a password if needed
    // use same string as id if password protection is not needed
    entityDS->token(entityToken);

    // *** REMOVE ALL ITEMS??
    entityDS->deleteItem();
//    delay(3000);
  }
