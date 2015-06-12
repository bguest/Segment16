#ifndef EFFECTS_H
#define EFFECTS_H

#include "Sign.h"
#include "effects/Effect.h"
#include "effects/RandomOn.h"
#include "effects/BasicTyping.h"
#include "effects/SolidColor.h"
#include "effects/SolidFade.h"
#include "effects/RandomFade.h"

#define BASIC_TYPING 0
#define RANDOM_ON 1
#define TEXT_EFFECTS_COUNT 2

#define SOLID_COLORS 0
#define SOLID_FADE 1
#define RANDOM_FADE 2
#define COLOR_EFFECTS_COUNT 3


class Effects {
  public:
    Effects();
    void pushChar(char character);
    void signWasUpdated(Sign &sign);
    void run(Sign &sign);

  private:
    RandomOn randomOn;
    BasicTyping basicTyping;
    SolidColor solidColor;
    RandomFade randomFade;
    SolidFade solidFade;
    Effect nullEffect;
    uint8_t curLayer;

    uint8_t cTextEffect;
    Effect *textEffect;
    uint8_t cColorEffect[LAYER_COUNT];
    Effect *colorEffect[LAYER_COUNT];

    unsigned long lastRun;
    uint16_t cycleTime;

    void reset();
    void setDefaults();

    uint8_t nextTextEffect();
    uint8_t prevTextEffect();
    void updateTextEffect();

    uint8_t nextColorEffect(uint8_t layer);
    uint8_t prevColorEffect(uint8_t layer);
    void updateColorEffect(uint8_t layer);

    //int16_t increaseSpeed(uint8_t layer);
    //int16_t decreaseSpeed(uint8_t layer);
    //int16_t incSegSpeed(bool isPositive, uint8_t layer);
    //int16_t incRandomSpeed(bool isPositive, uint8_t layer);

    //void basicTyping(Sign &sign); // TEXT EFFECTS
    //void randomOn(Sign &sign);
    //void off(Sign &sign);

    //void solidColor(Sign &sign, uint8_t layer);  // Color Effects
    //void solidFade(Sign &sign, uint8_t layer);
    //void randomFade(Sign &sign, uint8_t layer);
    //void recalculateSpeeds(Sign &sign);
};

#endif
