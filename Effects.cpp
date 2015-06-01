#define HUE_STEP 5
#define VALUE_STEP 5
#define PERIOD_STEP 3

#include "Effects.h"

Effects::Effects(){
  this -> reset();
}

void Effects::run(Sign &sign){
  switch(textEffect){
    case BASIC_TYPING: this -> basicTyping(sign); break;
    case RANDOM_ON: this -> randomOn(sign); break;
  }

  for(uint8_t i=0; i<LAYER_COUNT; i++){
    switch(colorEffect[i]){
      case SOLID_COLORS: this -> solidColor(sign, i); break;
      case SOLID_FADE: this -> solidFade(sign, i); break;
      case RANDOM_FADE: this -> randomFade(sign, i); break;
    }
  }
  clock ++;
}


void Effects::pushChar(char character){
  int32_t val = 0;
  switch(character){
    case 'R': this -> reset(); break;
    //case 'r': this -> randomize(); break;
    case 'q': clock = 0; break;   //Queue Button
    case 'k': val = period -= PERIOD_STEP; break;
    case 'j': val = period += PERIOD_STEP; break;

    case '1': val = (effectValue1++); break;
    case '!': val = (effectValue1--); break;
    case '2': val = (effectValue2++); break;
    case '@': val = (effectValue2--); break;
    case '3': val = (effectValue3++); break;
    case '#': val = (effectValue3--); break;

    case 'f': val = this -> increaseSpeed(0); break;
    case 's': val = this -> decreaseSpeed(0); break;
    case 'F': val = this -> increaseSpeed(1); break;
    case 'S': val = this -> decreaseSpeed(1); break;

    case '<': val = this -> prevTextEffect(); break;
    case '>': val = this -> nextTextEffect(); break;

    case 'l': val = this -> prevColorEffect(0); break;
    case 'h': val = this -> nextColorEffect(0); break;
    case 'L': val = this -> prevColorEffect(1); break;
    case 'H': val = this -> nextColorEffect(1); break;

    case 'c': val = color[0].hue += HUE_STEP; break;
    case 'C': val = color[1].hue += HUE_STEP; break;
    case 'v': val = color[0].saturation += VALUE_STEP; break;
    case 'V': val = color[1].saturation += VALUE_STEP; break;

    case 'b': val = color[0].value += VALUE_STEP; break;
    case 'd': val = color[0].value -= VALUE_STEP; break;
    case 'B': val = color[1].value += VALUE_STEP; break;
    case 'D': val = color[1].value -= VALUE_STEP; break;
  }
  Serial.print(character);
  Serial.print(": ");
  Serial.print(val);
  Serial.println(" ");
}

// Called when new letters pushed to sign
void Effects::signWasUpdated(Sign &sign){
  this -> run(sign);
  if(colorEffect[0] == RANDOM_FADE || colorEffect[1] == RANDOM_FADE){
    this -> recalculateSpeeds(sign);
  }
}

void Effects::reset(){
  textEffect = BASIC_TYPING;
  period = 100;
  clock = 0;
  effectValue1 = 1;
  effectValue2 = 800;
  effectValue3 = 1;
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    colorEffect[i] = SOLID_COLORS;
    color[i] = CHSV(128*i,255,255);
    fadeHue[i] = 0;
    fadeSpeed[i] = (-20*i)+10;
  }
  this -> incRandomSpeed(true, 0);

}

int16_t Effects::increaseSpeed(uint8_t layer){
  int16_t val = 0;
  switch(colorEffect[layer]){
    case RANDOM_FADE: val = this -> incRandomSpeed(true, layer); break;
    case SOLID_FADE: val = this -> incSegSpeed(true, layer); break;
  }
  return val;
}

int16_t Effects::decreaseSpeed(uint8_t layer){
  int16_t val = 0;
  switch(colorEffect[layer]){
    case RANDOM_FADE: val = this -> incRandomSpeed(false, layer); break;
    case SOLID_FADE: val = this -> incSegSpeed(false, layer);
  }
  return val;
}

int16_t Effects::incRandomSpeed(bool isPositive, uint8_t layer){
  int16_t val = this -> incSegSpeed(isPositive, layer);

  int16_t mn = min(fadeSpeed[0], fadeSpeed[1]);
  int16_t mx = max(fadeSpeed[0], fadeSpeed[1]);
  for(uint8_t i=0; i < 16*LETTERS_COUNT; i++){
    segSpeed[i] = random(mn, mx);
  }
  return val;
}

int16_t Effects::incSegSpeed(bool isPositive, uint8_t layer){
  if(isPositive){
    fadeSpeed[layer]++;
  }else{
    fadeSpeed[layer]--;
  }
  return fadeSpeed[layer];
}

void Effects::basicTyping(Sign &sign){
  uint8_t letters_count = sign.letterCount();

  // Set Characters
  for(uint8_t i=0; i < letters_count; i++){
    char current_char = sign.characters[i];
    sign.letters[i] -> setChar(current_char);
  }
}

void Effects::off(Sign &sign){
  uint16_t seg_count = sign.segmentCount();
  for(uint16_t i=0; i<seg_count; i++){
    sign.segments[i] -> isOn = false;
  }
}

void Effects::randomOn(Sign &sign){
  uint16_t seg_count = sign.segmentCount();
  if( clock % period == 0){
    this -> off(sign);
    for(uint8_t i = 0; i < effectValue1; i++){
      uint8_t rand = random(0,seg_count);
      sign.segments[rand] -> isOn = true;
    }
  }
}

uint8_t Effects::nextTextEffect(){
  textEffect++;
  return textEffect = textEffect % TEXT_EFFECTS_COUNT;
}
uint8_t Effects::prevTextEffect(){
  textEffect--;
  return textEffect = textEffect % TEXT_EFFECTS_COUNT;
}

uint8_t Effects::nextColorEffect(uint8_t ci){
  colorEffect[ci]++;
  return colorEffect[ci] = colorEffect[ci] % COLOR_EFFECTS_COUNT;
}
uint8_t Effects::prevColorEffect(uint8_t ci){
  if(colorEffect[ci] == 0){
    colorEffect[ci] = COLOR_EFFECTS_COUNT - 1;
  }else{
    colorEffect[ci]--;
    colorEffect[ci] = colorEffect[ci] % COLOR_EFFECTS_COUNT;
  }
  return colorEffect[ci];
}

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
