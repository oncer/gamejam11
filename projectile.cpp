#include <allegro5/allegro5.h>
#include <iostream>
#include <math.h>
#include "victim.h"
#include "projectile.h"
#include "resources.h"
#include "level.h"

Projectile::Projectile(PixelCoords pos)
{
	position = pos;
	isDead = false;
	steps = 0;
	maxSteps = 60;
	dx = dy = 0;
}
Projectile::~Projectile() {}

bool Projectile::canMove()
{
	// TODO: collision check (use CollisionChecker or something as parameter)
	return true;
}

void Projectile::doMove()
{
	CollisionChecker *c = Game::globalGame->collisionChecker;
	position.x += dx;
	if (!c->projectileCanMoveTo(position)) {
		position.x -= dx;
		dx = -dx;
	}
	position.y += dy;
	if (!c->projectileCanMoveTo(position)) {
		position.y -= dy;
		dy = -dy;
	}

	steps++;
	if (steps > maxSteps) {
		isDead = true;
	}
}

void Projectile::onHitVictim()
{
}

