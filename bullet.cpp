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

bool Bullet::collideWithVictim(Victim *v) {
	return position.x < v->position.x + 32 &&
		position.y < v->position.y + 32 &&
		position.x > v->position.x &&
		position.y > v->position.y;
}

void Bullet::doMove()
{
	position.x += dx;
	position.y += dy;
	steps++;
	if (steps > maxSteps) {
		isDead = true;
	}
	
	VictimList *victims = Game::globalGame->currentLevel->victims;
	for (VictimList::iterator it = victims->begin(); it != victims->end(); it++) {
		Victim *v = *it;
		if (collideWithVictim(v)) {
			v->isDead = true;
		}
	}
}
