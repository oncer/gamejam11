#ifndef _COLLISIONCHECKER_H_
#define _COLLISIONCHECKER_H_

#include "coords.h"

class Level;

// looks for and handles collisions:
// player vs. victim
// player vs. food
// victims vs. food
// player vs. map obstacles
// victims vs. map obstacles
class CollisionChecker
{

public:

CollisionChecker(Level* lvl);

bool foodCanMoveTo(PixelCoords position);
bool projectileCanMoveTo(PixelCoords position);
bool playerCanMoveTo(PixelCoords position);
bool victimCanMoveTo(PixelCoords position);
void playerPickupWeapon();
void playerPickupFood();
void victimPickupFood();
void playerVsVictim();
void victimVsProjectile();
bool canMoveTo(PixelCoords position, int w, int h);

// cap on nr. of expensive operations per tick (like collisions)
static const int OPERATIONS_CAP = 5000;

// bounding box sizes for collision checks of various objects
static const int PLAYER_WIDTH = 16;
static const int PLAYER_HEIGHT = 20;
static const int VICTIM_WIDTH = 24;
static const int VICTIM_HEIGHT = 24;
static const int FOOD_WIDTH = 24;
static const int FOOD_HEIGHT = 24;
static const int WEAPON_WIDTH = 24;
static const int WEAPON_HEIGHT = 24;

static const int BULLET_WIDTH = 4;
static const int BULLET_HEIGHT = 4;
static const int BLOCK_WIDTH0 = 24;
static const int BLOCK_HEIGHT0 = 24;
static const int BLOCK_WIDTH1 = 56;
static const int BLOCK_HEIGHT1 = 56;
static const int BLOCK_WIDTH2 = 64;
static const int BLOCK_HEIGHT2 = 64;
static const int PROJECTILE_WIDTH = 4;
static const int PROJECTILE_HEIGHT = 4;


Level* level;

};

#endif

