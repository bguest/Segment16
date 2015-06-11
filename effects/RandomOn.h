#ifndef RANDOM_ON_H
#define RANDOM_ON_H

#include "Effect.h"

class RandomOn : public Effect{

  public:
    RandomOn();
    void reset();
    void run(Sign &sign, uint8_t layer);
    bool pushChar(char character, uint8_t layer);

  private:
    uint8_t onCount;
    uint32_t period;

};
#endif
