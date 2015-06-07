#include "SolidColor.h"

SolidColor::SolidColor(){
  this -> reset();
}

void SolidColor::reset(){
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    color[i] = CHSV(128*i,255,255);
  }
}
void SolidColor::run(Sign &sign, uint32_t clock, uint8_t ci){
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
  int32_t val = 0;
  switch(character){
    case 'c': val = color[ci].hue += HUE_STEP; break;
    case 'C': val = color[ci].hue -= HUE_STEP; break;
    case 'v': val = color[ci].saturation += VALUE_STEP; break;
    case 'V': val = color[ci].saturation -= VALUE_STEP; break;

    case 'b': val = color[ci].value += VALUE_STEP; break;
    case 'd': val = color[ci].value -= VALUE_STEP; break;
  }

  if(val > 0){
    Serial.print(character);
    Serial.print(": ");
    Serial.print(val);
    Serial.println(" ");
    return true;
  }
  return false;

}
