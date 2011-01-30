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

static const int BORDER_ZONE = 40; // no moving objects within 40px of the level boundaries

Level(int num);
~Level();

void update();
void draw();
void shake(); // killing enemies shakes the level, 1 call per kill

bool isInLevelBoundaries(PixelCoords coords);

int pixelWidth;
int pixelHeight;

int levelBackground;

Player* player;
VictimList* victims;

LevelObjectList* levelObjects;
FoodList* foods;
BulletList* bullets;

private:

static const int BASE_FOOD_INTERVAL = 400;
static const float SHAKE_ROTATION_GAIN = .7;
static const float SHAKE_INTENSITY_GAIN = 1.5; // each shake adds rand from 0 to gain
static const float SHAKE_INTENSITY_MAX = 10;

long ticks; // game time
int background; // Background gfx for this level
int foodInterval; // Nr of ticks between food spawning
int foodTimer; // Ticks remaining until food spawns

float shakeIntensity; // approx. pixels
float shakeAngle;
float shakeRotation;

void spawnFood();
PixelCoords randomLevelCoords(); // returns valid random coords on level, not in any obstacle

};

#endif
