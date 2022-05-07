#include<iostream>
#include<SDL.h>
#include"utils.h"
#include"params.h"
#include<SDL_image.h>
#include"box.h"
#include"game.h"
#include<SDL_ttf.h>
#include<SDL_mixer.h>
using namespace std;
#define main SDL_main
SDL_Renderer *renderer;
SDL_Window *window;
Plane player;
Plane bullet;
Plane enemy;
game app;
int score;
bool enter=false;
void Screen() {
//    SDL_SetRenderDrawColor(renderer,96,128 ,255,255);
    SDL_RenderClear(renderer);
}
void upScence() {
    SDL_RenderPresent(renderer);
}

SDL_Texture *loadTexture(char *filename) {
    SDL_Texture *texture;

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    texture = IMG_LoadTexture(renderer, filename);

    return texture;
}

void blit(SDL_Texture *texture, int x, int y) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void doKeyDown(SDL_KeyboardEvent *event) {
    if(event->keysym.scancode==SDL_SCANCODE_SPACE){
        enter=true;
    }
    if (event->repeat == 0) {
        if (event->keysym.scancode == SDL_SCANCODE_UP) {
            app.up = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
            app.down = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
            app.left = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
            app.right = 1;
        }
        if (event->keysym.scancode == SDL_SCANCODE_C) {
            app.fire = 1;
        }
        if(event->keysym.scancode== SDL_SCANCODE_X) {
            quitSDL(window,renderer);
            cerr<<score;
        }
    }
}
void doKeyUp(SDL_KeyboardEvent *event) {
    if(event->keysym.scancode==SDL_SCANCODE_SPACE){
        enter=true;
    }
    if (event->repeat == 0) {
        if (event->keysym.scancode == SDL_SCANCODE_UP) {
            app.up = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
            app.down = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
            app.left = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
            app.right = 0;
        }
        if (event->keysym.scancode == SDL_SCANCODE_C) {
            app.fire = 0;
        }
        if(event->keysym.scancode== SDL_SCANCODE_X) {
            quitSDL(window,renderer);
            cerr<<score;
        }
    }
}
void doInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        switch (event.type) {
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
void setpos(Plane& a) {
    SDL_Rect tmp;
    SDL_QueryTexture(a.texture, NULL, NULL, &tmp.w, &tmp.h);
    a.w=tmp.w;
    a.h=tmp.h;
}
bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    int lefte,leftb;
    int righte,rightb;
    int tope,topb;
    int bote,botb;
    lefte=x1;
    righte=x1+w1;
    tope= y1;
    bote= y1+h1;
    leftb=x2;
    rightb=x2+w2;
    topb=y2;
    botb=y2+h2;
    if(bote<=topb) {
        return false;
    }
    if(tope >= topb) {
        return false;
    }
    if(righte<=leftb) {
        return false;
    }
    if(lefte>=rightb) {
        return false;
    }
    return true;
}
void spawnenemy() {
    setpos(enemy);
    enemy.x=rand()%SCREEN_WIDTH;
    enemy.y=rand()%SCREEN_HEIGHT;
    if(enemy.x<SCREEN_WIDTH/2) {
        enemy.x=SCREEN_WIDTH/2;
    }
    if(enemy.x>SCREEN_WIDTH-enemy.w-50) {
        SCREEN_WIDTH-enemy.w-50;
    }
    if(enemy.y<50) {
        enemy.y=50;
    }
    if(enemy.y>SCREEN_HEIGHT-enemy.h-50) {
        enemy.y=SCREEN_HEIGHT-enemy.h-50;
    }
}
void dobullet() {
    if (app.fire && bullet.health == 0) {
        bullet.x = player.x;
        bullet.y = player.y+24;
        bullet.dx = BULLET_SPEED;
        bullet.dy = 0;
        bullet.health = 1;
    }

    bullet.x += bullet.dx;
    bullet.y += bullet.dy;

    if (bullet.x > SCREEN_WIDTH||collision(bullet.x,bullet.y,bullet.w,bullet.h,enemy.x,enemy.y,enemy.w,enemy.h)) {
        bullet.health = 0;
    }
    if (bullet.health > 0) {
        blit(bullet.texture, bullet.x, bullet.y);
    }
}

SDL_Texture *toTexture(SDL_Surface *surface, int destroySurface)
{
	SDL_Texture *texture;

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (destroySurface)
	{
		SDL_FreeSurface(surface);
	}

	return texture;
}
SDL_Texture *getTextTexture(char *text)
{
	SDL_Surface *surface;

	surface = TTF_RenderUTF8_Blended(TTF_OpenFont("font.ttf",25), text,WHITE_COLOR);

	return toTexture(surface, 1);
}

int main(int argc,char* argv[]) {
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY*2,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1000000);
    Mix_Music *bgm= Mix_LoadMUS("bgm.mp3");

    initSDL(window,renderer,WINDOW_TITLE,SCREEN_WIDTH,SCREEN_HEIGHT);
    player.x = 100;
    player.y = 100;

    player.texture = loadTexture("player.png");
    bullet.texture = loadTexture("bullet.png");
    enemy.texture= loadTexture("enemy.png");
    SDL_Texture *backgr=loadTexture("backgrnew.png");
    SDL_Texture* explos= loadTexture("explosion.png");
    spawnenemy();

    while(true) {
        doInput();
        if(enter) {
            Screen();
            blit(backgr,0,0);
            Mix_PlayMusic(bgm,-1);
            setpos(player);
            setpos(enemy);
            setpos(bullet);
            if(collision(bullet.x,bullet.y,bullet.w,bullet.h,enemy.x,enemy.y,enemy.w/2,enemy.h/2)) {
                blit(explos,enemy.x,enemy.y);
                spawnenemy();
                score++;
            }
            blit(enemy.texture,enemy.x,enemy.y);
            player.x += player.dx;
            player.y += player.dy;
            if(player.x>SCREEN_WIDTH/2-70) {
                player.x=SCREEN_WIDTH/2-70;
            }
            if(player.x<0) {
                player.x=0;
            }
            if(player.y<0) {
                player.y=0;
            }
            if(player.y>SCREEN_HEIGHT-player.h+20) {
                player.y=SCREEN_HEIGHT-player.h;
            }

            if (app.up) {
                player.y -= PLAYER_SPEED;
            }

            if (app.down) {
                player.y += PLAYER_SPEED;
            }

            if (app.left) {
                player.x -= PLAYER_SPEED;
            }

            if (app.right) {
                player.x += PLAYER_SPEED;
            }

            blit(player.texture,player.x,player.y);
            dobullet();
            upScence();
            SDL_Delay(16);
        } else {
            Screen();
            SDL_Texture* font= getTextTexture("Press 'Space' to start ");
            blit(backgr,0,0);
            blit(font,SCREEN_HEIGHT/2,SCREEN_WIDTH/2);
            upScence();
        }

    }
    return 0;
}
