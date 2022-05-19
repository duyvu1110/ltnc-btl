#include<iostream>
#include<SDL.h>
#include"utils.h"
#include"params.h"
#include<SDL_image.h>
#include"box.h"
#include"game.h"
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<fstream>
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
int div_bullet;
int div_enemy;
game app;
int SPEED=0;
bool gamerunning=true;
int score;
int highscore;
int damage=0;
int key=0;
bool enter=false;
fstream gameStream;
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
void setpos(Plane& a) {
    SDL_Rect tmp;
    SDL_QueryTexture(a.texture, NULL, NULL, &tmp.w, &tmp.h);
    a.w=tmp.w;
    a.h=tmp.h;
}
void setplayer(){
    player.x=100;
    player.y=100;
}
void spawnenemy(Plane &enemyx) {
    setpos(enemyx);
    enemyx.x=SCREEN_WIDTH-enemyx.w;
    enemyx.y=rand()%SCREEN_HEIGHT;
    if(enemyx.y<50) {
        enemyx.y=50;
    }
    if(enemyx.y>SCREEN_HEIGHT-enemyx.h-50) {
        enemyx.y=SCREEN_HEIGHT-enemyx.h-50;
    }
}
void doKeyDown(SDL_KeyboardEvent *event) {
    if(event->keysym.scancode==SDL_SCANCODE_E){
        damage=1;
        div_bullet=60;
        div_enemy=500;
        score=0;
        enemybullet.health=0;
        enemybullet1.health=0;
        enemybullet2.health=0;
        spawnenemy(enemy);
        spawnenemy(enemy1);
        spawnenemy (enemy2);
        setplayer();
        player.health=5;
        enter=true;
    }
    if(event->keysym.scancode==SDL_SCANCODE_M){
        damage=2;
        div_bullet=55;
        div_enemy=400;
        score =0;
         enemybullet.health=0;
        enemybullet1.health=0;
        enemybullet2.health=0;
         spawnenemy(enemy);
        spawnenemy(enemy1);
        spawnenemy (enemy2);
        setplayer();
        player.health=5;
        enter=true;
    }
    if(event->keysym.scancode==SDL_SCANCODE_H){
        damage=3;
        div_bullet=50;
        div_enemy=300;
        score =0;
         enemybullet.health=0;
        enemybullet1.health=0;
        enemybullet2.health=0;
         spawnenemy(enemy);
        spawnenemy(enemy1);
        spawnenemy (enemy2);
        setplayer();
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
            gameStream.open("input.txt",ios::out|ios::trunc);
            if(player.health<=0){
                gameStream<<0;
            }else{
                gameStream<<1<<endl;
                gameStream<<enemy.x<<" "<<enemy.y<<endl;
                gameStream<<enemy1.x<<" "<<enemy1.y<<endl;
                gameStream<<enemy2.x<<" "<<enemy2.y<<endl;
                gameStream<<player.x<<" "<<player.y<<" "<<player.health<<endl;
                gameStream<<damage<<" "<<div_bullet<<" "<<div_enemy<<endl;
                gameStream<<score<<" "<<highscore<<endl;
            }


            gameStream.close();
            quitSDL(window,renderer);
            gamerunning=false;
        }
    }
}
void doKeyUp(SDL_KeyboardEvent *event) {
    if(event->keysym.scancode==SDL_SCANCODE_E){
        damage=1;
        div_bullet=60;
        div_enemy=500;
        score=0;
        enemybullet.health=0;
        enemybullet1.health=0;
        enemybullet2.health=0;
         spawnenemy(enemy);
        spawnenemy(enemy1);
        spawnenemy (enemy2);
        setplayer();
        player.health=5;
        enter=true;
    }
    if(event->keysym.scancode==SDL_SCANCODE_M){
        damage=2;
        div_bullet=55;
        div_enemy=400;
        score =0;
        enemybullet.health=0;
        enemybullet1.health=0;
        enemybullet2.health=0;
         spawnenemy(enemy);
        spawnenemy(enemy1);
        spawnenemy (enemy2);
        setplayer();
        player.health=5;
        enter=true;
    }
    if(event->keysym.scancode==SDL_SCANCODE_H){
        damage=3;
        div_bullet=50;
        div_enemy=300;
         spawnenemy(enemy);
        spawnenemy(enemy1);
        spawnenemy (enemy2);
        score =0;
        enemybullet.health=0;
        enemybullet1.health=0;
        enemybullet2.health=0;
        setplayer();
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
            gameStream.open("input.txt",ios::out|ios::trunc);
            if(player.health<=0){
                gameStream<<0;
            }else{
                gameStream<<1<<endl;
                gameStream<<enemy.x<<" "<<enemy.y<<endl;
                gameStream<<enemy1.x<<" "<<enemy1.y<<endl;
                gameStream<<enemy2.x<<" "<<enemy2.y<<endl;
                gameStream<<player.x<<" "<<player.y<<" "<<player.health<<endl;
                gameStream<<damage<<" "<<div_bullet<<" "<<div_enemy<<endl;
                gameStream<<score<<" "<<highscore<<endl;
            }
            gameStream.close();
            quitSDL(window,renderer);
            gamerunning=false;
        }
    }
}
void dogameStream() {
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
bool collision(Plane e1,Plane e2) {
        int x1=e1.x-20,w1=e1.w-20;
        int x2=e2.x-20,w2=e2.w-20;
        int y1=e1.y-20,h1=e1.h-20;
        int y2=e2.y-20,h2=e2.h-20;
        bool collision_x=x1+w1>=x2&&x2+w2>=x1;
        bool collision_y=y1+h1>=y2&&y2+h2>=y1;
        return collision_x && collision_y;
}

void dobullet() {
    if (app.fire && bullet.health == 0) {
        bullet.x = player.x;
        bullet.y = player.y+24;
        bullet.health = 1;
    }

    bullet.x += BULLET_SPEED;
//    bullet.y += BULLET_SPEED;
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
bool warning(Plane playerx,Plane enemyx){
    enemyx.x-=100;
    enemyx.y-=100;
    enemyx.w+=200;
    enemyx.h+=200;
    if(collision(playerx,enemyx)){
        return true;
    }
    return false;
}
void enemyfire(bool firing){
    firing=warning(player,enemy);
    int bulletspeedx;
    int bulletspeedy;
  if (enemybullet.health == 0&&firing) {
        enemybullet.x = enemy.x+enemy.w/2;
        enemybullet.y = enemy.y+enemy.h/2;
        enemybullet.health = 1;
    }
    bulletspeedx=(player.x-enemy.x)/div_bullet;
    bulletspeedy=(player.y-enemy.y)/div_bullet;

    enemybullet.x +=bulletspeedx;
    enemybullet.y +=bulletspeedy;
    if (enemybullet.x <0||collision(enemybullet,player)||enemybullet.x>SCREEN_WIDTH-enemybullet.w||enemybullet.y<0||enemybullet.y>SCREEN_HEIGHT-enemybullet.h) {
        enemybullet.health = 0;
    }
    if (enemybullet.health > 0) {
        blit(enemybullet.texture, enemybullet.x, enemybullet.y);
    }
}
void enemy1fire(bool firing){
    firing=warning(player,enemy1);
    int bulletspeedx;
    int bulletspeedy;
    if (enemybullet1.health == 0&&firing) {
        enemybullet1.x = enemy1.x+enemy1.w/2;
        enemybullet1.y = enemy1.y+enemy1.h/2;
        enemybullet1.health = 1;
    }
    bulletspeedx=(player.x-enemy1.x)/div_bullet;
    bulletspeedy=(player.y-enemy1.y)/div_bullet;

    enemybullet1.x +=bulletspeedx;
    enemybullet1.y +=bulletspeedy;
    if (enemybullet1.x <0||collision(enemybullet1,player)||enemybullet1.x>SCREEN_WIDTH-enemybullet1.w||enemybullet1.y<0||enemybullet1.y>SCREEN_HEIGHT-enemybullet1.h) {
        enemybullet1.health = 0;
    }
    if (enemybullet1.health > 0) {
        blit(enemybullet1.texture, enemybullet1.x, enemybullet1.y);
    }
}
void enemy2fire(bool firing){
    firing=warning(player,enemy2);
    int bulletspeedx;
    int bulletspeedy;
    if (enemybullet2.health == 0&&firing) {
        enemybullet2.x = enemy2.x+enemy2.w/2;
        enemybullet2.y = enemy2.y+enemy2.h/2;
        enemybullet2.health = 1;
    }
    bulletspeedx=(player.x-enemy2.x)/div_bullet;
    bulletspeedy=(player.y-enemy2.y)/div_bullet ;

    enemybullet2.x +=bulletspeedx;
    enemybullet2.y +=bulletspeedy;
    if (enemybullet2.x <0||collision(enemybullet2,player)||enemybullet2.x>SCREEN_WIDTH-enemybullet2.w||enemybullet2.y<0||enemybullet2.y>SCREEN_HEIGHT-enemybullet2.h) {
        enemybullet2.health = 0;
    }
    if (enemybullet2.health > 0) {
        blit(enemybullet2.texture, enemybullet2.x, enemybullet2.y);
    }
}
void crash(){
    if(collision(player,enemy)||collision(player,enemy1)||collision(player,enemy2)){
        player.health=0;
    }
}
void enemymove(Plane &enemyx){
    enemyx.x+=(player.x-enemyx.x)/div_enemy;
    enemyx.y+=(player.y-enemyx.y)/div_enemy;
        if (enemyx.x <0||enemyx.x>SCREEN_WIDTH-enemyx.w||enemyx.y<0||enemyx.y>SCREEN_HEIGHT-enemyx.h) {
        spawnenemy(enemyx);
    }
}
void playermove(){
            if(player.x<0) {
                player.x=0;
            }
            if(player.y<10) {
                player.y=10;
            }
            if(player.y>SCREEN_HEIGHT-player.h) {
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
    bool firing=false;
    gameStream.open("input.txt",ios::in);
    int key;gameStream>>key;
    gameStream.close();
//    while(!gameStream.eof()){
//        gameStream>>key;
//    }

    if(key==0){
    player.x = 100;
    player.y = 100;
    spawnenemy(enemy);
    spawnenemy(enemy1);
    spawnenemy(enemy2);
    }
    if(key==1){
            gameStream.open("input.txt",ios::in);

            if(gameStream.is_open()){
                gameStream>>key;
                gameStream>>enemy.x>>enemy.y;
                gameStream>>enemy1.x>>enemy1.y;
                gameStream>>enemy2.x>>enemy2.y;
                gameStream>>player.x>>player.y>>player.health;
                gameStream>>damage>>div_bullet>>div_enemy;
                gameStream>>score>>highscore;
                gameStream.close();
            }
            else return 404;
            enter=true;
    }

    //Mix_PlayMusic(bgm,-1);
    while(gamerunning) {
        dogameStream();
        if(enter) {
            Screen();
            blit(backgr,0,0);
            screenscore();
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
            enemy1fire(firing);
            enemy2fire(firing);
            crash();
            playermove();
            enemyfire(firing);
            enemymove(enemy);
            enemymove(enemy1);
            enemymove(enemy2);
            if(collision(enemy1,enemy2)){
                spawnenemy(enemy1);

                blit(explos,enemy1.x,enemy1.y);
            }
             if(collision(enemy,enemy2)){
                spawnenemy(enemy);

                blit(explos,enemy.x,enemy.y);
            }
             if(collision(enemy1,enemy)){
                spawnenemy(enemy1);

                blit(explos,enemy1.x,enemy1.y);
            }
            string s="Health:";
            s+=to_string(player.health);
            SDL_Texture* health=getTextTexture(s.c_str());
            blit(health,SCREEN_WIDTH/2,10);
            blit(player.texture,player.x,player.y);
            dobullet();
            if(player.health<=0){
//                blit(explos,player.x,player.y);
                SDL_RenderClear(renderer);
                blit(backgr,0,0);
                app.fire=0;
                gameover();
            }
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
