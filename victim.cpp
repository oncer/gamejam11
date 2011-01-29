#include <allegro5/allegro5.h>
#include "victim.h"
#include "resources.h"

Victim::Victim(PixelCoords pos)
{
	position = pos;
}

void Victim::draw()
{
	Resources* resources = Resources::instance();
	int currentFrame = 0;
	ALLEGRO_BITMAP* currentFrameImg = resources->imgVictim[currentFrame];
	al_draw_bitmap(currentFrameImg, position.x, position.y, 0);
}
