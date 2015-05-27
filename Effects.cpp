#include "Effects.h"

Effects::Effects(){
  currentEffect = BASIC_TYPING;
}

void Effects::run(Sign &sign){
  switch(currentEffect){
    case BASIC_TYPING: this -> basicTyping(sign); break;
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

  for(uint16_t i=0; i< seg_count; i++){
    Segment currSeg = *sign.segments[i];
    if(currSeg.isOn == true){
      currSeg.setColor(CRGB::Red);
    }else{
      currSeg.setColor(CRGB::White);
    }
  }

}
