#ifndef PIXEL_H
#define PIXEL_H

#include "FastLED.h"

class Pixel {

  public:
    Pixel();
    void setColor(CHSV color);
    void setHue16(uint16_t hue);
    void addHue16(int16_t deltaHue);
    uint16_t getHue16();
    CHSV getColor();

  private:
    uint16_t hsvColor[3];
    CHSV color;
};
#endif
