#include "resources.h"

Resources::Resources()
{
	imgPlayer[0] = NULL;
	imgVictim[0] = NULL;
	imgBullet = NULL;
	imgBit[0] = NULL;
}

Resources::~Resources()
{
	for (int i = 0; i < PLAYER_FRAMES; i++) al_destroy_bitmap(imgPlayer[i]);
	for (int i = 0; i < VICTIM_FRAMES; i++) al_destroy_bitmap(imgVictim[i]);
	al_destroy_bitmap(imgBullet);
	for (int i = 0; i < BIT_VARIATIONS; i++) al_destroy_bitmap(imgBit[i]);
	
}

void Resources::loadEverything()
{
	imgPlayer[0] = al_load_bitmap("./gfx/player.png");
	imgVictim[0] = al_load_bitmap("./gfx/victim.png");
	imgBullet = al_load_bitmap("./gfx/bullet.png");
	imgBit[0] = al_load_bitmap("./gfx/bit.png");
}

