#include "levelobject.h"
#include "resources.h"
#include "collisionchecker.h"

LevelObject::LevelObject(PixelCoords pos, int var) {
	position = pos;
	variation = var;
	switch (var) {
		case 0:
			w = CollisionChecker::BLOCK_WIDTH0;
			h = CollisionChecker::BLOCK_HEIGHT0;
			break;
		case 1:
			w = CollisionChecker::BLOCK_WIDTH1;
			h = CollisionChecker::BLOCK_HEIGHT1;
			break;
		case 2:
			w = CollisionChecker::BLOCK_WIDTH2;
			h = CollisionChecker::BLOCK_HEIGHT2;
			break;
	}
}

void LevelObject::draw() {
	Resources* resources = Resources::instance();
	ALLEGRO_BITMAP* img = resources->imgLevelObject[variation];
	PixelCoords imgPos = antiCenter(position, al_get_bitmap_width(img), al_get_bitmap_height(img));
	al_draw_bitmap(img, imgPos.x, imgPos.y, 0);
}
