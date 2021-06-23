 
#include "DFDataset.h"

extern const char* WIFI_SSID; //ssid of wifi network
extern const char* WIFI_PIN; //password of local wifi network
extern const char* DF_BASE_URL;

extern const char* IOT_DS;
extern const char* ENTITY_DS;
extern const int INTEGER;
extern const int STRING;
extern const int BOOL;

extern const char* IOT_DATASET_1_TOKEN;
extern const int  IOT_DATASET_1_ID;

extern const char* USER_ID;

    
// *** Data Foundry Helper Class **
class DFHelper {
  // ******************
  // *** ATTRIBUTES ***
  // ******************
  private:
    DFDataset *iotDS;
    DFDataset *entityDS;
    
    const char* datasetType;
    int datasetID = 0;
    const char* datasetToken;
    
  // *******************
  // *** CONSTRUCTOR ***
  // *******************  
  public:
    DFHelper(
      const char* dataFoundryURL, 
      const char* datasetType, 
      int  datasetID, 
      const char* datasetToken
    ); 
    
    DFDataset* getIoTDataset();
    DFDataset* getEntityDataset();
    
    // ***************
    // *** METHODS ***
    // ***************
    // *** Config WiFi network
    void wifiConnectConfig();
    const char* getDFDatasetType();
    int getDFDatasetID();
    // **********************
    // *** IOT DATASET OP ***
    // **********************
    void uploadIoTSelfReportOfSugar(
        const char* deviceID, 
        const char* activityType, 
        int btn1CountVal,
        int btn2CountVal,
        int btn3CountVal,
        int slider1MappedVal,
        int slider2MappedVal,
        int slider3MappedVal
    );
    // *** Upload Integer Data to DataFoundry IoT Dataset
    void uploadIoTDataOfInteger(
        const char* deviceID, 
        const char* activityType, 
        const char* dataTag, 
        int dataVal
     );
    // *** Upload String Data to DataFoundry IoT Dataset
    void uploadIoTDataOfString(
        const char* deviceID, 
        const char* activityType, 
        const char* dataTag,  
        const char* dataVal
     );
  
    // *** Upload Boolean Data to DataFoundry IoT Dataset
    void uploadIoTDataOfBoolean(
      const char* deviceID, 
      const char* activityType, 
      const char* dataTag, 
      bool dataVal
    );
  
    // *************************
    // *** ENTITY DATASET OP ***
    // *************************
    // *** INTEGER DATA ***
    // *** Initial Upload Integer Data to DataFoundry Entity Dataset
    void initialUploadEntityDataOfInteger(
        const char* deviceID, 
        const char* entityToken, 
        const char* dataTag, 
        int dataVal
     );
    // *** Update with New Integer Data to DataFoundry Entity Dataset
    void updateEntityDataOfInteger(
        const char* deviceID, 
        const char* entityToken, 
        const char* existingDataTag, 
        int newDataVal
     );
  
    // *** STRING DATA ***
    // *** Initial Upload String Data to DataFoundry Entity Dataset
    void initialUploadEntityDataOfString(
        const char* deviceID, 
        const char* entityToken, 
        const char* dataTag,  
        const char* dataVal
     );
    // *** Update with New String Data to DataFoundry Entity Dataset
    void updateEntityDataOfString(
        const char* deviceID, 
        const char* entityToken, 
        const char* existingDataTag,  
        const char* newDataVal
     );
  
    // *** BOOLEAN DATA ***
    // *** Initial Upload String Data to DataFoundry Entity Dataset
    void initialUploadEntityDataOfBoolean(
        const char* deviceID, 
        const char* entityToken, 
        const char* dataTag, 
        bool dataVal
     );
    // *** Update with New Boolean Data to DataFoundry Entity Dataset
    void updateEntityDataOfBoolean(
        const char* deviceID, 
        const char* entityToken,
        const char* existingDataTag, 
        bool newDataVal
     );
    // ***************************************
    // *** RETRIEVE DATA FROM DATA FOUNDRY ***
    // ***************************************
    void extractEntityData(
      const char* deviceID, 
      const char* entityToken, 
      const char* dataTag, 
      const int  dataType
    );
    // ********************
    // *** DELETE ITEMS ***
    // ********************
    void removeItemFromDF(
      const char* deviceID, 
      const char* entityToken
    );
    

  
  // ***
};
