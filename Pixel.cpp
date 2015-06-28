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


uint8_t Pixel::x(){
  return coords[0];
}
void Pixel::setX(uint8_t x){
  coords[0] = x;
}
uint8_t Pixel::y(){
  return coords[1];
}
void Pixel::setY(uint8_t y){
  coords[1] = y;
}

void Pixel::setXY(uint8_t xy[2]){
  coords[0] = xy[0];
  coords[1] = xy[1];
}
