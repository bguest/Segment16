#include "Segment.h"

Segment::Segment(){
}

Segment::Segment(uint8_t length){
  //pixels[length] = new Pixel[length];

  for(uint8_t i=0; i< length; i++){
    pixels[i] = new Pixel();
  }
  _length = length;

  isOn = false;
};

uint16_t Segment::pixelCount(){
  return _length;
}

void Segment::toArray(CRGB array[], uint16_t &currIdx){

  for(uint8_t i=0; i< _length; i++){
    array[currIdx] = pixels[i] -> getColor();
    currIdx++;
  }
}

void Segment::setColor(CRGB color){
  for(uint8_t i=0; i< _length; i++){
    pixels[i] -> setColor(color);
 }
}
