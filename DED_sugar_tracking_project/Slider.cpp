/***
 * Slider cpp implementation
 * potentiometer
 * a great arduino slide potentiometer for projects requiring a linear analog input
 */

 #include "Slider.h"
 #include "Arduino.h"

 Slider::Slider(const int sliderAnalogPinA) {
      _sliderAnalogPinA = sliderAnalogPinA;
      isChanged         = false;
      _sliderPrevMappedVal  = 0;
 }

 void Slider::sliderConfig(float rawMinRange, float rawMaxRange, float mappedMinRange, float mappedMaxRange) {
    _rawMinRange = rawMinRange;
    _rawMaxRange = rawMaxRange;
    _mappedMinRange = mappedMinRange;
    _mappedMaxRange = mappedMaxRange;
    pinMode(_sliderAnalogPinA, INPUT); // slider pin for receiving signal from sliding
 }

 int Slider::sliderEventHandler() {
    _sliderRawVal = analogRead(_sliderAnalogPinA);
    _sliderMappedVal = map(_sliderRawVal, _rawMinRange, _rawMaxRange, _mappedMinRange, _mappedMaxRange);
    return _sliderMappedVal;
 }

 void Slider:: resetSliderState(bool state) {
    isChanged = state;
 }

 void Slider::setSliderPrevMappedVal(int newVal) {
   _sliderPrevMappedVal = newVal;
 }

 int Slider::getSliderPrevMappedVal() {
    return _sliderPrevMappedVal;
 }

 
