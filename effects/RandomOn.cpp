#include "Effect.h"
#include "RandomOn.h"

RandomOn::RandomOn(){
  this -> reset();
}

void RandomOn::reset(){
  period = 100;
}

void RandomOn::run(Sign &sign, uint32_t clock, uint8_t layer){
  uint16_t seg_count = sign.segmentCount();
  if( clock % period == 0){
    this -> off(sign);
    for(uint8_t i = 0; i < onCount; i++){
      uint8_t rand = random(0,seg_count);
      sign.segments[rand] -> isOn = true;
    }
  }
}

bool RandomOn::pushChar(char character, uint8_t ci){
  int32_t val = 0;
  switch(character){
    case 'k': val = period -= PERIOD_STEP; break;
    case 'j': val = period += PERIOD_STEP; break;
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
