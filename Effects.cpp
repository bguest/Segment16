#define HUE_STEP 15
#define VALUE_STEP 15
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
  switch(colorEffect){
    case SOLID_COLORS: this -> solidColor(sign); break;
    case HUE_FADE: this -> hueFade(sign); break;
  }
  switch(bgColorEffect){
    case SOLID_COLORS: this -> bgSolidColor(sign); break;
    case HUE_FADE: this -> bgHueFade(sign); break;
  }
  clock ++;
}


void Effects::pushChar(char character){
  bool used = false;
  int32_t val = 0;
  switch(character){
    case 'r': this -> reset(); break;
    case 'q': clock = 0; break;   //Queue Button
    case 'k': val = period -= PERIOD_STEP; break;
    case 'j': val = period += PERIOD_STEP; break;

    case '1': val = (effectValue1++); break;
    case '!': val = (effectValue1--); break;
    case '2': val = (effectValue2++); break;
    case '@': val = (effectValue2--); break;
    case '3': val = (effectValue3++); break;
    case '#': val = (effectValue3--); break;

    case '<': val = this -> prevTextEffect(); break;
    case '>': val = this -> nextTextEffect(); break;

    case 'l': val = this -> prevColorEffect(); break;
    case 'h': val = this -> nextColorEffect(); break;
    case 'L': val = this -> prevBgColorEffect(); break;
    case 'H': val = this -> nextBgColorEffect(); break;

    case 'c': val = color.hue += HUE_STEP; break;
    case 'C': val = bgColor.hue += HUE_STEP; break;

    case 'b': val = color.value += VALUE_STEP; break;
    case 'd': val = color.value -= VALUE_STEP; break;
    case 'B': val = bgColor.value += VALUE_STEP; break;
    case 'D': val = bgColor.value -= VALUE_STEP; break;
  }
  Serial.print(character);
  Serial.print(": ");
  Serial.print(val);
  Serial.println(" ");
}

void Effects::reset(){
  textEffect = BASIC_TYPING;
  colorEffect = SOLID_COLORS;
  bgColorEffect = SOLID_COLORS;
  color = CHSV(128,255,255);
  bgColor = CHSV(0,255,0);
  period = 100;
  clock = 0;
  effectValue1 = 1;
  effectValue2 = 1;
  effectValue3 = 1;
}

void Effects::basicTyping(Sign &sign){
  uint8_t letters_count = sign.letterCount();
  uint16_t seg_count    = sign.segmentCount();

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

uint8_t Effects::nextColorEffect(){
  colorEffect++;
  return colorEffect = colorEffect % COLOR_EFFECTS_COUNT;
}
uint8_t Effects::prevColorEffect(){
  colorEffect--;
  return colorEffect = colorEffect % COLOR_EFFECTS_COUNT;
}

uint8_t Effects::nextBgColorEffect(){
  bgColorEffect++;
  return colorEffect = bgColorEffect % COLOR_EFFECTS_COUNT;
}
uint8_t Effects::prevBgColorEffect(){
  bgColorEffect--;
  return bgColorEffect = bgColorEffect % COLOR_EFFECTS_COUNT;
}

void Effects::solidColor(Sign &sign){
  uint16_t seg_count = sign.segmentCount();
  for(uint16_t i=0; i< seg_count; i++){
    Segment currSeg = *sign.segments[i];
    if(currSeg.isOn == true){
      currSeg.setColor(color);
    }
  }
}

void Effects::bgSolidColor(Sign &sign){
  uint16_t seg_count = sign.segmentCount();
  for(uint16_t i=0; i< seg_count; i++){
    Segment currSeg = *sign.segments[i];
    if(currSeg.isOn == false){
      currSeg.setColor(bgColor);
    }
  }
}

void Effects::hueFade(Sign &sign){
  if( clock % 3 == 0){
    color.hue += effectValue2;
    this -> solidColor(sign);
  }
}

void Effects::bgHueFade(Sign &sign){
  if( clock % 3 == 0){
    bgColor.hue += effectValue3;
    this -> bgSolidColor(sign);
  }
}
