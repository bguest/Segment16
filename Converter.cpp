#include "Converter.h"

uint16_t binarySegsForChar(char character){
  uint16_t rtn = 0;
  switch(character){
    case 'a': case 'A':
            //0123456789012345
      rtn = 0b1111001100000011; break;
    case 'b': case 'B':
            //0123456789012345
      rtn = 0b1101111100001001; break;
  }
  return rtn;
}

