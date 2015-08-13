#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdint.h>
#include "Pixel.h"

class Segment {
  public:
    Segment();
    Segment(uint8_t length);
    Pixel *pixels[4];
    bool isOn;
    uint16_t pixelCount();
    void toArray(CRGB array[], uint16_t &currIdx);
    void setColor(CHSV color);
    void setColor(uint8_t layer, CHSV color);

  private:
    uint8_t _length;
};

#endif

