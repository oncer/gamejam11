#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player;

#include "game.h"
#include "coords.h"

class Player
{
	int ix, iy; /* input direction */
	int ifire; /* fire button input */
	int vx, vy; /* view direction */
	PixelCoords position;
	int fireRate; /* how many ticks for next bullet */
	int fireTicks;
public:

Player(PixelCoords pos);

void nextAnimFrame();
void draw();

bool handleEvent(ALLEGRO_EVENT *event);

bool canMove();
void doMove();

};

#endif
