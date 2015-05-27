#include "Sign.h"

Sign::Sign(void){

  uint8_t lengths[2][16] = {
    {3, 2, 4, 4, 2, 2, 4, 4, 2, 2, 4, 4, 2, 2, 2, 2},
    {2, 2, 4, 4, 2, 2, 4, 4, 2, 2, 4, 4, 2, 2, 2, 2}
  };

  uint16_t curr = 0;

  for(uint16_t i=0; i < LETTERS_COUNT; i++){
    letters[i] = new Letter(lengths[i]);
    for(uint16_t j=0; j<16; j++){
      segments[(i*16)+j] = letters[i] -> segments[j];
    }
  }
  //uint16_t pixel_count = this -> pixelCount();

  characters[0] = 'A';
  characters[1] = 'B';
};

uint16_t Sign::pixelCount(){

  //if(_pixel_count > 0){
    //return _pixel_count;
  //}

  uint16_t pixel_count = 0;
  for(uint8_t i = 0; i < LETTERS_COUNT; i++){
    pixel_count += letters[i]->pixelCount();
  }
  _pixel_count = pixel_count;
  return pixel_count;
}

uint8_t Sign::letterCount(){
  return LETTERS_COUNT;
}

uint16_t Sign::segmentCount(){
  return 16*LETTERS_COUNT;
}