#define HUE_STEP 5
#define VALUE_STEP 5
#define PERIOD_STEP 3

#include "Effects.h"
#include "effects/Effect.cpp"
#include "effects/RandomOn.cpp"
#include "effects/Counter.cpp"
#include "effects/BasicTyping.cpp"
#include "effects/SolidColor.cpp"
#include "effects/SolidFade.cpp"
#include "effects/RandomFade.cpp"

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

  textEffect -> run(sign, 0);

  for(uint8_t i=0; i<LAYER_COUNT; i++){
    colorEffect[i] -> run(sign, i);
  }
}

void Effects::pushChar(char character){

  switch(character){
    case '2':
      curLayer = 0;
      Serial.println("Layer 2: Letters");
      return;
    case '1':
      curLayer = 1;
      Serial.println("Layer 1: Background");
      return;
  }

  if( textEffect -> pushChar(character, 0) ){ return; }
  if( colorEffect[curLayer] -> pushChar(character, curLayer) ){ return; }

  int32_t val = 0;
  switch(character){
    case 'R': this -> reset(); break;

    case '<': val = this -> prevTextEffect(); break;
    case '>': val = this -> nextTextEffect(); break;

    case 'l': val = this -> prevColorEffect(curLayer); break;
    case 'h': val = this -> nextColorEffect(curLayer); break;

  }
  Serial.print(character);
  Serial.print(": ");
  Serial.print(val);
  Serial.println(" ");
}

// Called when new letters pushed to sign
void Effects::signWasUpdated(Sign &sign){
  this -> run(sign);
  textEffect -> signWasUpdated(sign);
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    colorEffect[i] -> signWasUpdated(sign);
  }
}

void Effects::reset(){
  curLayer = 0;
  lastRun = 0;
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
  switch(cTextEffect){
    case RANDOM_ON:
      textEffect = &randomOn;
      Serial.println("Random On, keys: []kj");
      break;
    case BASIC_TYPING:
      textEffect = &basicTyping;
      Serial.println("Basic Typing");
      break;
    case COUNTER:
      textEffect = &counter;
      Serial.println("Counter, keys:[]kj");
      break;
    default:
      textEffect = &nullEffect;
      Serial.println("ERROR");
  }
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
  switch(cColorEffect[ci]){
    case SOLID_COLORS:
      colorEffect[ci] = &solidColor;
      Serial.println("Solid Color");
      break;
    case RANDOM_FADE:
      colorEffect[ci] = &randomFade;
      Serial.println("Random Fade");
      break;
    case SOLID_FADE:
      colorEffect[ci] = &solidFade;
      Serial.println("Solid Fade");
      break;
  }
}

