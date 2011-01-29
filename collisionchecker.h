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

bool playerCanMoveTo(PixelCoords position);
bool victimCanMoveTo(PixelCoords position);
void playerPickupFood();
void victimPickupFood();
void playerVsVictim();

private:

// bounding box sizes for collision checks of various objects
static const int PLAYER_WIDTH = 16;
static const int PLAYER_HEIGHT = 20;
static const int VICTIM_WIDTH = 24;
static const int VICTIM_HEIGHT = 24;
static const int FOOD_WIDTH = 24;
static const int FOOD_HEIGHT = 24;

Level* level;

};

#endif

