#define HUE_STEP 15
#define VALUE_STEP 15

#include "Effects.h"

Effects::Effects(){
  textEffect = BASIC_TYPING;
  colorEffect = SOLID_COLORS;
  bgColorEffect = SOLID_COLORS;
  color = CHSV(128,255,255);
  bgColor = CHSV(0,255,0);
}

void Effects::run(Sign &sign){
  switch(textEffect){
    case BASIC_TYPING: this -> basicTyping(sign); break;
  }
  switch(colorEffect){
    case SOLID_COLORS: this -> solidColor(sign); break;
  }
  switch(bgColorEffect){
    case SOLID_COLORS: this -> bgSolidColor(sign); break;
  }
}

void Effects::basicTyping(Sign &sign){
  uint8_t letters_count = sign.letterCount();
  uint16_t seg_count    = sign.segmentCount();

  // Set Characters
  for(uint8_t i=0; i < letters_count; i++){
    char current_char = sign.characters[i];
    sign.letters[i] -> setChar(current_char);
  }

}

bool Effects::pushChar(uint32_t character){
  bool used = false;
  switch(character){
    case 0xE28098: this -> increaseHue(); used = true; break;
    case 0xC3A6: this -> bgIncreaseHue(); used = true; break;
    case 0xC2AC: this -> bgIncreaseValue(); used = true; break;
    case 0xCB9A: this -> bgDecreaseValue(); used = true; break;
  }

  return used;
}

void Effects::increaseHue(){
  color.hue += HUE_STEP;
}

void Effects::bgIncreaseHue(){
  bgColor.hue += HUE_STEP;
}

void Effects::bgIncreaseValue(){
  bgColor.value += VALUE_STEP;
}

void Effects::bgDecreaseValue(){
  bgColor.value -= VALUE_STEP;
}

void Effects::solidColor(Sign &sign){
  uint16_t seg_count = sign.segmentCount();
  for(uint16_t i=0; i< seg_count; i++){
    Segment currSeg = *sign.segments[i];
    if(currSeg.isOn == true){
      currSeg.setColor(color);
    }
  }
}

void Effects::bgSolidColor(Sign &sign){
  uint16_t seg_count = sign.segmentCount();
  for(uint16_t i=0; i< seg_count; i++){
    Segment currSeg = *sign.segments[i];
    if(currSeg.isOn == false){
      currSeg.setColor(bgColor);
    }
  }

}
