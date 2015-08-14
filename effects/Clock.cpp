#include "Clock.h"

Clock::Clock(){
  this -> reset();
}

void Clock::reset(){
  isClock = true; //As Apposed to Timer
  is24Hour = false;
  stepTime = 1000;
  minutesOffset = 0;
  hoursOffset = 0;
  lastUpdated = 0;
}

void Clock::run(Sign &sign, uint8_t layer){
  unsigned long time = millis();
  if(time - lastUpdated < stepTime){ return; }
  this -> off(sign);
  lastUpdated = time;
  sign.textChanged = true;

  //Clock Math
  uint8_t hour_per_day = (is24Hour ? 24 : 12);
  uint8_t minutes_per = (isClock ? 60 : 100);

  unsigned long seconds = time/stepTime + minutesOffset*60 + hoursOffset*3600;
  uint8_t minutes = (seconds/60) % minutes_per;
  uint8_t hours = (seconds/3600) % hour_per_day;
  uint8_t display[2];

  if(isClock){
    display[0] = minutes;
    display[1] = hours;
  }else{
    display[0] = seconds % 60;
    display[1] = minutes;
  }

  uint8_t letterIdx = LETTERS_COUNT - 1;
  for(uint8_t set=0; set < 2; set++){
    uint8_t devisor = 100;
    uint8_t remainder = display[set] % devisor;
    uint8_t dspl;
    for(uint8_t ltr=2; ltr>0; ltr--){
      dspl = remainder % 10;
      sign.letters[letterIdx] -> setChar(char(dspl + '0'));
      letterIdx--;
      remainder /= 10;
    }
  }
}

bool Clock::pushChar(char character, uint8_t ci){
  int32_t val = 0xFFFF;
  String desc;
  String hours_off_str = F("Hours Offset");
  String minutes_off_str = F("Minimum Offset");
  String step_time_str = F("Millis / Second");

  switch(character){
    case 'u': val = 1; desc = RESET_STR; this->reset(); break;
    case ']': val = ++minutesOffset; desc = minutes_off_str; break;
    case '[': val = --minutesOffset; desc = minutes_off_str; break;
    case '}': val = ++hoursOffset; desc = hours_off_str; break;
    case '{': val = --hoursOffset; desc = hours_off_str; break;
    case 'K': val = --stepTime; desc = step_time_str; break;
    case 'J': val = ++stepTime; desc = step_time_str; break;
    case 'o': val = (isClock = !isClock); desc = F("Clock Mode"); break;
    case 'O': val = (is24Hour = !is24Hour); desc = F("24 Hour Time"); break;

  }
  return( usedSetting(desc, val) );
}
