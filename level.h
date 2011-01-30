#ifndef _LEVEL_H_
#define _LEVEL_H_

class Level;

#include <vector>
#include <list>
#include "player.h"
#include "victim.h"
#include "levelobject.h"
#include "projectile.h"
#include "food.h"
#include "weapon.h"
#include "laser.h"

typedef std::list<Victim*> VictimList;
typedef std::vector<LevelObject*> LevelObjectList;
typedef std::list<Food*> FoodList;
typedef std::list<Weapon*> WeaponList;
typedef std::vector<Projectile*> ProjectileList;

/* Contains runtime level info */
class Level
{

public:

static const int BORDER_ZONE = 25; // no moving objects within 25px of the level boundaries
static const int MAX_VICTIMS = 1000; // stop splitting after that

Level();
~Level();

void create(int num);

void update();
void draw();
void shake(); // killing enemies shakes the level, 1 call per kill

bool isInLevelBoundaries(PixelCoords coords);
void laserBeam (PixelCoords position, float dx, float dy); // only holds for 1 tick

int pixelWidth;
int pixelHeight;

int levelNumber; // 1 and up 
int levelBackground;

Player* player;
VictimList* victims;

LevelObjectList* levelObjects;
FoodList* foods;
WeaponList* weapons;
ProjectileList* projectiles;
Laser* laser;

private:

static const int FLAMETHROWER_SPAWN_TIME = 600;
static const int LASER_SPAWN_TIME = 1200;
static const int FLAMETHROWER_FIRST_LEVEL = 3;
static const int LASER_FIRST_LEVEL = 6;
static const int BASE_FOOD_INTERVAL = 240;
static const float SHAKE_ROTATION_GAIN = .7;
static const float SHAKE_INTENSITY_GAIN = 1.5; // each shake adds rand from 0 to gain
static const float SHAKE_INTENSITY_MAX = 10;
static const int LASER_COLORS = 4;

#define LASER_COLOR_0 al_map_rgb(100, 100, 255)
#define LASER_COLOR_1 al_map_rgb(200, 200, 255)
#define LASER_COLOR_2 al_map_rgb(255, 255, 255)
#define LASER_COLOR_3 al_map_rgb(200, 200, 255)

long ticks; // game time
int background; // Background gfx for this level
int foodInterval; // Nr of ticks between food spawning
int foodTimer; // Ticks remaining until food spawns

float shakeIntensity; // approx. pixels
float shakeAngle;
float shakeRotation;

void spawnFood();
void drawLaser();
PixelCoords randomLevelCoords(); // returns valid random coords on level, not in any obstacle

};

#endif
