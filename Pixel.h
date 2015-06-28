#ifndef PIXEL_H
#define PIXEL_H

#include "FastLED.h"

class Pixel {

  public:
    Pixel();
    void setColor(CRGB color);
    CRGB getColor();
    uint8_t coords[2];
    uint8_t x();
    void setX(uint8_t x);
    uint8_t y();
    void setY(uint8_t y);
    void setXY(uint8_t xy[2]);
  private:
    CRGB color;
};
#endif
