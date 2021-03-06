#ifndef _RESOURCES_H_
#define _RESOURCES_H_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/* Contains game assets from files (images, sounds, ...) */
class Resources
{

public:

static Resources* instance(); // get singleton instance
static void destroyInstance(); // release resources

~Resources();
void loadEverything();

static const int OBSTACLES = 3;
static const int PLAYER_FRAMES = 1;
static const int VICTIM_FRAMES = 2;
static const int WEAPON_IMAGES = 3;
static const int BULLET_FRAMES = 4;
static const int FLAME_FRAMES = 13;
static const int EXPLOSION_FRAMES = 6;
static const int FOOD_VARIATIONS = 3;
static const int BIT_VARIATIONS = 1; // how many different kinds of bits there are
static const int BACKGROUND_VARIATIONS = 2;
static const int LEVEL_OBJECT_VARIATIONS = 3;

enum Frame { FRAME_FRONT }; // anim frame indices

ALLEGRO_BITMAP* imgTitle;
ALLEGRO_BITMAP* imgObstacle[OBSTACLES];
ALLEGRO_BITMAP* imgPlayer[PLAYER_FRAMES];
ALLEGRO_BITMAP* imgVictim[VICTIM_FRAMES];
ALLEGRO_BITMAP* imgWeapon[BULLET_FRAMES];
ALLEGRO_BITMAP* imgBullet[BULLET_FRAMES];
ALLEGRO_BITMAP* imgFlame[FLAME_FRAMES];
ALLEGRO_BITMAP* imgExplosion[EXPLOSION_FRAMES];
ALLEGRO_BITMAP* imgFood[FOOD_VARIATIONS];
ALLEGRO_BITMAP* imgBit[BIT_VARIATIONS];
ALLEGRO_BITMAP* imgBackground[BACKGROUND_VARIATIONS];
ALLEGRO_BITMAP* imgLevelObject[LEVEL_OBJECT_VARIATIONS];

ALLEGRO_FONT* fontNormal;
ALLEGRO_FONT* fontBig;

private:

Resources();
Resources(const Resources & );

static Resources* theInstance;

};

#endif
