#include "resources.h"

Resources* Resources::theInstance = NULL;

Resources* Resources::instance()
{
	if (theInstance == NULL) {
		theInstance = new Resources();
	}
	return theInstance;
}

void Resources::destroyInstance()
{
	if (theInstance != NULL) {
		delete theInstance;
		theInstance = NULL;
	}
}

Resources::Resources()
{
	fontNormal = NULL;
	fontBig = NULL;

	imgTitle = NULL;
	memset(imgObstacle, 0, OBSTACLES * sizeof(ALLEGRO_BITMAP*));
	memset(imgPlayer, 0, PLAYER_FRAMES * sizeof(ALLEGRO_BITMAP*));
	memset(imgVictim, 0, VICTIM_FRAMES * sizeof(ALLEGRO_BITMAP*));
	memset(imgExplosion, 0, EXPLOSION_FRAMES * sizeof(ALLEGRO_BITMAP*));
	memset(imgWeapon, 0, WEAPON_IMAGES * sizeof(ALLEGRO_BITMAP*));
	memset(imgBullet, 0, BULLET_FRAMES * sizeof(ALLEGRO_BITMAP*));
	memset(imgFlame, 0, FLAME_FRAMES * sizeof(ALLEGRO_BITMAP*));
	memset(imgFood, 0, FOOD_VARIATIONS * sizeof(ALLEGRO_BITMAP*));
	memset(imgBit, 0, BIT_VARIATIONS * sizeof(ALLEGRO_BITMAP*));
	memset(imgBackground, 0, BACKGROUND_VARIATIONS * sizeof(ALLEGRO_BITMAP*));
	memset(imgLevelObject, 0, LEVEL_OBJECT_VARIATIONS * sizeof(ALLEGRO_BITMAP*));
}

Resources::~Resources()
{
	al_destroy_font(fontNormal);
	al_destroy_font(fontBig);
	al_destroy_bitmap(imgTitle);
	for (int i = 0; i < OBSTACLES; i++) al_destroy_bitmap(imgObstacle[i]);
	for (int i = 0; i < PLAYER_FRAMES; i++) al_destroy_bitmap(imgPlayer[i]);
	for (int i = 0; i < VICTIM_FRAMES; i++) al_destroy_bitmap(imgVictim[i]);
	for (int i = 0; i < WEAPON_IMAGES; i++) al_destroy_bitmap(imgWeapon[i]);
	for (int i = 0; i < BULLET_FRAMES; i++) al_destroy_bitmap(imgBullet[i]);
	for (int i = 0; i < FLAME_FRAMES; i++) al_destroy_bitmap(imgFlame[i]);
	for (int i = 0; i < EXPLOSION_FRAMES; i++) al_destroy_bitmap(imgExplosion[i]);
	for (int i = 0; i < FOOD_VARIATIONS; i++) al_destroy_bitmap(imgFood[i]);
	for (int i = 0; i < BIT_VARIATIONS; i++) al_destroy_bitmap(imgBit[i]);
	for (int i = 0; i < BACKGROUND_VARIATIONS; i++) al_destroy_bitmap(imgBackground[i]);
	for (int i = 0; i < LEVEL_OBJECT_VARIATIONS; i++) al_destroy_bitmap(imgLevelObject[i]);
}

void Resources::loadEverything()
{
	fontNormal = al_load_font("./gfx/DejaVuSans.ttf", 24, 0);
	fontBig = al_load_font("./gfx/DejaVuSans.ttf", 64, 0);

	imgTitle = al_load_bitmap("./gfx/title.png");

	imgObstacle[0] = al_load_bitmap("./gfx/little rock.png");
	imgObstacle[1] = al_load_bitmap("./gfx/rock.png");
	imgObstacle[2] = al_load_bitmap("./gfx/rock middle-sized.png");
	
	imgPlayer[0] = al_load_bitmap("./gfx/killa.png");

	imgVictim[0] = al_load_bitmap("./gfx/smiled bacteria.png");
	imgVictim[1] = al_load_bitmap("./gfx/wounded.png");
	imgExplosion[0] = al_load_bitmap("./gfx/explosion00.png");
	imgExplosion[1] = al_load_bitmap("./gfx/explosion01.png");
	imgExplosion[2] = al_load_bitmap("./gfx/explosion02.png");
	imgExplosion[3] = al_load_bitmap("./gfx/explosion03.png");
	imgExplosion[4] = al_load_bitmap("./gfx/explosion04.png");
	imgExplosion[5] = al_load_bitmap("./gfx/explosion05.png");

	imgWeapon[0] = al_load_bitmap("./gfx/gun - left.png");
	imgWeapon[1] = al_load_bitmap("./gfx/bazooka.png");
	imgWeapon[2] = al_load_bitmap("./gfx/lasergun.png");

	imgBullet[0] = al_load_bitmap("./gfx/bullet00.png");
	imgBullet[1] = al_load_bitmap("./gfx/bullet01.png");
	imgBullet[2] = al_load_bitmap("./gfx/bullet02.png");
	imgBullet[3] = al_load_bitmap("./gfx/bullet03.png");
	
	imgFlame[0] = al_load_bitmap("./gfx/flame00.png");
	imgFlame[1] = al_load_bitmap("./gfx/flame01.png");
	imgFlame[2] = al_load_bitmap("./gfx/flame02.png");
	imgFlame[3] = al_load_bitmap("./gfx/flame03.png");
	imgFlame[4] = al_load_bitmap("./gfx/flame04.png");
	imgFlame[5] = al_load_bitmap("./gfx/flame05.png");
	imgFlame[6] = al_load_bitmap("./gfx/flame06.png");
	imgFlame[7] = al_load_bitmap("./gfx/flame07.png");
	imgFlame[8] = al_load_bitmap("./gfx/flame08.png");
	imgFlame[9] = al_load_bitmap("./gfx/flame09.png");
	imgFlame[10] = al_load_bitmap("./gfx/flame10.png");
	imgFlame[11] = al_load_bitmap("./gfx/flame11.png");
	imgFlame[12] = al_load_bitmap("./gfx/flame12.png");
	
	imgFood[0] = al_load_bitmap("./gfx/cola.png");
	imgFood[1] = al_load_bitmap("./gfx/hot dog.png");
	imgFood[2] = al_load_bitmap("./gfx/banana.png");
	
	imgBit[0] = al_load_bitmap("./gfx/bit.png");
	
	imgBackground[0] = al_load_bitmap("./gfx/background 2.png");
	imgBackground[1] = al_load_bitmap("./gfx/background 3.png");
	
	imgLevelObject[0] = al_load_bitmap("./gfx/little rock.png");
	imgLevelObject[1] = al_load_bitmap("./gfx/rock middle-sized.png");
	imgLevelObject[2] = al_load_bitmap("./gfx/rock.png");
}

