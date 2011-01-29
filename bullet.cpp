#include <allegro5/allegro5.h>
#include <iostream>
#include <math.h>
#include "victim.h"
#include "bullet.h"
#include "resources.h"
#include "level.h"

Bullet::Bullet(PixelCoords pos)
    :bulletAnim(4, Resources::BULLET_FRAMES, true)
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
    bulletAnim.update();
}

void Bullet::draw()
{
	Resources* resources = Resources::instance();
	int currentFrame = bulletAnim.getCurrentFrame();
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
        isDead = true;
    }
}
