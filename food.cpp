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
	dx = dy = 0;
}

void Food::nextAnimFrame()
{
	if (isConsumed) isDead = true; // TODO: die animation
}

void Food::doMove()
{
	float d = dx * dx + dy * dy;
	if (d > 0.1) {
		position.x += dx;
		position.y += dy;
		dx *= 0.95;
		dy *= 0.95;
	}
	else {
		dx = 0;
		dy = 0;
	}
}

void Food::draw()
{
	Resources* resources = Resources::instance();
	al_draw_bitmap(isPlayerEdible ? resources->imgFood[variation] :
		resources->imgBit[variation], position.x, position.y, 0);
}
