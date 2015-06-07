#ifndef BASIC_TYPING_H
#define BASIC_TYPING_H

#include "Effect.h"

class BasicTyping : public Effect{

  public:
    BasicTyping();
    void run(Sign &sign, uint32_t clock, uint8_t layer);
};

#endif
