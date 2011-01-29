#include <allegro5/allegro5.h>
#include <iostream>
#include <math.h>
#include "bullet.h"
#include "resources.h"

Bullet::Bullet(PixelCoords pos)
{
	position = pos;
	dead = false;
	steps = 0;
	maxSteps = 240;
	dx = dy = 0;
	dead = false;
}

void Bullet::nextAnimFrame()
{
}

void Bullet::draw()
{
	Resources* resources = Resources::instance();
	int currentFrame = 0;
	ALLEGRO_BITMAP* currentFrameImg = resources->imgBullet[currentFrame];
	al_draw_bitmap(currentFrameImg, position.x, position.y, 0);
}

bool Bullet::canMove()
{
	// TODO: collision check (use CollisionChecker or something as parameter)
	return true;
}

void Bullet::doMove()
{
	position.x += dx;
	position.y += dy;
	steps++;
	if (steps > maxSteps) {
		dead = true;
	}
}
