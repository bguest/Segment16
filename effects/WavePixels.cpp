
#include "WavePixels.h"

WavePixels::WavePixels(){
  this -> reset();
}

void WavePixels::reset(){
  for(uint8_t i=0; i< LAYER_COUNT; i++){
    cycleTime[i] = 500;
    hueA[i] = INT16_MAX/8;
  }
}

void WavePixels::randomize(uint8_t ci){
  cycleTime[ci] = random16(10,2000);
  hueA[ci] = random16(INT16_MAX/4);
}

void WavePixels::run(Sign &sign, uint8_t ci){
  uint16_t angle = (millis() % cycleTime[ci])/cycleTime[ci] * UINT8_MAX;
  int16_t delta_hue = hueA[ci] * sin16(angle);
  uint16_t seg_count = sign.segmentCount();

  bool on = (ci == 0);

  for(uint8_t i=0; i < seg_count; i++){
    Segment currSeg = *sign.segments[i];
    currSeg.setColor(color[ci]);

    if(currSeg.isOn == on){
      uint8_t pixel_count = currSeg.pixelCount();

      for(uint8_t j = 0; j < pixel_count; j++ ){
        Pixel currPixel = *currSeg.pixels[j];
        currPixel.addHue16(delta_hue);
        delta_hue = -delta_hue;
      }
    }
  }

}


bool WavePixels::pushChar(char character, uint8_t ci){
  if( this -> useCharForColor(character, ci)){ return true; };

  int32_t val = 0xFFFF;
  String desc;

  const uint16_t ampStep = 100;
  const uint8_t cycleStep = 5;

  switch(character){
    case 'e': val = (hueA[ci] += ampStep);
              desc = HUE_AMP_STR; break;
    case 'E': val = (hueA[ci] -= ampStep);
              desc = HUE_AMP_STR; break;
    case 'f': val = (cycleTime[ci] -= cycleStep);
              desc = FADE_SPEED_STR; break;
    case 's': val = (cycleTime[ci] += cycleStep);
              desc = FADE_SPEED_STR; break;
  }

  return( usedSetting(desc, val) );
}
