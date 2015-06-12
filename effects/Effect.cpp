
#include "Effect.h"

//const String HueStrng = "Hue:";

Effect::Effect(){
}

void Effect::reset(){
}

void Effect::run(Sign &sign, uint32_t clock, uint8_t layer){
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

bool Effect::usedSetting(String desc, int32_t val){
  if(val != 0){
    Serial.print(desc);
    Serial.print(": ");
    Serial.print(val);
    Serial.println(" ");
    return true;
  }
  return false;
}
