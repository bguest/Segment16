#include "Letter.h"

Letter::Letter(uint8_t *lengths){

  //uint8_t lengths[16] = {2, 2, 4, 4, 2, 2, 4, 4, 2, 2, 4, 4, 2, 2, 2, 2};

  for(uint8_t i=0; i<16; i++){
    _lengths[i] = lengths[i];
    segments[i] = new Segment(lengths[i]);
  }

};

uint16_t Letter::pixelCount(){
  uint16_t pixel_count = 0;
  for(uint8_t i=0; i < 16; i++){
    pixel_count += segments[i]->pixelCount();
  }
  return pixel_count;
}

void Letter::toArray(CRGB array[], uint16_t &currIdx){
  for(uint8_t i; i<16; i++){
    segments[i] -> toArray(array, currIdx);
  }
  
}

