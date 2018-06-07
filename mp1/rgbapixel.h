#ifndef RGBAPixel_H
#define RGBAPixel_H

#include <cstdint>
using std::uint8_t;

class RGBAPixel{
public:
        uint8_t red, green, blue, alpha;
        RGBAPixel();
        RGBAPixel(uint8_t, uint8_t, uint8_t);
};

#endif
