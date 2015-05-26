#include "Segment.h"

Segment::Segment(uint8_t length){

  for(uint8_t i; i< length; i++){
    pixels[i] = Pixel();
  }
  _length = length;
};

uint16_t Segment::pixelCount(){
  return _length;
}


void Segment::toArray(CRGB array[], uint16_t &currIdx){
  
  for(uint8_t i=0; i<_length; i++){
    array[currIdx] = pixels[i].color;
    currIdx++;
  }
}
