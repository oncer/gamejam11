#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player;

#include "game.h"
#include "coords.h"

class Player
{
public:

Player(PixelCoords pos);

static const int HUNGER_LIMIT = 3000;

int ix, iy; /* input direction */
int ifire; /* fire button input */
int vx, vy; /* view direction */
PixelCoords position;
int fireRate; /* how many ticks for next bullet */
int fireTicks;
int hunger; // if this reaches HUNGER_LIMIT, player dies
bool isDead; // set after death animation concludes. => Game Over

void nextAnimFrame();
void draw();

bool handleEvent(ALLEGRO_EVENT *event);
void increaseHunger();
void feed(int foodValue);
 
bool canMove();
void doMove();

};

#endif
