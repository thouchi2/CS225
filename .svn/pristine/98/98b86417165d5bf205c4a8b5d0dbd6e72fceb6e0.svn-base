#include "scene.h"
#include "image.h"
#include <iostream>
using namespace std;

Scene::Scene(int max){
	pic = new Image*[max];
	this->max = max;
	xc = new int[max];
	yc = new int[max];
	for(int i = 0; i < max; i++){
		pic[i] = NULL;
    xc[i] = 0;
    xc[i] = 0;
  }
}

Scene::~Scene(){
	_clear();
}

Scene::Scene(const Scene &source){
	_copy(source);
}

void Scene::_clear(){
	for(int i = 0; i < max; i++){
		if(pic[i] != NULL){
			delete pic[i];
			pic[i] = NULL;
		}
	}
	delete[] pic;
	delete[] xc;
	delete[] yc;
	pic = NULL;
	xc = NULL;
	yc = NULL;
}

void Scene::_copy(const Scene &source){
	this->max = source.max;
	pic = new Image*[max];
	xc = new int[max];
	yc = new int[max];
	for(int i = 0; i < max; i++){
		if(source.pic[i] == NULL)
      pic[i] = NULL;
    else
      pic[i] = new Image(*source.pic[i]);
    xc[i] = source.xc[i];
    yc[i] = source.yc[i];
    }
  }

const Scene & Scene::operator = (const Scene & source){
	if(this != &source){
		_clear();
		_copy(source);
	}
	return *this;
}

void Scene::changemaxlayers(int newmax){
	if(max > newmax){
		for(int i = newmax; i < max; i++){
			if(pic[i] != NULL){
				cout << "invalid newmax" << endl;
				return;
			}
		}
	}
	if(newmax == max)
		return;

  Image ** npic = new Image*[newmax];
	int * nxc = new int[newmax];
	int * nyc = new int[newmax];

	if(newmax > max){
		for(int i = 0; i < max; i++){
			npic[i] = pic[i];
			nxc[i] = xc[i];
			nyc[i] = yc[i];
		}
		for(int i = max; i < newmax; i++){
			npic[i] = NULL;
			nxc[i] = 0;
			nyc[i] = 0;
		}
	}
	else{
		for(int i = 0; i < newmax; i++){
			npic[i] = pic[i];
			nxc[i] = xc[i];
			nyc[i] = yc[i];
		}
	}
	delete[] pic;
	delete[] xc;
	delete[] yc;
	max = newmax;
	pic = new Image *[ max];
	xc = new int[max];
	yc = new int[max];
	for(int i = 0; i < max; i++){
		pic[i] = npic[i];
		xc[i] = nxc[i];
		yc[i] = nyc[i];
	}
	delete[] npic;
	delete[] nxc;
	delete[] nyc;
	npic = NULL;
	nxc = NULL;
	nyc = NULL;
}

void Scene::addpicture(const char *FileName, int index, int x, int y){
	if(index >= max || index < 0){
		cout << "index out of bounds" << endl;
		return;
	}
	if(pic[index]!= NULL){
		delete pic[index];
		pic[index] = NULL;
	}
	Image *im = new Image();
	im->readFromFile(FileName);
	pic[index] = im;
	xc[index] = x;
	yc[index] = y;
}

void Scene::changelayer(int index, int newindex){
	if(index >= max || newindex >= max || index < 0 || newindex < 0)
		cout << "invalid index" << endl;
	else if(index != newindex){
		if(pic[newindex] != NULL){
			delete pic[newindex];
			pic[newindex] = NULL;
		}
		pic[newindex] = pic[index];
		pic[index] = NULL;
		xc[newindex] = xc[index];
		yc[newindex] = yc[index];
	}
}

void Scene::translate(int index, int xcoord, int yc){
	if(index >= 0 && index < max && pic[index] != NULL){
    this->xc[index] = xcoord;
    this->yc[index] = yc;
  }
	else{
		cout << "invalid index" << endl;
    return;
  }
}

void Scene::deletepicture(int index){
	if((index >= 0 && index < max) && (pic[index] != NULL)){
    delete pic[index];
    pic[index] = NULL;
  }
  else
    cout << "invalid index" << endl;
}

Image * Scene::getpicture(int index) const{
  if((index < max && index >= 0) && (pic[index] != NULL))
    return pic[index];
  else{
    cout << "invalid index" << endl;
    return NULL;
  }
}

Image Scene::drawscene() const{
	int width = 0;
	int height = 0;
	for(int i = 0; i < max; i++){
		if(pic[i] != NULL){
			if(xc[i] + (int)((*pic[i]).width()) > width)
				width = xc[i] + (int)((*pic[i]).width());
			if(yc[i] + (int)((*pic[i]).height()) > height)
				height = yc[i] + (int)((*pic[i]).height());
		}
	}
	Image im;
	im.resize(width,height);
	for(int i = 0; i < max; i++){
		if(pic[i] != NULL){
			for(int x = 0; x < ((int)(*pic[i]).width()); x++){
				for(int y = 0; y < ((int)(*pic[i]).height()); y++){
					*im(xc[i] + x, yc[i] + y) = *(*pic[i])(x,y);
				}
			}
		}
	}
	return im;
}
