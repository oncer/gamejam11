#include <allegro5/allegro5.h>
#include "victim.h"
#include "resources.h"

Victim::Victim(PixelCoords pos)
{
	position = pos;
}

void Victim::nextAnimFrame()
{
}

void Victim::draw()
{
	Resources* resources = Resources::instance();
	int currentFrame = 0;
	ALLEGRO_BITMAP* currentFrameImg = resources->imgVictim[currentFrame];
	al_draw_bitmap(currentFrameImg, position.x, position.y, 0);
}

bool Victim::canMove()
{
	// TODO: collision check (use CollisionChecker or something as parameter)
	return true;
}

void Victim::doMove()
{
	position.x += 
	
	if (position == target) {
		/* TODO: decide and plan actions here */
		plan = PLAN_WANDER;
		target = (PixelCoords) { target.x + 130 % 600, target.y + 30 % 600 };
	}
}
