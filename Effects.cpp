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
  sign.textChanged = false;

  textEffect -> run(sign, 0);

  for(uint8_t i=0; i<LAYER_COUNT; i++){
    colorEffect[i] -> run(sign, i);
  }
}

void Effects::pushChar(char character){

  switch(character){
    case '2':
      curLayer = LETTERS_LAYER;
      Serial.println("Layer 2: Letters");
      Serial1.print("Layer 2: Letters\n");
      return;
    case '1':
      curLayer = BACKGROUND_LAYER;
      Serial.println("Layer 1: Background");
      Serial1.print("Layer 1: Background\n");
      return;
  }

  if( textEffect -> pushChar(character, 0) ){ return; }
  if( colorEffect[curLayer] -> pushChar(character, curLayer) ){ return; }

  int32_t val = 0;
  switch(character){
    case 'R':
      Serial1.print("RESET\n");
      this -> reset(); break;

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
  String desc;
  switch(cTextEffect){
    case RANDOM_ON:
      textEffect = &randomOn;
      desc = "Random, use:[]kj";
      break;
    case BASIC_TYPING:
      textEffect = &basicTyping;
      desc = "Basic Typing";
      break;
    case COUNTER:
      textEffect = &counter;
      desc = "Counter, use:[]kj";
      break;
    default:
      textEffect = &nullEffect;
      desc = "ERROR";
  }
  Serial.println(desc);
  Serial1.print(desc);
  Serial1.print('\n');
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
      Serial1.print("Solid Color\n");
      Serial.println("Solid Color");
      break;
    case RANDOM_FADE:
      colorEffect[ci] = &randomFade;
      Serial1.print("Random Fade\n");
      Serial.println("Random Fade");
      break;
    case SOLID_FADE:
      colorEffect[ci] = &solidFade;
      Serial.println("Solid Fade");
      Serial1.print("Solid Fade\n");
      break;
  }
}

