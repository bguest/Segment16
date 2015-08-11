#include "Effect.h"
#include "RainbowLetter.h"

RainbowLetter::RainbowLetter(){
  this -> reset();
}

void RainbowLetter::reset(){
  isStatic = false;
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    color[i] = CHSV(128*i,255,255);
    hueStep[i] = 40;
  }
}

void RainbowLetter::run(Sign &sign, uint8_t layer){
  if( sign.textChanged ){ this -> signWasUpdated(sign, layer);}

  uint8_t letters_count = sign.letterCount();
  CHSV curr_color = color[layer];

  for(uint8_t i=0; i<letters_count; i++){
    Letter* curr_letter = sign.letters[i];
    curr_letter -> setColor(layer, curr_color);
    curr_color.hue += hueStep[layer];
  }

}

bool RainbowLetter::pushChar(char character, uint8_t ci){
  if( this -> useCharForColor(character, ci)){ return true; };

  int32_t val = 0xFFFF;
  String desc;

  switch(character){

    case 'w': val = (color[ci].hue += hueStep[ci]);
              desc = "Jump forward"; break;
    case 'e': val = (color[ci].hue -= hueStep[ci]);
              desc = "Jump backward"; break;

    case 's': val = (hueStep[ci] -= HUE_STEP);
              desc = STEP_SIZE_STR; break;
    case 'f': val = (hueStep[ci] += HUE_STEP);
              desc = STEP_SIZE_STR; break;
    case 'd': val = (isStatic = !isStatic);
              desc = "Static"; break;

  }
  return( usedSetting(desc, val));
}

void RainbowLetter::signWasUpdated(Sign &sign, uint8_t layer){
  if(isStatic){return;}
  color[layer].hue += hueStep[layer];
}

void RainbowLetter::signWasUpdated(Sign &sign){
  for(uint8_t i=0; i< LAYER_COUNT; i++){
    this -> signWasUpdated(sign, i);
  }
}
