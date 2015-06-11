#define FADE_TIME_STEP 5
#include "RandomFade.h"

RandomFade::RandomFade(){
  this -> reset();
}

void RandomFade::reset(){
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    color[i] = CHSV(128*i,255,255);
    fadeSpeed[i] = (-20*i)+10;
  }
  this -> incRandomSpeed(true, 0);
}

void RandomFade::run(Sign &sign, uint8_t ci){
  uint16_t seg_count = sign.segmentCount();
  CHSV clr = color[ci];

  bool on = (ci == 0);

  for(uint8_t i=0; i < seg_count; i++){
    Segment currSeg = *sign.segments[i];
    if(currSeg.isOn == on){
      segHue[i] += segSpeed[i];
      clr.hue = (uint8_t)(segHue[i] >> 8);
      currSeg.setColor(clr);
    }
  }
}

bool RandomFade::pushChar(char character, uint8_t ci){
  int32_t val = 0;
  switch(character){
    case 'c': val = color[ci].hue += HUE_STEP; break;
    case 'C': val = color[ci].hue -= HUE_STEP; break;
    case 'v': val = color[ci].saturation += VALUE_STEP; break;
    case 'V': val = color[ci].saturation += VALUE_STEP; break;

    case 'b': val = color[ci].value += VALUE_STEP; break;
    case 'd': val = color[ci].value -= VALUE_STEP; break;
    case 'f': val = this -> incRandomSpeed(true, ci); break;
    case 's': val = this -> incRandomSpeed(false, ci); break;
    case 'F': val = fadeTime += FADE_TIME_STEP; break;
    case 'S': val = fadeTime -= FADE_TIME_STEP; break;
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

int16_t RandomFade::incRandomSpeed(bool isPositive, uint8_t layer){

  if(isPositive){
    fadeSpeed[layer]++;
  }else{
    fadeSpeed[layer]--;
  }

  int16_t mn = min(fadeSpeed[0], fadeSpeed[1]);
  int16_t mx = max(fadeSpeed[0], fadeSpeed[1]);
  for(uint8_t i=0; i < 16*LETTERS_COUNT; i++){
    segSpeed[i] = random(mn, mx);
  }
  return fadeSpeed[layer];
}

// Called when new letters pushed to sign
void RandomFade::signWasUpdated(Sign &sign){
  this -> recalculateSpeeds(sign);
}

void RandomFade::recalculateSpeeds(Sign &sign){
  uint16_t seg_count = sign.segmentCount();
  uint16_t hue_final[LAYER_COUNT];

  for(uint8_t i=0; i<LAYER_COUNT; i++){
    hue_final[i] = (uint16_t)(color[i].hue << 8);
  }

  for(uint16_t i=0; i< seg_count; i++){
    Segment currSeg = *sign.segments[i];
    uint8_t ci = currSeg.isOn ? 0 : 1;
    segSpeed[i] = (hue_final[ci] - segHue[i])/fadeTime;
  }
}
