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
Plane enemy1;
Plane enemy2;
Plane enemybullet;
Plane enemybullet1;
Plane enemybullet2;
game app;
bool gamerunning=true;
int score;
int highscore;
int damage=0;
int bulletspeed=0;
bool enter=false;
void Screen() {
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
    if(event->keysym.scancode==SDL_SCANCODE_E){
        damage=1;
        bulletspeed=10;
        score=0;
        player.health=5;
        enter=true;
    }
    if(event->keysym.scancode==SDL_SCANCODE_M){
        damage=2;
        bulletspeed=15;
        score =0;
        player.health=5;
        enter=true;
    }
    if(event->keysym.scancode==SDL_SCANCODE_H){
        damage=3;
        bulletspeed=20;
        score =0;
        player.health=5;
        enter=true;
    }if(event->keysym.scancode==SDL_SCANCODE_R){
        enter=false;
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
            gamerunning=false;
        }
    }
}
void doKeyUp(SDL_KeyboardEvent *event) {
    if(event->keysym.scancode==SDL_SCANCODE_E){
        damage=1;
        bulletspeed=10;
        player.health=5;
        enter=true;
    }
    if(event->keysym.scancode==SDL_SCANCODE_M){
        damage=2;
        bulletspeed=15;
        player.health=5;
        enter=true;
    }
    if(event->keysym.scancode==SDL_SCANCODE_H){
        damage=3;
        bulletspeed=20;
        player.health=5;
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
            gamerunning=false;
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
        case SDL_QUIT:
            quitSDL(window,renderer);
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
bool collision(Plane e1,Plane e2) {
        int x1=e1.x,w1=e1.w;
        int x2=e2.x,w2=e2.w;
        int y1=e1.y,h1=e1.h;
        int y2=e2.y,h2=e2.h;
        bool collision_x=x1+w1>=x2&&x2+w2>=x1;
        bool collision_y=y1+h1>=y2&&y2+h2>=y1;
        return collision_x && collision_y;
}
void spawnenemy(Plane &enemyx) {
    setpos(enemyx);
    enemyx.x=rand()%SCREEN_WIDTH;
    enemyx.y=rand()%SCREEN_HEIGHT;
    if(enemyx.x<SCREEN_WIDTH/2) {
        enemyx.x=SCREEN_WIDTH/2;
    }
    if(enemyx.x>SCREEN_WIDTH-enemyx.w-50) {
        enemyx.x=SCREEN_WIDTH-enemyx.w-50;
    }
    if(enemyx.y<50) {
        enemyx.y=50;
    }
    if(enemyx.y>SCREEN_HEIGHT-enemyx.h-50) {
        enemyx.y=SCREEN_HEIGHT-enemyx.h-50;
    }
}
void logic(){
    while(collision(enemy1,enemy)){
        spawnenemy(enemy1);
    }
    while(collision(enemy2,enemy)){
        spawnenemy(enemy2);
    }
    while(collision(enemy1,enemy2)){
        spawnenemy(enemy2);
    }
}
void dobullet() {
    if (app.fire && bullet.health == 0) {
        bullet.x = player.x;
        bullet.y = player.y+24;
        bullet.health = 1;
    }

    bullet.x += BULLET_SPEED;
    if (bullet.x > SCREEN_WIDTH||collision(bullet,enemy)||collision(bullet,enemy1)||collision(bullet,enemy2)) {
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
SDL_Texture *getTextTexture(const char *text)
{
	SDL_Surface *surface;

	surface = TTF_RenderText_Solid(TTF_OpenFont("font.ttf",20), text,WHITE_COLOR);

	return toTexture(surface, 1);
}
void screenscore(){
    string s="Score:";
    s+=to_string(score);
    SDL_Texture* point= getTextTexture(s.c_str());
    blit(point,10,10);
    string w="Hi:";
    w+=to_string(highscore);
    SDL_Texture* hipoint= getTextTexture(w.c_str());
    blit(hipoint,SCREEN_WIDTH-100,10);
}
void enemyfire(int bulletspeed){
  if (enemybullet.health == 0) {
        enemybullet.x = enemy.x;
        enemybullet.y = enemy.y+24;
        enemybullet.health = 1;
    }
    enemybullet.x -=bulletspeed ;
    if (enemybullet.x <0||collision(enemybullet,player)) {
        enemybullet.health = 0;
    }
    if (enemybullet.health > 0) {
        blit(enemybullet.texture, enemybullet.x, enemybullet.y);
    }
}
void enemy1fire(int bulletspeed){
    if (enemybullet1.health == 0) {
        enemybullet1.x = enemy1.x;
        enemybullet1.y = enemy1.y+24;
        enemybullet1.health = 1;
    }
    enemybullet1.x -=bulletspeed ;
    if (enemybullet1.x <0||collision(enemybullet1,player)) {
        enemybullet1.health = 0;
    }
    if (enemybullet1.health > 0) {
        blit(enemybullet1.texture, enemybullet1.x, enemybullet1.y);
    }
}
void enemy2fire(int bulletspeed){
    if (enemybullet2.health == 0) {
        enemybullet2.x = enemy2.x;
        enemybullet2.y = enemy2.y+24;
        enemybullet2.health = 1;
    }
    enemybullet2.x -=bulletspeed ;
    if (enemybullet2.x <0||collision(enemybullet2,player)) {
        enemybullet2.health = 0;
    }
    if (enemybullet2.health > 0) {
        blit(enemybullet2.texture, enemybullet2.x, enemybullet2.y);
    }
}
void playermove(){
    if(player.x>SCREEN_WIDTH/2-70) {
                player.x=SCREEN_WIDTH/2-70;
            }
            if(player.x<0) {
                player.x=0;
            }
            if(player.y<20) {
                player.y=20;
            }
            if(player.y>SCREEN_HEIGHT-player.h-20) {
                player.y=SCREEN_HEIGHT-player.h-20;
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
}
void Menu()
{
    SDL_Texture *s1=getTextTexture("Choose game levels:");
    SDL_Texture *s2=getTextTexture("Press 'E' for easy");
    SDL_Texture *s3=getTextTexture("Press 'M' for medium");
    SDL_Texture *s4=getTextTexture("Press 'H' for hard");
    SDL_Texture *s5=getTextTexture("Press 'C' to shoot");
    blit(s1,SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-100);
    blit(s2,SCREEN_WIDTH/2-90,SCREEN_HEIGHT/2-70);
    blit(s3,SCREEN_WIDTH/2-90,SCREEN_HEIGHT/2-40);
    blit(s4,SCREEN_WIDTH/2-90,SCREEN_HEIGHT/2-10);
    SDL_Texture *s6=getTextTexture("Press 'X' to exit");
    blit(s5,SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2+50);
    blit(s6,SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2+20);

}
void gameover(){
    SDL_Texture*g1= getTextTexture("Press 'R' to play again");
    SDL_Texture*g2= getTextTexture("Press 'X' to exit");
    SDL_Texture *g3= getTextTexture("You Died!");
    string s="Your score:";
    s+=to_string(score);
    SDL_Texture*g4= getTextTexture(s.c_str());
    blit(g4,SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-70);
    blit(g1,SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-40);
    blit(g2,SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-10);
    blit(g3,SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-100);
}

int main(int argc,char* argv[]) {
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY*2,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,2048);
    Mix_Music *bgm= Mix_LoadMUS("bgm.mp3");
    initSDL(window,renderer,WINDOW_TITLE,SCREEN_WIDTH,SCREEN_HEIGHT);
    player.x = 100;
    player.y = 100;
    player.texture = loadTexture("player.png");
    bullet.texture = loadTexture("bullet.png");
    enemy.texture= loadTexture("enemy.png");
    enemy1.texture= loadTexture("enemy.png");
    enemy2.texture= loadTexture("enemy.png");

    enemybullet.texture=loadTexture("enemybullet.1.png");
    enemybullet1.texture=loadTexture("enemybullet.1.png");
    enemybullet2.texture=loadTexture("enemybullet.1.png");
    SDL_Texture *backgr=loadTexture("backgrnew.png");
    SDL_Texture* explos= loadTexture("explosion.png");
    spawnenemy(enemy);
    spawnenemy(enemy1);
    spawnenemy(enemy2);
    Mix_PlayMusic(bgm,-1);
    while(gamerunning) {
        doInput();
        if(enter) {
            Screen();
            blit(backgr,0,0);
            screenscore();
            logic();
            setpos(player);
            setpos(enemy);
            setpos(enemy1);
            setpos(enemy2);
            setpos(bullet);
            if(collision(bullet,enemy)) {
                blit(explos,enemy.x,enemy.y);
                spawnenemy(enemy);
                enemybullet.health=0;
                score++;
                if(highscore<score){
                    highscore++;
                }
                screenscore();
            }
            if(collision(bullet,enemy1)) {
                blit(explos,enemy1.x,enemy1.y);
                spawnenemy(enemy1);
                enemybullet1.health=0;
                score++;
                if(highscore<score){
                    highscore++;
                }
                screenscore();
            }
            if(collision(bullet,enemy2)) {
                blit(explos,enemy2.x,enemy2.y);
                spawnenemy(enemy2);
                enemybullet2.health=0;
                score++;
                if(highscore<score){
                    highscore++;
                }
                screenscore();
            }
            if(collision(enemybullet,player)||collision(enemybullet1,player)||collision(enemybullet2,player)){
                player.health-=damage;
            }
            blit(enemy.texture,enemy.x,enemy.y);
            blit(enemy1.texture,enemy1.x,enemy1.y);
            blit(enemy2.texture,enemy2.x,enemy2.y);
            enemyfire(bulletspeed);
            enemy1fire(bulletspeed);
            enemy2fire(bulletspeed);
            playermove();
            string s="Health:";
            s+=to_string(player.health);
            SDL_Texture* health=getTextTexture(s.c_str());
            blit(health,SCREEN_WIDTH/2,10);
            blit(player.texture,player.x,player.y);
            if(player.health<=0){
                blit(backgr,0,0);
                app.fire=0;
                gameover();
            }
            dobullet();
            upScence();
            SDL_Delay(16);
        } else {
            Screen();
            blit(backgr,0,0);
            Menu();
            upScence();
        }
    }
    return 0;
}
