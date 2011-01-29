#ifndef _LEVEL_H_
#define _LEVEL_H_

class Level;

#include <vector>
#include <list>
#include "player.h"
#include "victim.h"
#include "levelobject.h"
#include "bullet.h"
#include "food.h"

typedef std::list<Victim*> VictimList;
typedef std::vector<LevelObject*> LevelObjectList;
typedef std::list<Food*> FoodList;
typedef std::vector<Bullet*> BulletList;

/* Contains runtime level info */
class Level
{

public:

Level();
~Level();

void update();
void draw();

Player* player;

private:

static const int BASE_FOOD_INTERVAL = 900;

VictimList* victims;
LevelObjectList* levelObjects;
FoodList* foods;

int pixelWidth;
int pixelHeight;
int foodInterval; // Nr of ticks between food spawning
int foodTimer; // Ticks remaining until food spawns

void spawnFood();
PixelCoords randomLevelCoords(); // returns valid random coords on level, not in any obstacle

public:
	BulletList* bullets;
};

#endif
