#include "Counter.h"

Counter::Counter(){
  this -> reset();
}

void Counter::reset(){
  step = 1;
  count = 0;
}

void Counter::run(Sign &sign, uint8_t layer){
  this -> off(sign);
  if( step != 0 ){ sign.textChanged = true; }

  count += step;
  uint8_t letter_count = sign.letterCount();

  uint8_t devisor = 1;
  for(uint8_t i = 0; i<letter_count; i++){
    devisor *= 10;
  }
  uint16_t remainder = count % devisor;
  uint8_t display;

  // Set Characters
  for(uint8_t i=letter_count; i>0; i--){
    display = remainder % 10;
    sign.letters[i-1] -> setChar(char(display+'0'));
    remainder /= 10;
  }
}

bool Counter::pushChar(char character, uint8_t ci){
  int32_t val = 0xFFFF;
  String desc;

  switch(character){
    case ']': val = ++step;
      desc = STEP_SIZE_STR; break;
    case '[': val = --step;
      desc = STEP_SIZE_STR; break;
  }
  return( usedSetting(desc, val) );
}
