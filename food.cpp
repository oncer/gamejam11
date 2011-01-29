#include "food.h"
#include "resources.h"

Food::Food(PixelCoords pos)
{
	position = pos;
}

void Food::nextAnimFrame()
{
}

void Food::draw()
{
	Resources* resources = Resources::instance();
	int currentFrame = 0;
	ALLEGRO_BITMAP* currentFrameImg = resources->imgExplosion[currentFrame];
	al_draw_bitmap(currentFrameImg, position.x, position.y, 0);
}
