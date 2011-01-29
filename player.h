#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player;

#include "game.h"
#include "coords.h"

class Player
{
	int ix, iy; /* Input direction. */
	PixelCoords position;
	
public:

void nextAnimFrame();
void draw();

bool handleEvent(ALLEGRO_EVENT *event);

bool canMove();
void doMove();

};

#endif
