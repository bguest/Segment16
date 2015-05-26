#ifndef LETTER_H
#define LETTER_H

#include <stdint.h>
#include "Segment.h"

class Letter {

  public:
    Letter(uint8_t *lengths);
    Segment *segments[16];
    uint16_t pixelCount();
    void toArray(CRGB array[], uint16_t &currIdx);

  private:
    uint8_t _lengths[16];
};
#endif
