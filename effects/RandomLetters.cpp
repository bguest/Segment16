#include "Effect.h"
#include "RandomLetters.h"

RandomLetters::RandomLetters(){
  this -> reset();
}

void RandomLetters::reset(){
  lastRun = 0;
  cycleTime = 500;
}

void RandomLetters::run(Sign &sign, uint8_t layer){
  if(! this -> shouldRun() ){return;};
  sign.textChanged = true;
  uint8_t letters_count = sign.letterCount();
  char random_char;

  for(uint8_t i=0; i < letters_count; i++){
    random_char = 'A' + random(25);
    sign.letters[i] -> setChar(random_char);
  }

}

bool RandomLetters::pushChar(char character, uint8_t ci){
  int32_t val = 0xFFFF;
  String desc;
  const uint8_t periodStep = 25;

  if( this -> useCharForTiming(character) ){ return true;};

  switch(character){
    case 'k': val = cycleTime -= periodStep;
              desc = CYCLE_TIME_STR; break;
    case 'j': val = cycleTime += periodStep;
              desc = CYCLE_TIME_STR; break;
  }

  return( this ->usedSetting(desc, val) );
}
