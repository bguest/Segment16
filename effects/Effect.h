#ifndef EFFECT_H
#define EFFECT_H

#define LAYER_COUNT 2     // 0: Foreground 1:Background

#include "Sign.h"

class Effect{
  public:
    Effect();
    virtual bool pushChar(char character, uint8_t layer);
    virtual void reset();
    virtual void signWasUpdated(Sign &sign);
    virtual void run(Sign &sign, uint8_t layer);
    void off(Sign &sign);
  protected:
    bool shouldRun();
    bool useCharForTiming(char character);
    unsigned long lastRun;
    uint16_t cycleTime;
};
#endif
