#ifndef PIXEL_H
#define PIXEL_H

#include "FastLED.h"

class Pixel {

  public:
    Pixel();
    void setColor(CRGB color);
    CRGB getColor();
  private:
    CRGB color;
};
#endif
