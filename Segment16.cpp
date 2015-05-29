
#include "Segment16.h"

#define DATA_PIN 10
#define CLOCK_PIN 11

Segment16::Segment16(void){
  //uint16_t pixel_count = sign.pixelCount();
  //leds = new CRGB[pixel_count];
  //leds = new CRGB[89];
  //FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, pixel_count);
};

void Segment16::init(){
  uint16_t pixel_count = sign.pixelCount();
  leds = new CRGB[pixel_count];
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, pixel_count);
}

void Segment16::pushChar(uint32_t character){
  bool isEffectsKey = effects.pushChar(character);
  if(!isEffectsKey){
    sign.pushChar(character);
  }
}

void Segment16::show(void){

  effects.run(sign);

  uint16_t currentPixel = 0;
  for(uint8_t i=0; i < LETTERS_COUNT; i++){
    sign.letters[i] -> toArray(leds, currentPixel);
  }
  FastLED.show();
};
