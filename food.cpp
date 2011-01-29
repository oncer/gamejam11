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
	al_draw_bitmap(resources->imgFood[variation], position.x, position.y, 0);
}
