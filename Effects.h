#ifndef EFFECTS_H
#define EFFECTS_H

#include "Sign.h"

#define BASIC_TYPING 0
#define RANDOM_ON 1
#define TEXT_EFFECTS_COUNT 2

#define SOLID_COLORS 0
#define SOLID_FADE 1
#define RANDOM_FADE 2
#define COLOR_EFFECTS_COUNT 3

#define LAYER_COUNT 2     // 0: Foreground 1:Background

class Effects {
  public:
    Effects();
    void pushChar(char character);
    void signWasUpdated(Sign &sign);
    uint8_t textEffect;
    uint8_t colorEffect[LAYER_COUNT];
    void run(Sign &sign);

  private:
    CHSV color[LAYER_COUNT];
    uint16_t fadeHue[LAYER_COUNT];
    uint16_t fadeSpeed[LAYER_COUNT];
    uint16_t segHue[16*LETTERS_COUNT];
    int16_t  segSpeed[16*LETTERS_COUNT];
    uint32_t period;
    uint32_t clock;
    uint8_t effectValue1;   // RandomOn count
    int16_t effectValue2;   // Cycles to Random Converge
    int16_t effectValue3;   // 

    void reset();
    void setDefaults();

    uint8_t nextTextEffect();
    uint8_t prevTextEffect();

    uint8_t nextColorEffect(uint8_t layer);
    uint8_t prevColorEffect(uint8_t layer);

    int16_t increaseSpeed(uint8_t layer);
    int16_t decreaseSpeed(uint8_t layer);
    int16_t incSegSpeed(bool isPositive, uint8_t layer);
    int16_t incRandomSpeed(bool isPositive, uint8_t layer);

    void basicTyping(Sign &sign); // TEXT EFFECTS
    void randomOn(Sign &sign);
    void off(Sign &sign);

    void solidColor(Sign &sign, uint8_t layer);  // Color Effects
    void solidFade(Sign &sign, uint8_t layer);
    void randomFade(Sign &sign, uint8_t layer);
    void recalculateSpeeds(Sign &sign);
};

#endif
