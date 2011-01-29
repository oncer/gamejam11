#include <allegro5/allegro5.h>
#include "level.h"

Level::Level()
{
	player = new Player((PixelCoords) {225, 40});
	victims = new VictimList();
	levelObjects = new LevelObjectList();
	bullets = new BulletList();
	
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
	if (player->canMove()) {
		player->doMove();
	}
	player->nextAnimFrame();
	
	for (VictimList::iterator it = victims->begin(); it != victims->end(); it++) {
		Victim* victim = *it;
		if (victim->canMove()) {
			victim->doMove();
		}
		victim->nextAnimFrame();
	}
	
	for (BulletList::iterator it = bullets->begin(); it != bullets->end(); it++) {
		Bullet* bullet = *it;
		if (bullet->canMove()) {
			bullet->doMove();
		}
		bullet->nextAnimFrame();
	}
	
	for (BulletList::iterator it = bullets->begin(); it != bullets->end();) {
		Bullet* bullet = *it;
		if (bullet->dead) {
			it = bullets->erase(it);
			delete bullet;
		}
		else
			it++;
	}
}

void Level::draw()
{
	al_clear_to_color(al_map_rgb(127, 127, 127));
	player->draw();
	for (VictimList::iterator it = victims->begin(); it != victims->end(); it++) {
		(*it)->draw();
	}
}
