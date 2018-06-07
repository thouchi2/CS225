#include "image.h"

void Image::invertcolors(){

  for(int x = 0; x < (int)this->width(); x++){
    for(int y = 0; y < (int)this->height(); y++){

      (*this)(x,y)->red = 255 - (*this)(x,y)->red;
      (*this)(x,y)->green = 255 - (*this)(x,y)->green;
      (*this)(x,y)->blue = 255 - (*this)(x,y)->blue;
    }
  }
}

void Image::adjustbrightness(int r, int g, int b){
  for(int x = 0; x < (int)this->width(); x++){
    for(int y = 0; y < (int)this->height(); y++){

      if((*this)(x,y)->red + r < 0)
        (*this)(x,y)->red = 0;
      else if((*this)(x,y)->red + r > 255)
        (*this)(x,y)->red = 255;
      else
        (*this)(x,y)->red += r;

      if((*this)(x,y)->green + g < 0)
        (*this)(x,y)->green = 0;
      else if((*this)(x,y)->green + g > 255)
        (*this)(x,y)->green = 255;
      else
        (*this)(x,y)->green += g;

      if((*this)(x,y)->blue + b < 0)
        (*this)(x,y)->blue = 0;
      else if((*this)(x,y)->blue + b > 255)
        (*this)(x,y)->blue = 255;
      else
        (*this)(x,y)->blue += b;
    }
  }
}

void Image::flipleft(){

  for(int y = 0; y < (int)this->height(); y++){
    for(int x = 0; x < (int)this->width()/2; x++){

      RGBAPixel* l = (*this)(x, y);
      RGBAPixel* r = (*this)(this->width() - 1 - x, y);
      RGBAPixel temp(l->red, l->green, l->blue);
      *l = *r;
      *r = temp;
    }
  }
}
