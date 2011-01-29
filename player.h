#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player;

#include "game.h"
#include "coords.h"

class Player
{

public:

static const int HUNGER_LIMIT = 3000;

int ix, iy; /* Input direction. */
PixelCoords position;
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
