#include "resources.h"

Resources* Resources::theInstance = NULL;

Resources* Resources::instance()
{
	if (theInstance == NULL) {
		theInstance = new Resources();
	}
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
	imgTitle = NULL;
	memset(imgPlayer, 0, PLAYER_FRAMES * sizeof(ALLEGRO_BITMAP*));
	memset(imgVictim, 0, VICTIM_FRAMES * sizeof(ALLEGRO_BITMAP*));
	memset(imgExplosion, 0, EXPLOSION_FRAMES * sizeof(ALLEGRO_BITMAP*));
	memset(imgullet, 0, BULLET_FRAMES * sizeof(ALLEGRO_BITMAP*));
	memset(imgBit, 0, BIT_VARIATIONS * sizeof(ALLEGRO_BITMAP*));
>>>>>>> 313e4c50e9a7992c51c64ef55192399df30995bb
}

Resources::~Resources()
{
	al_destroy_bitmap(imgTitle);
	for (int i = 0; i < PLAYER_FRAMES; i++) al_destroy_bitmap(imgPlayer[i]);
	for (int i = 0; i < VICTIM_FRAMES; i++) al_destroy_bitmap(imgVictim[i]);
	for (int i = 0; i < BULLET_FRAMES; i++) al_destroy_bitmap(imgBullet[i]);
	for (int i = 0; i < EXPLOSION_FRAMES; i++) al_destroy_bitmap(imgExplosion[i]);
	for (int i = 0; i < BIT_VARIATIONS; i++) al_destroy_bitmap(imgBit[i]);
	
}

void Resources::loadEverything()
{
	imgTitle = al_load_bitmap("./gfx/title.png");
	imgPlayer[0] = al_load_bitmap("./gfx/player.png");
<<<<<<< HEAD
	imgVictim[0] = al_load_bitmap("./gfx/victim.png");
	imgBullet[0] = al_load_bitmap("./gfx/bullet.png");
=======
	imgVictim[0] = al_load_bitmap("./gfx/smiled bacteria.png");
	imgVictim[1] = al_load_bitmap("./gfx/wounded.png");
	imgExplosion[0] = al_load_bitmap("./gfx/death.png");
	imgBullet = al_load_bitmap("./gfx/bullet.png");
>>>>>>> 313e4c50e9a7992c51c64ef55192399df30995bb
	imgBit[0] = al_load_bitmap("./gfx/bit.png");
}

