#include "Effect.h"
#include "RandomOn.h"

RandomOn::RandomOn(){
  this -> reset();
}

void RandomOn::reset(){
  onCount = 1;
  lastRun = 0;
  cycleTime = 500;
  shouldReset = true;
  turnOn = true;
}

void RandomOn::run(Sign &sign, uint8_t layer){
  if(! this -> shouldRun() ){return;};
  sign.textChanged = true;

  uint16_t seg_count = sign.segmentCount();
  if(shouldReset){
    this -> off(sign);
  }else{
    sign.setLayer(BACKGROUND_LAYER, false);
  }
  for(uint8_t i = 0; i < onCount; i++){
    uint8_t rand = random(0,seg_count);
    sign.segments[rand] -> isOn = turnOn;
  }
}

bool RandomOn::pushChar(char character, uint8_t ci){
  int32_t val = 0xFFFF;
  String desc;
  const uint8_t periodStep = 25;

  if( this -> useCharForTiming(character) ){ return true;};

  switch(character){
    case 'o': val = turnOn = !turnOn;
              desc = SET_SEGS_STR; break;
    case 'r': shouldReset = true; val = 1;
              desc = RESET_STR; break;

    case 'k': val = cycleTime -= periodStep;
              desc = CYCLE_TIME_STR; break;
    case 'j': val = cycleTime += periodStep;
              desc = CYCLE_TIME_STR; break;
    case ']': val = (onCount++);
              desc = NUMBER_ON_STR; break;
    case '[': val = (onCount--);
              desc = NUMBER_ON_STR; break;
  }
  return( this ->usedSetting(desc, val) );
}
