#include <allegro5/allegro_primitives.h>
#include "hud.h"
#include "coords.h"

#define COLOR_HUNGERBORDER al_map_rgb(200, 220, 10)
#define COLOR_HUNGERBAR al_map_rgb(240, 30, 100)

const PixelCoords HUNGERBAR_POSITION = { 15, 15 };
const int HUNGERBAR_LENGTH = 100;
const int HUNGERBAR_HEIGHT = 14;

void Hud::draw()
{
	al_draw_filled_rectangle(HUNGERBAR_POSITION.x, HUNGERBAR_POSITION.y,
	                         HUNGERBAR_POSITION.x+HUNGERBAR_LENGTH, HUNGERBAR_POSITION.x+HUNGERBAR_HEIGHT,
	                         COLOR_HUNGERBORDER);     
	float hunger_part = (HUNGERBAR_LENGTH-4) * (1.0 - (float)hunger / maxHunger);
	if (hunger_part > 0) {
		al_draw_filled_rectangle(HUNGERBAR_POSITION.x+2, HUNGERBAR_POSITION.y+2,
		                         HUNGERBAR_POSITION.x+hunger_part, HUNGERBAR_POSITION.x+HUNGERBAR_HEIGHT-2,
		                         COLOR_HUNGERBAR);
	}
}

void Hud::setMaxHunger(int value)
{
	maxHunger = value;
}

void Hud::setHunger(int value)
{
	hunger = value;
}
