#ifndef SEGMENT_16_H
#define SEGMENT_16_H

#include "Arduino.h"
#include <FastLED.h>
#include "Sign.h"
#include "Effects.h"

class Segment16 {
  public:
    Segment16();
    Sign sign;
    CRGB *leds;
    void show(void);

  private:
    Effects effects;
};

#endif