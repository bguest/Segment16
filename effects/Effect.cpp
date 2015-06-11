
#include "Effect.h"

Effect::Effect(){
  lastRun=0;
  cycleTime=5;
}

void Effect::reset(){
}
void Effect::run(Sign &sign, uint8_t layer){
}
void Effect::signWasUpdated(Sign &sign){
}
bool Effect::pushChar(char character, uint8_t layer){
  return false;
}

void Effect::off(Sign &sign){
  uint16_t seg_count = sign.segmentCount();
  for(uint16_t i=0; i<seg_count; i++){
    sign.segments[i] -> isOn = false;
  }
}

bool Effect::shouldRun(){
  unsigned long currTime = millis();
  if(currTime - lastRun > cycleTime){
    lastRun = currTime;
    return true;
  }else{
    return false;
  }

}

bool Effect::useCharForTiming(char character){
  switch(character){
    case 't':
      lastRun = 0;
      return true;
    case 'g':
      lastRun = millis();
      return true;
      break;
  }
  return false;
}
