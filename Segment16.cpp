#include "Segment16.h"

Segment16::Segment16(void){

  uint8_t lenghts[16] = {2, 2, 4, 4, 2, 2, 4, 4, 2, 2, 4, 4, 2, 2, 2, 2};

  for(uint8_t i=0; i < LETTERS_COUNT; i++){
    letters[i] = new Letter(lenghts);
  }
  uint16_t pixel_count = this -> pixelCount();

  leds = new CRGB[pixel_count];

  FastLED.addLeds<WS2801>(leds, pixel_count);

};

uint16_t Segment16::pixelCount(){

  if(_pixel_count > 0){
    return _pixel_count;
  }

  uint16_t pixel_count = 0;
  for(uint8_t i = 0; i < LETTERS_COUNT; i++){
    pixel_count += letters[i]->pixelCount();
  }
  _pixel_count = pixel_count;
  return pixel_count;
}


void Segment16::show(void){

  uint16_t pixel_count = this -> pixelCount();
  CRGB* pixels = new CRGB[pixel_count];

  uint16_t currentPixel = 0;
  for(uint8_t i=0; i < LETTERS_COUNT; i++){
    letters[i] -> toArray(pixels, currentPixel);
  }

  for(uint16_t i=0; i < pixel_count; i++){
    leds[i] = pixels[i];
  }
  FastLED.show();

  delete [] pixels;
};
