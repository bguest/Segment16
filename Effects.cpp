#define HUE_STEP 1
#define VALUE_STEP 5
#define PERIOD_STEP 3

#define LETTERS_LAYER 0
#define BACKGROUND_LAYER 1

#include "Effects.h"
#include "effects/Effect.cpp"
#include "effects/RandomOn.cpp"
#include "effects/Counter.cpp"
#include "effects/BasicTyping.cpp"
#include "effects/SolidColor.cpp"
#include "effects/SolidFade.cpp"
#include "effects/RandomFade.cpp"
#include "effects/RandomLetters.cpp"
#include "effects/RainbowLetter.cpp"
#include "effects/RainbowSegment.cpp"

const uint16_t CYCLE_TIME = 5;

Effects::Effects(){
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    colorEffect[i] = &solidColor;
    cColorEffect[i] = SOLID_COLORS;
  }
  cTextEffect = BASIC_TYPING;
  textEffect = &basicTyping;
  this -> reset();
}

void Effects::run(Sign &sign){
  unsigned long time = millis();
  if(time - lastRun < CYCLE_TIME){ return; }
  lastRun = time;

  if(changeText){
    changeText = false;
    sign.textChanged = true;
  }else{
    sign.textChanged = false;
  }

  if( time - textLastRun > textCycleTime ||
      textEffect == &basicTyping){
    textEffect -> run(sign, 0);
    textLastRun = time;
  }

  for(uint8_t i=0; i<LAYER_COUNT; i++){
    colorEffect[i] -> run(sign, i);
  }
}

void Effects::pushChar(char character){
  const uint8_t periodStep = 25;

  switch(character){
    case '2':
      curLayer = LETTERS_LAYER;
      Serial.println("Layer 2: Letters");
      Serial1.print("\nLayer 2: Letters");
      return;
    case '1':
      curLayer = BACKGROUND_LAYER;
      Serial.println("Layer 1: Background");
      Serial1.print("\nLayer 1: Background");
      return;
  }

  if( textEffect -> pushChar(character, 0) ){ return; }
  if( colorEffect[curLayer] -> pushChar(character, curLayer) ){ return; }

  int32_t val = 0xFFFF;
  String desc;

  switch(character){
    case 'R':
      Serial1.print("\nRESET");
      this -> reset(); break;

    case 'k': val = (textCycleTime -= periodStep);
              desc = CYCLE_TIME_STR; break;
    case 'j': val = (textCycleTime += periodStep);
              desc = CYCLE_TIME_STR; break;

    case 't': textLastRun = 0; lastRun = 0;
              changeText = true; break;
    case 'g': textLastRun = millis(); break;

    case '.': this -> prevTextEffect(); break;
    case ',': this -> nextTextEffect(); break;

    case 'l': this -> prevColorEffect(curLayer); break;
    case 'h': this -> nextColorEffect(curLayer); break;
    case 'I': this -> invertColors(); break;
  }

  usedSetting(desc, val);
}

// Called when new letters pushed to sign
void Effects::signWasUpdated(Sign &sign){
  textLastRun = 0;
  this -> run(sign);
  textEffect -> signWasUpdated(sign);

  colorEffect[0] -> signWasUpdated(sign);
  if(colorEffect[0] != colorEffect[1]){
    colorEffect[1] -> signWasUpdated(sign);
  }
}

void Effects::reset(){
  curLayer = 0;
  lastRun = 0;
  textLastRun = 0;
  textCycleTime = 500;
  changeText = false;

  textEffect -> reset();
  for(uint8_t i=1; i<LAYER_COUNT; i++){
    colorEffect[i] -> reset();
  }
}

uint8_t Effects::nextTextEffect(){
  cTextEffect++;
  cTextEffect = cTextEffect % TEXT_EFFECTS_COUNT;
  this -> updateTextEffect();
  return cTextEffect;
}

uint8_t Effects::prevTextEffect(){
  cTextEffect--;
  cTextEffect = cTextEffect % TEXT_EFFECTS_COUNT;
  this -> updateTextEffect();
  return cTextEffect;
}

void Effects::updateTextEffect(){
  String desc;
  switch(cTextEffect){
    case RANDOM_ON:
      textEffect = &randomOn;
      desc = "Random Segs,\nkeys:[]kjor";
      break;
    case BASIC_TYPING:
      textEffect = &basicTyping;
      desc = "Basic Typing";
      break;
    case COUNTER:
      textEffect = &counter;
      desc = "Counter\nkeys:[]kj";
      break;
    case RANDOM_LETTERS:
      textEffect = &randomLetters;
      desc = "Random Letters\nkeys:kj";
      break;
    default:
      textEffect = &nullEffect;
      desc = "ERROR";
  }
  Serial.println(desc);
  Serial1.print('\n');
  Serial1.print(desc);
}

uint8_t Effects::nextColorEffect(uint8_t ci){
  cColorEffect[ci]++;
  cColorEffect[ci] = cColorEffect[ci] % COLOR_EFFECTS_COUNT;
  this -> updateColorEffect(ci);
  return cColorEffect[ci];
}
uint8_t Effects::prevColorEffect(uint8_t ci){
  if(cColorEffect[ci] == 0){
    cColorEffect[ci] = COLOR_EFFECTS_COUNT - 1;
  }else{
    cColorEffect[ci]--;
    cColorEffect[ci] = cColorEffect[ci] % COLOR_EFFECTS_COUNT;
  }
  this -> updateColorEffect(ci);
  return cColorEffect[ci];
}

void Effects::updateColorEffect(uint8_t ci){
  String desc;
  switch(cColorEffect[ci]){
    case SOLID_COLORS:
      colorEffect[ci] = &solidColor;
      desc = "Solid Color\nKeys:cCvVbB";
      break;
    case RANDOM_FADE:
      colorEffect[ci] = &randomFade;
      desc = "Random Fade\nKeys:cCvVbBfsFS";
      break;
    case SOLID_FADE:
      colorEffect[ci] = &solidFade;
      desc = "Solid Fade\nKeys:cCvVbBfs";
      break;
    case RAINBOW_LETTER:
      colorEffect[ci] = &rainbowLetter;
      desc = "Rainbow Letter\nKeys:cCvVbBrefsd";
      break;
    case RAINBOW_SEGMENT:
      colorEffect[ci] = &rainbowSegment;
      desc = "Rainbow Segment\nKeys:cCvVbBrefsd";
      break;
  }
  Serial.println(desc);
  Serial1.print('\n');
  Serial1.print(desc);
}

void Effects::invertColors(){
  uint8_t cTemp = cColorEffect[0];
  cColorEffect[0] = cColorEffect[1];
  cColorEffect[1] = cTemp;

  this -> updateColorEffect(0);
  this -> updateColorEffect(1);

  colorEffect[0] -> invertColors();
  if(colorEffect[0] != colorEffect[1]){ //Prevent Double Flip
    colorEffect[1] -> invertColors();
  }

  usedSetting(INVERTED_STR, 0);
}

