#ifndef EFFECTS_H
#define EFFECTS_H

#include "Sign.h"

#define BASIC_TYPING 0
#define TEXT_EFFECTS_COUNT 1

#define SOLID_COLORS 0
#define COLOR_EFFECTS_COUNT 1

class Effects {
  public:
    Effects();
    bool pushChar(uint32_t character);
    uint8_t textEffect;
    uint8_t colorEffect;
    uint8_t bgColorEffect;
    void run(Sign &sign);
  private:
    void increaseHue();
    void bgIncreaseHue();
    void bgIncreaseValue();
    void bgDecreaseValue();
    void basicTyping(Sign &sign);
    void solidColor(Sign &sign);
    void bgSolidColor(Sign &sign);
    CHSV color;
    CHSV bgColor;
};

#endif
