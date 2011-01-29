#include "food.h"
#include "resources.h"

Food::Food(PixelCoords pos, int val, bool playerEdible)
{
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
	int currentFrame = 0;
	ALLEGRO_BITMAP* currentFrameImg = resources->imgExplosion[currentFrame];
	al_draw_bitmap(currentFrameImg, position.x, position.y, 0);
}
