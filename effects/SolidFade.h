#ifndef SOLID_FADE_H
#define SOLID_FADE_H

#include "Effect.h"

class SolidFade : public Effect{
  public:
    SolidFade();
    void reset();
    void run(Sign &sign, uint8_t layer);
    bool pushChar(char character, uint8_t layer);
  private:
    CHSV color[LAYER_COUNT];
    uint16_t fadeHue[LAYER_COUNT];
    uint16_t fadeSpeed[LAYER_COUNT];

    int16_t incSegSpeed(bool isPositive, uint8_t layer);
};
#endif