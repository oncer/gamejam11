#include <allegro5/allegro5.h>
#include <iostream>
#include <math.h>
#include "victim.h"
#include "bullet.h"
#include "resources.h"
#include "level.h"

Bullet::Bullet(PixelCoords pos)
{
	position = pos;
	isDead = false;
	steps = 0;
	maxSteps = 60;
	dx = dy = 0;
	isDead = false;
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
	CollisionChecker *c = Game::globalGame->collisionChecker;
	position.x += dx;
	if (!c->bulletCanMoveTo(position)) {
		position.x -= dx;
		dx = -dx;
	}
	position.y += dy;
	if (!c->bulletCanMoveTo(position)) {
		position.y -= dy;
		dy = -dy;
	}

	steps++;
	if (steps > maxSteps) {
		isDead = true;
	}
}
