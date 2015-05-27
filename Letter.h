#ifndef LETTER_H
#define LETTER_H

#include <stdint.h>
#include "Converter.h"
#include "Segment.h"

/**Represents a sixteen segment single letter, it looks like this
#
#  --- 0 --- --- 1 ---
# |\        |        /|
# | \       |       / |
# |  \      |      /  |
# |   \     |     /   |
# 7    8   11   12    2
# |     \   |   /     |
# |      \  |  /      |
# |       \ | /       |
# |        \|/        |
#  -- 14 --- --- 15 --
# |        /|\        |
# |       / | \       |
# |      /  |  \      |
# |     /   |   \     |
# 6   13   10    9    3
# |   /     |     \   |
# |  /      |      \  |
# | /       |       \ |
# |/        |        \|
#  --- 5 --- --- 4 ---
#
# NOTE: These are the segment numbers
*/

class Letter {

  public:
    Letter();
    Letter(uint8_t lengths[16]);
    Segment *segments[16];
    uint16_t pixelCount();
    void toArray(CRGB array[], uint16_t &currIdx);
    void setChar(char character);

  private:
    uint8_t _lengths[16];
    char currentChar;
};
#endif
