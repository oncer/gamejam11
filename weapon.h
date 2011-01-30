#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "weapontype.h"
#include "coords.h"

// This is the collectible weapon (on the ground in the level)
// which the player can pick up
class Weapon
{

public:

Weapon(WeaponType type, PixelCoords pos);

WeaponType weaponType;
PixelCoords position;
bool isConsumed;
bool isDead; // means the player has picked it up

void nextAnimFrame();
void draw();
void doMove();
void getPickedUp(); // get picked up

private:

static const int SPAWN_ANIM_TIME = 60;
static const int DEATH_ANIM_TIME = 40;

int animCountdown; // for spawn and death anims

};

#endif
