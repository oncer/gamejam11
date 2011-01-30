#ifndef _FOOD_H_
#define _FOOD_H_

#include "coords.h"

// Food may be fruit (consumable by player) or bits of bad guys
// (player wants to collect those before other bad guys do)
class Food
{

public:

Food(int var, PixelCoords pos, int val, bool playerEdible = true);

int variation;
PixelCoords position;
int value;
bool isPlayerEdible; // true if player can eat this
bool isConsumed;
bool isDead;

float dx, dy;

void nextAnimFrame();
void draw();
void doMove();
void getEaten();

private:

static const int SPAWN_ANIM_TIME = 60;
static const int DEATH_ANIM_TIME = 40;

int animCountdown; // for spawn and death anims

};

#endif
