#include "weapon.h"
#include "resources.h"
#include "level.h"

Weapon::Weapon(WeaponType type, PixelCoords pos)
{
	weaponType = type;
	position = pos;
	isConsumed = false;
	isDead = false;
	animCountdown = SPAWN_ANIM_TIME;
}

void Weapon::nextAnimFrame()
{
	if (animCountdown > 0) animCountdown--;
	if (isConsumed && (animCountdown <= 0)) {
		animCountdown = 0;
		isDead = true;
	}
}

void Weapon::getPickedUp()
{
	isConsumed = true;
	animCountdown = DEATH_ANIM_TIME;
}

void Weapon::doMove()
{
}

void Weapon::draw()
{
	Resources* resources = Resources::instance();
	ALLEGRO_BITMAP* img = resources->imgWeapon[weaponType];
	float baseWidth = al_get_bitmap_width(img);
	float baseHeight = al_get_bitmap_height(img);
	float scaleWidth = baseWidth;
	float scaleHeight = baseHeight;
	
	float tintAlpha = 1.0;
	
	if (isConsumed) {
		tintAlpha = ((float)animCountdown) / DEATH_ANIM_TIME;
		float scaling = 2.0 - tintAlpha;
		scaleWidth *= scaling;
		scaleHeight *= scaling;
	}
	else { // spawn animation until animCountdown==0
		float animPercent = 1.0 - ((float)animCountdown) / SPAWN_ANIM_TIME;
		float scaling = 1.0;
		if (animPercent < 0.75) {
			scaling = 2.0 * animPercent;
		}
		else {
			scaling = 1.2 * (2.0 - animPercent);
		}
		scaleWidth *= scaling;
		scaleHeight *= scaling;
	}
	PixelCoords imgPos = antiCenter(position, scaleWidth, scaleHeight);
	al_draw_tinted_scaled_bitmap(img, al_map_rgba_f(tintAlpha, tintAlpha, tintAlpha, tintAlpha), 
		0, 0, baseWidth, baseHeight, imgPos.x, imgPos.y, scaleWidth, scaleHeight, 0);
}
