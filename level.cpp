#include <allegro5/allegro5.h>
#include "level.h"

Level::Level()
{
	player = new Player();
	victims = new VictimList();
	levelObjects = new LevelObjectList();
	
	/* DEMO CODE */
	victims->push_back(new Victim((PixelCoords) {50, 50}));
	victims->push_back(new Victim((PixelCoords) {500, 30}));
}

Level::~Level()
{
	delete player;
	delete victims;
	delete levelObjects;
}

void Level::update()
{
}

void Level::draw()
{
	al_clear_to_color(al_map_rgb(127, 127, 127));
	player->draw();
	for (VictimList::iterator it = victims->begin(); it != victims->end(); it++) {
		(*it)->draw();
	}
}
