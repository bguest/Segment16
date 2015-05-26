#ifndef SEGMENT_16_H
#define SEGMENT_16_H

#include "Arduino.h"
#include <FastLED.h>
#include "Letter.h"

#define LETTERS_COUNT 2

class Segment16 {
  public:
    CRGB *leds;
    Segment16();
    uint16_t pixelCount();
    Letter *letters[LETTERS_COUNT];
    void show(void);

  private:
    uint16_t _pixel_count;
};

#endif
