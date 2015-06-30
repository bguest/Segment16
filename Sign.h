#ifndef SIGN_H
#define SIGN_H

#define LETTERS_COUNT 2
#include "Letter.h"

class Sign{
  public:
    Sign();
    uint16_t pixelCount();
    uint8_t letterCount();
    uint16_t segmentCount();
    void pushChar(char);
    void pushChar(char, bool);
    Letter *letters[LETTERS_COUNT];
    Segment *segments[16*LETTERS_COUNT];
    char characters[LETTERS_COUNT];
    bool textChanged;

  private:
    uint16_t _pixel_count;
};
#endif
