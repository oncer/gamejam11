#include "food.h"
#include "resources.h"
#include "level.h"

Food::Food(int var, PixelCoords pos, int val, bool playerEdible)
{
	variation = var;
	position = pos;
	value = val;
	isPlayerEdible = playerEdible;
	isConsumed = false;
	isDead = false;
	dx = dy = 0;
	animCountdown = SPAWN_ANIM_TIME;
}

void Food::nextAnimFrame()
{
	if (animCountdown > 0) animCountdown--;
	if (isConsumed && (animCountdown <= 0)) {
		animCountdown = 0;
		isDead = true;
	}
}

void Food::getEaten()
{
	isConsumed = true;
	animCountdown = DEATH_ANIM_TIME;
}

void Food::doMove()
{
	float d = dx * dx + dy * dy;
	if (d > 0.1) {
		CollisionChecker *c = Game::globalGame->collisionChecker;
		Level *level = Game::globalGame->currentLevel;
		position.x += dx;
		if (!c->foodCanMoveTo(position)) {
			position.x -= dx;
			dx = -dx;
		}
		position.y += dy;
		if (!c->foodCanMoveTo(position)) {
			position.y -= dy;
			dy = -dy;
		}
		dx *= 0.95;
		dy *= 0.95;
		if (position.x > level->pixelWidth - Level::BORDER_ZONE) {
			if (dx > 0) dx = -dx;
			position.x = level->pixelWidth - Level::BORDER_ZONE;
		}
		if (position.y > level->pixelHeight - Level::BORDER_ZONE) {
			if (dy > 0) dy = -dy;
			position.y = level->pixelHeight - Level::BORDER_ZONE;
		}
		if (position.x < Level::BORDER_ZONE) {
			if (dx < 0) dx = -dx;
			position.x = Level::BORDER_ZONE;
		}
		if (position.y < Level::BORDER_ZONE) {
			if (dy < 0) dy = -dy;
			position.y = Level::BORDER_ZONE;
		}
	}
	else {
		dx = 0;
		dy = 0;
	}
}

void Food::draw()
{
	Resources* resources = Resources::instance();
	ALLEGRO_BITMAP** imageCollection;
	
	if (isPlayerEdible) {
		imageCollection = resources->imgFood;
	}
	else {
		imageCollection = resources->imgBit;
	}
	
	ALLEGRO_BITMAP* img = imageCollection[variation];
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
	al_draw_tinted_scaled_bitmap(img, al_map_rgba_f(1, 1, 1, tintAlpha), 
		0, 0, baseWidth, baseHeight, imgPos.x, imgPos.y, scaleWidth, scaleHeight, 0);
}
