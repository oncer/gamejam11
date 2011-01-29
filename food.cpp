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
}

void Food::nextAnimFrame()
{
	if (isConsumed) isDead = true; // TODO: die animation
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
	PixelCoords imgPos = antiCenter(position, al_get_bitmap_width(img), al_get_bitmap_height(img));
	al_draw_bitmap(img, imgPos.x, imgPos.y, 0);
}
