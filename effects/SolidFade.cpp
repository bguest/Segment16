#include "SolidFade.h"

SolidFade::SolidFade(){
  this -> reset();
}

void SolidFade::reset(){
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    fadeHue[i] = 0;
    fadeSpeed[i] = (-20*i)+10;
  }
}

void SolidFade::run(Sign &sign, uint8_t ci){
  uint16_t seg_count = sign.segmentCount();
  CHSV clr = color[ci];

  fadeHue[ci] += fadeSpeed[ci];
  clr.hue = (uint8_t)(fadeHue[ci] >> 8);

  bool on = (ci == 0);

  for(uint8_t i=0; i < seg_count; i++){
    Segment currSeg = *sign.segments[i];
    if(currSeg.isOn == on){
      currSeg.setColor(clr);
    }
  }
}

bool SolidFade::pushChar(char character, uint8_t ci){
  int32_t val = 0;
  switch(character){
    case 'f': val = this -> incSegSpeed(true, ci); break;
    case 's': val = this -> incSegSpeed(false, ci); break;

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

int16_t SolidFade::incSegSpeed(bool isPositive, uint8_t layer){
  if(isPositive){
    fadeSpeed[layer]++;
  }else{
    fadeSpeed[layer]--;
  }
  return fadeSpeed[layer];
}

