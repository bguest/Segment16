#include "SolidColor.h"

SolidColor::SolidColor(){
  this -> reset();
}

void SolidColor::reset(){
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    color[i] = CHSV(128*i,255,255);
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
  int32_t val = 0xFFFF;
  switch(character){
    case 'c': val = color[ci].hue += HUE_STEP; break;
    case 'C': val = color[ci].hue -= HUE_STEP; break;
    case 'v': val = color[ci].saturation += VALUE_STEP; break;
    case 'V': val = color[ci].saturation -= VALUE_STEP; break;
    case 'B': val = color[ci].value += VALUE_STEP; break;
    case 'b': val = color[ci].value -= VALUE_STEP; break;
  }
  String str = String(character);
  return(this -> usedSetting(str, val));
}
