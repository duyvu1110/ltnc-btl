#include <SDL.h>

using namespace std;

//const int RECT_SIZE = 30;

struct Fruits {
    int Fruitsx;
    int Fruitsy;

    void drawF(SDL_Renderer* renderer) {
        SDL_Rect rect;
        rect.x = Fruitsx;
        rect.y = Fruitsy;
        rect.w = RECT_SIZE;
        rect.h = RECT_SIZE;

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        SDL_RenderDrawRect(renderer, &rect);
    }
};


