#include "levelobject.h"
#include "resources.h"

LevelObject::LevelObject(PixelCoords pos) {
	position = pos;
}

void LevelObject::draw() {
	Resources* resources = Resources::instance();
	int variation = 0;
	ALLEGRO_BITMAP* img = resources->imgLevelObject[variation];
	PixelCoords imgPos = antiCenter(position, al_get_bitmap_width(img), al_get_bitmap_height(img));
	al_draw_bitmap(img, imgPos.x, imgPos.y, 0);
}
