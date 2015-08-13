#include "Pixel.h"

Pixel::Pixel(){
  color = CHSV();
};

void Pixel::setColor(CHSV clr){
  hsvColor[0] = clr.hue << 8;
  hsvColor[1] = clr.sat << 8;
  hsvColor[2] = clr.val << 8;

  color = clr;
}

void Pixel::setHue16(uint16_t hue){
  hsvColor[0] = hue;
}

void Pixel::addHue16(int16_t deltaHue){
  hsvColor[0] += deltaHue;
}

uint16_t Pixel::getHue16(){
  return hsvColor[0];
}

CHSV Pixel::getColor(){
  color.hue = (hsvColor[0] >> 8);
  color.sat = (hsvColor[1] >> 8);
  color.val = (hsvColor[2] >> 8);
  return color;
}
