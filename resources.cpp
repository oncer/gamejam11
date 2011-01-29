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
	memset(imgBullet, 0, BULLET_FRAMES * sizeof(ALLEGRO_BITMAP*));
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
	for (int i = 0; i < PLAYER_FRAMES; i++) al_destroy_bitmap(imgPlayer[i]);
	for (int i = 0; i < VICTIM_FRAMES; i++) al_destroy_bitmap(imgVictim[i]);
	for (int i = 0; i < BULLET_FRAMES; i++) al_destroy_bitmap(imgBullet[i]);
	for (int i = 0; i < EXPLOSION_FRAMES; i++) al_destroy_bitmap(imgExplosion[i]);
	for (int i = 0; i < FOOD_VARIATIONS; i++) al_destroy_bitmap(imgFood[i]);
	for (int i = 0; i < BIT_VARIATIONS; i++) al_destroy_bitmap(imgBit[i]);
	for (int i = 0; i < BACKGROUND_VARIATIONS; i++) al_destroy_bitmap(imgBackground[i]);
	for (int i = 0; i < LEVEL_OBJECT_VARIATIONS; i++) al_destroy_bitmap(imgLevelObject[i]);
}

void Resources::loadEverything()
{
	fontNormal = al_load_font("./gfx/DejaVuSans.ttf", 12, 0);
	fontBig = al_load_font("./gfx/DejaVuSans.ttf", 64, 0);

	imgTitle = al_load_bitmap("./gfx/title.png");

	imgPlayer[0] = al_load_bitmap("./gfx/killa.png");

	imgVictim[0] = al_load_bitmap("./gfx/smiled bacteria.png");
	imgVictim[1] = al_load_bitmap("./gfx/wounded.png");
	imgExplosion[0] = al_load_bitmap("./gfx/death.png");
	imgBullet[0] = al_load_bitmap("./gfx/bullet.png");
	
	imgFood[0] = al_load_bitmap("./gfx/cola.png");
	imgFood[1] = al_load_bitmap("./gfx/hot dog.png");
	imgFood[2] = al_load_bitmap("./gfx/banana.png");
	
	imgBit[0] = al_load_bitmap("./gfx/bit.png");
	
	imgBackground[0] = al_load_bitmap("./gfx/background 2.png");
	imgBackground[1] = al_load_bitmap("./gfx/background 3.png");
	
	imgLevelObject[0] = al_load_bitmap("./gfx/rock.png");
}

