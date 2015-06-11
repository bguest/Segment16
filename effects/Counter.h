#ifndef COUNTER_H
#define COUNTER_H

#include "Effect.h"
class Counter : public Effect{
  public:
    Counter();
    void reset();
    void run(Sign &sign, uint8_t layer);
    bool pushChar(char character, uint8_t layer);
  private:
    int8_t step;
    int8_t count;
};

#endif
