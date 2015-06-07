#define HUE_STEP 5
#define VALUE_STEP 5
#define PERIOD_STEP 3

#include "Effects.h"
#include "effects/Effect.cpp"
#include "effects/RandomOn.cpp"
#include "effects/BasicTyping.cpp"
#include "effects/SolidColor.cpp"
#include "effects/SolidFade.cpp"
#include "effects/RandomFade.cpp"

Effects::Effects(){
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    colorEffect[i] = &solidColor;
    cColorEffect[i] = SOLID_COLORS;
  }
  cTextEffect = BASIC_TYPING;
  textEffect = &basicTyping;
  this -> reset();
}

void Effects::run(Sign &sign){

  textEffect -> run(sign, clock, 0);

  for(uint8_t i=0; i<LAYER_COUNT; i++){
    colorEffect[i] -> run(sign, clock, i);
  }
  clock ++;
}

void Effects::pushChar(char character){

  switch(character){
    case '0':
      curLayer = 0;
      Serial.println("Layer 0");
      return;
    case '1':
      curLayer = 1;
      Serial.println("Layer 1");
      return;
  }

  if( textEffect -> pushChar(character, 0) ){ return; }
  if( colorEffect[curLayer] -> pushChar(character, curLayer) ){ return; }

  int32_t val = 0;
  switch(character){
    case 'R': this -> reset(); break;
    //case 'r': this -> randomize(); break;
    case 'g': clock = 1; break;   //Queue Button
    case 't': clock = 0; break;   //Step Button

    case '<': val = this -> prevTextEffect(); break;
    case '>': val = this -> nextTextEffect(); break;

    case 'l': val = this -> prevColorEffect(curLayer); break;
    case 'h': val = this -> nextColorEffect(curLayer); break;

  }
  Serial.print(character);
  Serial.print(": ");
  Serial.print(val);
  Serial.println(" ");
}

// Called when new letters pushed to sign
void Effects::signWasUpdated(Sign &sign){
  this -> run(sign);
  textEffect -> signWasUpdated(sign);
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    colorEffect[i] -> signWasUpdated(sign);
  }
}

void Effects::reset(){
  curLayer = 0;
  clock = 0;
  textEffect -> reset();
  for(uint8_t i=1; i<LAYER_COUNT; i++){
    colorEffect[i] -> reset();
  }
}

uint8_t Effects::nextTextEffect(){
  cTextEffect++;
  cTextEffect = cTextEffect % TEXT_EFFECTS_COUNT;
  this -> updateTextEffect();
  return cTextEffect;
}

uint8_t Effects::prevTextEffect(){
  cTextEffect--;
  cTextEffect = cTextEffect % TEXT_EFFECTS_COUNT;
  this -> updateTextEffect();
  return cTextEffect;
}

void Effects::updateTextEffect(){
  switch(cTextEffect){
    case RANDOM_ON:
      textEffect = &randomOn;
      Serial.println("Random On");
      break;
    case BASIC_TYPING:
      textEffect = &basicTyping;
      Serial.println("Basic Typing");
      break;
    default:
      textEffect = &nullEffect;
      Serial.println("ERROR");
  }
}

uint8_t Effects::nextColorEffect(uint8_t ci){
  cColorEffect[ci]++;
  cColorEffect[ci] = cColorEffect[ci] % COLOR_EFFECTS_COUNT;
  this -> updateColorEffect(ci);
  return cColorEffect[ci];
}
uint8_t Effects::prevColorEffect(uint8_t ci){
  if(cColorEffect[ci] == 0){
    cColorEffect[ci] = COLOR_EFFECTS_COUNT - 1;
  }else{
    cColorEffect[ci]--;
    cColorEffect[ci] = cColorEffect[ci] % COLOR_EFFECTS_COUNT;
  }
  this -> updateColorEffect(ci);
  return cColorEffect[ci];
}

void Effects::updateColorEffect(uint8_t ci){
  switch(cColorEffect[ci]){
    case SOLID_COLORS:
      colorEffect[ci] = &solidColor;
      Serial.println("Solid Color");
      break;
    case RANDOM_FADE:
      colorEffect[ci] = &randomFade;
      Serial.println("Random Fade");
      break;
    case SOLID_FADE:
      colorEffect[ci] = &solidFade;
      Serial.println("Solid Fade");
      break;
  }
}

/*
void Effects::solidColor(Sign &sign, uint8_t ci){
  uint16_t seg_count = sign.segmentCount();

  bool on = (ci == 0);

  for(uint16_t i=0; i< seg_count; i++){
    Segment currSeg = *sign.segments[i];
    if(currSeg.isOn == on){
      currSeg.setColor(color[ci]);
    }
  }
}


void Effects::solidFade(Sign &sign, uint8_t ci){
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

void Effects::randomFade(Sign &sign, uint8_t ci){
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

void Effects::recalculateSpeeds(Sign &sign){
  uint16_t seg_count = sign.segmentCount();
  uint16_t hue_final[LAYER_COUNT];

  for(uint8_t i=0; i<LAYER_COUNT; i++){
    hue_final[i] = (uint16_t)(color[i].hue << 8);
  }

  for(uint16_t i=0; i< seg_count; i++){
    Segment currSeg = *sign.segments[i];
    uint8_t ci = currSeg.isOn ? 0 : 1;
    segSpeed[i] = (hue_final[ci] - segHue[i])/effectValue2;
  }
}
*/
