#ifndef EFFECT_H
#define EFFECT_H

#define LAYER_COUNT 2     // 0: Foreground 1:Background

#include "Sign.h"

const String CYCLE_TIME_STR = "(1/Tempo)";
const String STEP_SIZE_STR = "Step Size";
const String HUE_STR = "Hue";
const String SAT_STR = "Saturation";
const String VAL_STR = "Value";

class Effect{
  public:
    Effect();
    virtual bool pushChar(char character, uint8_t layer);
    virtual void reset();
    virtual void signWasUpdated(Sign &sign);
    virtual void run(Sign &sign, uint8_t layer);

  protected:
    void off(Sign &sign);
    bool usedSetting(String desc, int32_t val);
    bool shouldRun();
    bool useCharForTiming(char character);
    unsigned long lastRun;
    uint16_t cycleTime;
};
#endif
