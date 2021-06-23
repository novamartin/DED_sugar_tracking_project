/***
 * Slider header file
 */

 extern const float SLIDER_1_MAX_RANGE;
 extern const float SLIDER_1_MIN_RANGE;

 extern const float SLIDER_2_MAX_RANGE;
 extern const float SLIDER_2_MIN_RANGE;

 extern const float SLIDER_3_MAX_RANGE;
 extern const float SLIDER_3_MIN_RANGE;
 
 extern const float SLIDER_1_OUTPUT_MAPPED_MAX_RANGE;
 extern const float SLIDER_1_OUTPUT_MAPPED_MIN_RANGE;

 extern const float SLIDER_2_OUTPUT_MAPPED_MIN_RANGE;
 extern const float SLIDER_2_OUTPUT_MAPPED_MAX_RANGE;

 extern const float SLIDER_3_OUTPUT_MAPPED_MIN_RANGE;
 extern const float SLIDER_3_OUTPUT_MAPPED_MAX_RANGE;
 
 class Slider {

  private:
    int _sliderAnalogPinA;
    int _sliderRawVal;
    int _sliderMappedVal;
    int _sliderPrevMappedVal;
    int _rawMinRange;
    int _rawMaxRange;
    int _mappedMinRange;
    int _mappedMaxRange;
    int EMA_S = 0;
    
  public:
    // *** constructor ***
    Slider(const int sliderAnalogPinA);

    void sliderConfig(float rawMinRange, float rawMaxRange, float mappedMinRange, float mappedMaxRange);

    int sliderEventHandler();

    void resetSliderState(bool state);

    void setSliderPrevMappedVal(int newVal);

    int getSliderPrevMappedVal();
    
    bool isChanged;
 
 };
