#include <allegro5/allegro5.h>
#include <iostream>
#include <math.h>
#include "victim.h"
#include "flame.h"
#include "resources.h"
#include "level.h"

Flame::Flame(PixelCoords pos)
    : Projectile(pos), flameAnim(5, Resources::FLAME_FRAMES, false)
{
}
Flame::~Flame() {}

void Flame::nextAnimFrame()
{
    flameAnim.update();
}

void Flame::draw()
{
	float alpha = 1.;
	
	Resources* resources = Resources::instance();
	int currentFrame = flameAnim.getCurrentFrame();
	if (currentFrame >= Resources::FLAME_FRAMES) {
		currentFrame = Resources::FLAME_FRAMES-1;
	}
	if (currentFrame >= Resources::FLAME_FRAMES*0.75) {
		// fade out
		alpha = 1- ((((float)currentFrame) / Resources::FLAME_FRAMES) - 0.75) * 4;
	}
	ALLEGRO_BITMAP* img = resources->imgFlame[currentFrame];
	PixelCoords imgPos = antiCenter(position, al_get_bitmap_width(img), al_get_bitmap_height(img));
	al_draw_tinted_bitmap(img, al_map_rgba_f(alpha, alpha, alpha, alpha), imgPos.x, imgPos.y, 0);
}

float Flame::getBaseSpeed()
{
	return Flame::BASE_SPEED;
}

void Flame::onHitVictim()
{
    Projectile::onHitVictim();
}

