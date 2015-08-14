#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdint.h>
#include "Pixel.h"

#define VERTICAL 0
#define HORIZONTAL 1
#define DIAGONAL_RIGHT 2
#define DIAGONAL_LEFT 3
#define ORIENTATION_COUNT 4

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
    uint8_t index;
    char orientation();

  private:
    uint8_t _length;
};

#endif

