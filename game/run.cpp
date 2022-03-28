#include <iostream>
#include <SDL.h>
#include "utils.h"
#include "game.h"
#include "params.h"

using namespace std;

void clearScreen(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

void getEvent(Event & event) {
       // sua event neu cp
            SDL_Event e;

            if ( SDL_PollEvent(&e) == 0 ) return;

            if   (e.type == SDL_QUIT) event = QUIT;
            else if (e.type == SDL_KEYDOWN ) {
                switch (e.key.keysym.sym) {
                    case SDLK_u:
                    case SDLK_UP:  event = UP;  cerr << "UP" << endl; break;
                    case SDLK_m:
                    case SDLK_DOWN:  event = DOWN; cerr << "D" << endl;break;
                    case SDLK_h:
                    case SDLK_LEFT:  event = LEFT; cerr << "L" << endl;break;
                    case SDLK_k:
                    case SDLK_RIGHT:  event = RIGHT; cerr << "R" << endl; break;
                }
            }
}

int main(int argc, char *argv[])
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    initSDL(window, renderer, WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

    Game game(renderer);
    Event event = UP;

    while ( ! game.isOver()) {
            getEvent(event);
            if (event == QUIT) break;
            game.update(event);

            clearScreen(renderer);
            game.draw();
            SDL_Delay(100);
    }
    cout << "Your score is " << game.score;

    quitSDL(window, renderer);
    return 0;
}
