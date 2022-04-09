#ifndef BOX__H
#define BOX__H

#include <iostream>
#include <SDL.h>

using namespace std;

const int RECT_SIZE = 30;

struct Plane {
   float x;
    float y;
    float dx;
    float dy;
    int health;
    int w;
    int h;
    int reload;
    SDL_Texture* texture;
};


#endif
