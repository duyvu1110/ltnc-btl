#ifndef BOX__H
#define BOX__H

#include <iostream>
#include <SDL.h>

using namespace std;

const int RECT_SIZE = 30;

struct Plane {
    float x;
    float y;
    float w;
    float h;
    int health;
    SDL_Texture* texture;
};


#endif
