#include <allegro5/allegro5.h>
#include <iostream>
#include <math.h>
#include "victim.h"
#include "bullet.h"
#include "resources.h"
#include "level.h"

Bullet::Bullet(PixelCoords pos)
    : Projectile(pos), bulletAnim(4, Resources::BULLET_FRAMES, true)
{
}
Bullet::~Bullet() {}

void Bullet::nextAnimFrame()
{
    bulletAnim.update();
}

void Bullet::draw()
{
	Resources* resources = Resources::instance();
	int currentFrame = bulletAnim.getCurrentFrame();	
	ALLEGRO_BITMAP* img = resources->imgBullet[currentFrame];
	PixelCoords imgPos = antiCenter(position, al_get_bitmap_width(img), al_get_bitmap_height(img));
	al_draw_bitmap(img, imgPos.x, imgPos.y, 0);
}

float Bullet::getBaseSpeed()
{
	return Bullet::BASE_SPEED;
}

void Bullet::onHitVictim()
{
	isDead = true;
}

