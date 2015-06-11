#include "Counter.h"

Counter::Counter(){
  this -> reset();
}

void Counter::reset(){
  lastRun = 0;
  cycleTime = 500;
  step = 1;
  count = 0;
}

void Counter::run(Sign &sign, uint8_t layer){
  if(! this -> shouldRun() ){return;};
  this -> off(sign);

  count += step;
  uint8_t letterCount = sign.letterCount();
  uint8_t remainder = count % letterCount;
  uint8_t display;
  while(remainder){
    display = remainder % 10;
    sign.pushChar(display + '0');
    remainder /= 10;
  }
}

bool Counter::pushChar(char character, uint8_t ci){
  if( this -> useCharForTiming(character) ){ return true;};
  int32_t val = 0;
  const uint8_t periodStep = 25;

  switch(character){
    case 'k': val = cycleTime -= periodStep; break;
    case 'j': val = cycleTime += periodStep; break;
    case ']': val = (step++); break;
    case '[': val = (step--); break;
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
