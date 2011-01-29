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
	imgBullet = NULL;
	memset(imgBit, 0, BIT_VARIATIONS * sizeof(ALLEGRO_BITMAP*));
}

Resources::~Resources()
{
	al_destroy_bitmap(imgTitle);
	for (int i = 0; i < PLAYER_FRAMES; i++) al_destroy_bitmap(imgPlayer[i]);
	for (int i = 0; i < VICTIM_FRAMES; i++) al_destroy_bitmap(imgVictim[i]);
	for (int i = 0; i < EXPLOSION_FRAMES; i++) al_destroy_bitmap(imgExplosion[i]);
	al_destroy_bitmap(imgBullet);
	for (int i = 0; i < BIT_VARIATIONS; i++) al_destroy_bitmap(imgBit[i]);
	
}

void Resources::loadEverything()
{
	imgTitle = al_load_bitmap("./gfx/title.png");
	imgPlayer[0] = al_load_bitmap("./gfx/player.png");
	imgVictim[0] = al_load_bitmap("./gfx/smiled bacteria.png");
	imgVictim[1] = al_load_bitmap("./gfx/wounded.png");
	imgExplosion[0] = al_load_bitmap("./gfx/death.png");
	imgBullet = al_load_bitmap("./gfx/bullet.png");
	imgBit[0] = al_load_bitmap("./gfx/bit.png");
}

