#include <iostream>

#include "rgbapixel.h"
#include "png.h"

using namespace std;

/**
* Rotates an image 180 degrees
**/

PNG rotate(PNG png1){
  size_t width = png1.width();
  size_t height = png1.height();

  //horizontal flip
  for(size_t y = 0; y < height; y++){
    for(size_t x = 0; x < width/2; x++){
      RGBAPixel* l = png1(x, y);
      RGBAPixel* r = png1(width - 1 - x, y);
      RGBAPixel temp(l->red, l->green, l->blue);
      *l = *r;
      *r = temp;
    }
  }

  //verticle flip
  for(size_t x = 0; x < width; x++){
    for(size_t y = 0; y < height/2; y++){
      RGBAPixel* t = png1(x, y);
      RGBAPixel* b = png1(x, height - 1 - y);
      RGBAPixel temp(t->red, t->green, t->blue);
      *t = *b;
      *b = temp;
    }
  }

  return png1;
}

int main() {
  PNG image("in.png");

  image = rotate(image);

  image.writeToFile("out.png");

  return 0;
}
