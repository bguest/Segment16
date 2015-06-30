#include "Letter.h"

Letter::Letter(){};

Letter::Letter(uint8_t lengths[16]){

  for(uint8_t i=0; i<16; i++){
    _lengths[i] = lengths[i];
    segments[i] = new Segment(lengths[i]);
  }

};

uint16_t Letter::pixelCount(){
  uint16_t pixel_count = 0;
  for(uint8_t i=0; i < 16; i++){
    pixel_count += _lengths[i];
    //pixel_count += segments[i]->pixelCount();
  }
  return pixel_count;
}

void Letter::setChar(char character){
  currentChar = character;
  uint16_t binarySegs = binarySegsForChar(character);
                  //0123456789012345
  uint16_t mask = 0b1000000000000000;
  for(uint8_t i=0; i<16; i++){
    if(mask & binarySegs){
      segments[i]->isOn = true;
    }else{
      segments[i]->isOn = false;
    }
    mask = mask >> 1;
  }

}
void Letter::setLayer(uint8_t layer, bool isOn){
  uint16_t binarySegs = binarySegsForChar(currentChar);
  if(layer == 1){ binarySegs = ~binarySegs;}
                  //0123456789012345
  uint16_t mask = 0b1000000000000000;
  for(uint8_t i=0; i<16; i++){
    if(mask & binarySegs){
      segments[i]->isOn = isOn;
    }
    mask = mask >> 1;
  }
}

void Letter::toArray(CRGB array[], uint16_t &currIdx){
  for(uint16_t i=0; i<16; i++){
    segments[i] -> toArray(array, currIdx);
  }

}

