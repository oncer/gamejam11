#include "food.h"
#include "resources.h"

Food::Food(int var, PixelCoords pos, int val, bool playerEdible)
{
	variation = var;
	position = pos;
	value = val;
	isPlayerEdible = playerEdible;
	isConsumed = false;
	isDead = false;
}

void Food::nextAnimFrame()
{
	if (isConsumed) isDead = true; // TODO: die animation
}

void Food::draw()
{
	Resources* resources = Resources::instance();
	ALLEGRO_BITMAP* img = resources->imgFood[variation];
	PixelCoords imgPos = antiCenter(position, al_get_bitmap_width(img), al_get_bitmap_height(img));
	al_draw_bitmap(img, imgPos.x, imgPos.y, 0);
}
