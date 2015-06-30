#ifndef EFFECT_H
#define EFFECT_H

#define LAYER_COUNT 2     // 0: Foreground 1:Background

#include "Sign.h"

const String CYCLE_TIME_STR = "(1/Tempo)";
const String FADE_TIME_STR = "Fade Time";
const String CONVERGE_TIME_STR = "Converge In";
const String STEP_SIZE_STR = "Step Size";
const String NUMBER_ON_STR = "Number On";
const String HUE_STR = "Color";
const String SAT_STR = "Vibrance";
const String VAL_STR = "Brightness";

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
