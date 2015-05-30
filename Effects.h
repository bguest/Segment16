#ifndef EFFECTS_H
#define EFFECTS_H

#include "Sign.h"

#define BASIC_TYPING 0
#define RANDOM_ON 1
#define TEXT_EFFECTS_COUNT 2

#define SOLID_COLORS 0
#define HUE_FADE 1
#define COLOR_EFFECTS_COUNT 2

class Effects {
  public:
    Effects();
    void pushChar(char character);
    uint8_t textEffect;
    uint8_t colorEffect;
    uint8_t bgColorEffect;
    void run(Sign &sign);

  private:
    CHSV color;
    CHSV bgColor;
    uint32_t period;
    uint32_t clock;
    uint8_t effectValue1;   // RandomOn count
    int16_t effectValue2;   // Hue Step for color fade
    int16_t effectValue3;   // BG Hue Step for color fade

    void reset();
    void setDefaults();

    uint8_t nextTextEffect();
    uint8_t prevTextEffect();

    uint8_t nextColorEffect();
    uint8_t prevColorEffect();

    uint8_t nextBgColorEffect();
    uint8_t prevBgColorEffect();

    void basicTyping(Sign &sign); // TEXT EFFECTS
    void randomOn(Sign &sign);
    void off(Sign &sign);

    void solidColor(Sign &sign);
    void bgSolidColor(Sign &sign);
    void hueFade(Sign &sign);
    void bgHueFade(Sign &sign);

};

#endif
