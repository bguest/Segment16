#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdint.h>
#include "Pixel.h"

class Segment {
  public:
    Segment(uint8_t length);
    Pixel pixels[];
    bool isOn;
    uint16_t pixelCount();
    void toArray(CRGB array[], uint16_t &currIdx);

  private:
    uint8_t _length;
};

#endif

