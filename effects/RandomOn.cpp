#include "Effect.h"
#include "RandomOn.h"

RandomOn::RandomOn(){
  this -> reset();
}

void RandomOn::reset(){
  onCount = 1;
  lastRun = 0;
  cycleTime = 500;
}

void RandomOn::run(Sign &sign, uint8_t layer){
  if(! this -> shouldRun() ){return;};

  uint16_t seg_count = sign.segmentCount();
  this -> off(sign);
  for(uint8_t i = 0; i < onCount; i++){
    uint8_t rand = random(0,seg_count);
    sign.segments[rand] -> isOn = true;
  }
}

bool RandomOn::pushChar(char character, uint8_t ci){
  int32_t val = 0;
  const uint8_t periodStep = 25;

  if( this -> useCharForTiming(character) ){ return true;};

  switch(character){
    case 'k': val = cycleTime -= periodStep; break;
    case 'j': val = cycleTime += periodStep; break;
    case ']': val = (onCount++); break;
    case '[': val = (onCount--); break;
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
