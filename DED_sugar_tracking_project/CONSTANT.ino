/**
 * Constants for Data Foundry helper class
 */
 const char* IOT_DS    = "IOT_DATASET";
 const char* ENTITY_DS = "ENTITY_DATASET";
 const int INTEGER     = 0;
 const int STRING      = 1;
 const int BOOL        = 2;

 // *** CLOCK WISE ROTARY ENCODER PREF ***
 bool CLOCK_WISE_ROTATION_PREF = true;

 // *** SLIDER RANGE ***
 // *NOTE: different band of potentiometer may be different !!
 const float SLIDER_1_MAX_RANGE = 4095.0;
 const float SLIDER_1_MIN_RANGE = 0.0;

 const float SLIDER_2_MAX_RANGE = 4095.0;
 const float SLIDER_2_MIN_RANGE = 0.0;

 const float SLIDER_3_MAX_RANGE = 4095.0;
 const float SLIDER_3_MIN_RANGE = 400.0;

 // *** THE RANGE OF MAPPED OUTPUT VAL FROM SLIDER ***
 const float SLIDER_1_OUTPUT_MAPPED_MAX_RANGE = 6.0;
 const float SLIDER_1_OUTPUT_MAPPED_MIN_RANGE = 1.0;

 const float SLIDER_2_OUTPUT_MAPPED_MAX_RANGE = 6.0;
 const float SLIDER_2_OUTPUT_MAPPED_MIN_RANGE = 1.0;

 const float SLIDER_3_OUTPUT_MAPPED_MAX_RANGE = 6.0;
 const float SLIDER_3_OUTPUT_MAPPED_MIN_RANGE = 1.0;

 // *** ACTIVITY NAME
 const char* LOGGING_ACT = "self-logging";
