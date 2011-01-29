#ifndef _FOOD_H_
#define _FOOD_H_

#include "coords.h"

// Food may be fruit (consumable by player) or bits of bad guys
// (player wants to collect those before other bad guys do)
class Food
{

public:

Food(PixelCoords pos, int val, bool playerEdible = true);

PixelCoords position;
int value;
bool isPlayerEdible; // true if player can eat this
bool isConsumed;
bool isDead;

void nextAnimFrame();
void draw();

private:

};

#endif
