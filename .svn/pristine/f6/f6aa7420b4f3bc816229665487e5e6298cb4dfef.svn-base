#ifndef SCENE_H
#define SCENE_H

#include <cstdint>
#include "png.h"
#include "image.h"

class Scene{

  public:

  Scene(int max); //Initializes object to hold max images

  ~Scene(); //Frees dynamically allocated space

  Scene(const Scene &source); //Copy constructor - Independent copy

  const Scene& operator= (const Scene &source); //Assignment operator

  void changemaxlayers(int newmax); //Modifies size of array image pointers

  void addpicture(const char *FileName, int index, int x, int y); //Add picture to scene

  void changelayer(int index, int newindex); //Moves image

  void translate(int index, int xcoord, int ycoord); //Changes x and y coordinates

  void deletepicture(int index); //Deletes picture

  Image * getpicture (int index) const; //Returns ptr to index

  Image drawscene () const; //Draws whole scene

private:
  int max;
  Image ** pic;
  int * xc;
  int * yc;

  void _copy(const Scene & source);

  void _clear();

};

#endif
