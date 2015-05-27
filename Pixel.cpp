#include "Pixel.h"

Pixel::Pixel(){
  color = CRGB::Black;
};

void Pixel::setColor(CRGB clr){
  color = clr;
}

CRGB Pixel::getColor(){
  return color;
}
