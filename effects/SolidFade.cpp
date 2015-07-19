#include "SolidFade.h"

SolidFade::SolidFade(){
  this -> reset();
}

void SolidFade::reset(){
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    color[i] = CHSV(128*i,255,255);
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
  int32_t val = 0xFFFF;
  String desc;

  switch(character){
    case 'f': val = this -> incSegSpeed(true, ci);
              desc = FADE_SPEED_STR; break;
    case 's': val = this -> incSegSpeed(false, ci);
              desc = FADE_SPEED_STR; break;

    case 'c': val = (color[ci].hue += HUE_STEP);
              desc = HUE_STR; break;
    case 'C': val = (color[ci].hue -= HUE_STEP);
              desc = HUE_STR; break;
    case 'v': val = (color[ci].saturation += VALUE_STEP);
              desc = SAT_STR; break;
    case 'V': val = (color[ci].saturation -= VALUE_STEP);
              desc = SAT_STR; break;
    case 'B': val = (color[ci].value -= VALUE_STEP);
              desc = VAL_STR; break;
    case 'b': val = (color[ci].value += VALUE_STEP);
              desc = VAL_STR; break;
  }
  return usedSetting(desc, val);

}

int16_t SolidFade::incSegSpeed(bool isPositive, uint8_t layer){
  if(isPositive){
    fadeSpeed[layer]++;
  }else{
    fadeSpeed[layer]--;
  }
  return fadeSpeed[layer];
}

