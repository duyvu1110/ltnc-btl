#include<iostream>
#include<SDL.h>
#include"utils.h"
#include"params.h"
#include<SDL_image.h>
#include"box.h"
#include"game.h"
using namespace std;
#define main SDL_main
SDL_Renderer *renderer;
SDL_Window *window;
Plane player;
Plane bullet;
Plane enemy;
game app;
void Screen(){
    SDL_SetRenderDrawColor(renderer,96,128 ,255,255);
    SDL_RenderClear(renderer);
}
void upScence(){
    SDL_RenderPresent(renderer);
}
SDL_Texture *loadTexture(char *filename)
{
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(renderer, filename);

	return texture;
}
void blit(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void doKeyDown(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			app.up = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			app.down = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
            app.left = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			app.right = 1;
		}
		if (event->keysym.scancode == SDL_SCANCODE_C)
        {
            app.fire = 1;
        }
	}
}
void doKeyUp(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			app.up = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			app.down = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
            app.left = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			app.right = 0;
		}
		if (event->keysym.scancode == SDL_SCANCODE_C)
        {
            app.fire = 0;
        }
	}
}
void doInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				doKeyDown(&event.key);
				break;

			case SDL_KEYUP:
				doKeyUp(&event.key);
				break;

			default:
				break;
		}
	}
}
void Framerate(long *a,float* remainder){
    long wait, frameTime;

	wait = 16 + *remainder;

	*remainder -= (int)*remainder;

	frameTime = SDL_GetTicks() - *a;

	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);

	*remainder += 0.667;

	*a = SDL_GetTicks();
}
void spawnenemy(Plane enemy){
    if(enemy.health!=0){
         blit(enemy.texture,enemy.x,enemy.y);
    }else{
    enemy.health=1;
    enemy.x=rand()% SCREEN_WIDTH/2;
    enemy.y=rand()% SCREEN_HEIGHT/2;
    blit(enemy.texture,enemy.x,enemy.y);
    }
}

int main(int argc,char* argv[])
{
    IMG_Init(IMG_INIT_PNG);
    initSDL(window,renderer,WINDOW_TITLE,SCREEN_WIDTH,SCREEN_HEIGHT);
    long a;
    float remain;
    a=SDL_GetTicks();
    remain=0;
    player.x = 50;
	player.y = 50;
	player.texture = loadTexture("player1.png");
	bullet.texture = loadTexture("bullet.png");
	enemy.texture= loadTexture("player1.png");
	enemy.health=1;
//	spawnenemy(enemy);
    while(true){
        Screen();
        spawnenemy(enemy);

        doInput();
        player.x += player.dx;
		player.y += player.dy;
        if (app.up)
		{
			player.y -= PLAYER_SPEED;
		}

		if (app.down)
		{
			player.y += PLAYER_SPEED;
		}

		if (app.left)
		{
			player.x -= PLAYER_SPEED;
		}

		if (app.right)
		{
			player.x += PLAYER_SPEED;
		}
		if (app.fire && bullet.health == 0)
		{
			bullet.x = player.x;
			bullet.y = player.y;
			bullet.dx = BULLET_SPEED;
			bullet.dy = 0;
			bullet.health = 1;
		}

		bullet.x += bullet.dx;
		bullet.y += bullet.dy;

		if (bullet.x > SCREEN_WIDTH)
		{
			bullet.health = 0;
		}

        blit(player.texture,player.x,player.y);

        if (bullet.health > 0)
		{
			blit(bullet.texture, bullet.x, bullet.y);

		}
		 upScence();
        Framerate(&a,&remain);
    }
    return 0;
}
