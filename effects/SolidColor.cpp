#include "SolidColor.h"

SolidColor::SolidColor(){
  this -> reset();
}

void SolidColor::reset(){
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    color[i] = CHSV(128*i,255,255-100*i);
  }
}
void SolidColor::run(Sign &sign, uint8_t ci){
  uint16_t seg_count = sign.segmentCount();

  bool on = (ci == 0);

  for(uint16_t i=0; i< seg_count; i++){
    Segment currSeg = *sign.segments[i];
    if(currSeg.isOn == on){
      currSeg.setColor(color[ci]);
    }
  }
}

bool SolidColor::pushChar(char character, uint8_t ci){
  return this -> useCharForColor(character, ci);
}
