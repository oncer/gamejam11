#include <allegro5/allegro5.h>
#include <math.h>
#include "victim.h"
#include "resources.h"

Victim::Victim(PixelCoords pos)
{
	position = pos;
	target = position;
	plan = PLAN_WANDER;
	speed = BASE_SPEED;
	isDying = false;
	isDead = false;
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

void Victim::feed(int foodValue)
{
	// TODO: after a certain amount of food, the victim splits
}

bool Victim::canMove()
{
	if (isDead) return false;
	// TODO: collision check (use CollisionChecker or something as parameter)
	return true;
}

void Victim::doMove()
{
	float dir_x = target.x - position.x;
	float dir_y = target.y - position.y;
	float dir_w = sqrt(dir_x * dir_x + dir_y * dir_y);
	
	if (dir_w > 1) {
		position.x += dir_x / dir_w;
		position.y += dir_y / dir_w;
	}
	else {
		position = target;
	}

	if (position == target) {
		/* TODO: decide and plan actions here */
		plan = PLAN_WANDER;
		target = (PixelCoords) { (int)(target.x + 130) % 600, (int)(target.y + 30) % 600 };
	}
}
