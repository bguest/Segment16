#ifndef RANDOM_FADE_H
#define RANDOM_FADE_H

#include "Effect.h"

class RandomFade : public Effect{
  public:
    RandomFade();
    void reset();
    void run(Sign &sign, uint32_t clock, uint8_t layer);
    bool pushChar(char character, uint8_t layer);
    void signWasUpdated(Sign &sign);
  private:
    CHSV color[LAYER_COUNT];
    uint16_t fadeSpeed[LAYER_COUNT];
    uint16_t segHue[16*LETTERS_COUNT];
    int16_t  segSpeed[16*LETTERS_COUNT];
    uint16_t fadeTime;

    int16_t incRandomSpeed(bool isPositive, uint8_t layer);
    void recalculateSpeeds(Sign &sign);
};
#endif
