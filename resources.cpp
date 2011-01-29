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
	imgPlayer[0] = NULL;
	imgVictim[0] = NULL;
	imgBullet[0] = NULL;
	imgBit[0] = NULL;
}

Resources::~Resources()
{
	al_destroy_bitmap(imgTitle);
	for (int i = 0; i < PLAYER_FRAMES; i++) al_destroy_bitmap(imgPlayer[i]);
	for (int i = 0; i < VICTIM_FRAMES; i++) al_destroy_bitmap(imgVictim[i]);
	for (int i = 0; i < BULLET_FRAMES; i++) al_destroy_bitmap(imgBullet[i]);
	for (int i = 0; i < BIT_VARIATIONS; i++) al_destroy_bitmap(imgBit[i]);
	
}

void Resources::loadEverything()
{
	imgTitle = al_load_bitmap("./gfx/title.png");
	imgPlayer[0] = al_load_bitmap("./gfx/player.png");
	imgVictim[0] = al_load_bitmap("./gfx/victim.png");
	imgBullet[0] = al_load_bitmap("./gfx/bullet.png");
	imgBit[0] = al_load_bitmap("./gfx/bit.png");
}

