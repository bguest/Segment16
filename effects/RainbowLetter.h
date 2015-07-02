#ifndef RAINBOW_LETTER_H
#define RAINBOW_LETTER_H

#include "Effect.h"

class RainbowLetter : public Effect{
  public:
    RainbowLetter();
    void reset();
    void run(Sign &sign, uint8_t layer);
    bool pushChar(char character, uint8_t layer);
    void signWasUpdated(Sign &sign);

  private:
    bool isStatic;
    int8_t hueStep[LAYER_COUNT];
    CHSV color[LAYER_COUNT];
};
#endif