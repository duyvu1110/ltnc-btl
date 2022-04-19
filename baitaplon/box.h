#ifndef BOX__H
#define BOX__H

#include <iostream>
#include <SDL.h>

using namespace std;

const int RECT_SIZE = 30;

struct Plane {
    int x;
    int y;
    int w;
    int h;
    int dx;
    int dy;
    int health;
    SDL_Texture* texture;
};


#endif
