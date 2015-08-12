#ifndef COUNTER_H
#define COUNTER_H

#include "Effect.h"
class Counter : public Effect{
  public:
    Counter();
    void reset();
    void run(Sign &sign, uint8_t layer);
    bool pushChar(char character, uint8_t layer);
    void randomize(uint8_t ci);
  private:
    int8_t step;
    uint32_t count;
};

#endif
