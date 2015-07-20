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
  if( this -> useCharForColor(character, ci)){ return true; };

  int32_t val = 0xFFFF;
  String desc;

  switch(character){
    case 'f': val = this -> incSegSpeed(true, ci);
              desc = FADE_SPEED_STR; break;
    case 's': val = this -> incSegSpeed(false, ci);
              desc = FADE_SPEED_STR; break;
  }
  return usedSetting(desc, val);

}

void SolidFade::invertColors(){
  Effect::invertColors();
  uint16_t tempHue = fadeHue[0];
  fadeHue[0] = fadeHue[1];
  fadeHue[1] = tempHue;
}

int16_t SolidFade::incSegSpeed(bool isPositive, uint8_t layer){
  if(isPositive){
    fadeSpeed[layer]++;
  }else{
    fadeSpeed[layer]--;
  }
  return fadeSpeed[layer];
}

