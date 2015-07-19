#include "Effect.h"
#include "RainbowSegment.h"

RainbowSegment::RainbowSegment(){
  this -> reset();
}

void RainbowSegment::reset(){
  isStatic = false;
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    color[i] = CHSV(128*i,255,255);
    hueStep[i] = 40;
  }
}

void RainbowSegment::run(Sign &sign, uint8_t layer){
  if( sign.textChanged ){ this -> signWasUpdated(sign);}
  uint8_t segment_count = sign.segmentCount();
  CHSV curr_color = color[layer];

  for(uint8_t i=0; i<segment_count; i++){
    Segment* curr_segment = sign.segments[i];
    curr_segment -> setColor(layer, curr_color);
    curr_color.hue += hueStep[layer];
  }

}

bool RainbowSegment::pushChar(char character, uint8_t ci){
  int32_t val = 0xFFFF;
  String desc;

  switch(character){
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

void RainbowSegment::signWasUpdated(Sign &sign){
  if(isStatic){return;}

  for(uint8_t i=0; i< LAYER_COUNT; i++){
    color[i].hue += hueStep[i];
  }
}
