#ifndef EFFECTS_H
#define EFFECTS_H

#include "Sign.h"

#define BASIC_TYPING 0

class Effects {
  public:
    Effects();
    uint8_t currentEffect;
    void run(Sign &sign);
  private:
    void basicTyping(Sign &sign);
};

#endif
