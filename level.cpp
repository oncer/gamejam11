#include <allegro5/allegro5.h>
#include <math.h>
#include "level.h"

Level::Level()
{
	player = new Player((PixelCoords) {225, 40});
	victims = new VictimList();
	levelObjects = new LevelObjectList();
<<<<<<< HEAD
	bullets = new BulletList();
=======
	foods = new FoodList();
	
	pixelWidth = 640;  // TODO: dynamic
	pixelHeight = 480; // TODO: dynamic
	foodInterval = BASE_FOOD_INTERVAL;
	foodTimer = foodInterval;
>>>>>>> 313e4c50e9a7992c51c64ef55192399df30995bb
	
	/* DEMO CODE */
	victims->push_back(new Victim((PixelCoords) {50, 50}));
	victims->push_back(new Victim((PixelCoords) {500, 30}));
}

Level::~Level()
{
	delete player;
	delete victims;
	delete levelObjects;
	delete foods;
}

void Level::update()
{
	// move and animate everything
	for (FoodList::iterator it = foods->begin(); it != foods->end(); it++) {
		(*it)->nextAnimFrame();
	}
	
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

	foodTimer--;
	if (foodTimer <= 0) {
		spawnFood();
		foodTimer = foodInterval;
	}
}

void Level::draw()
{
	// Background
	al_clear_to_color(al_map_rgb(127, 127, 127));
	
	// Food objects
	for (FoodList::iterator it = foods->begin(); it != foods->end(); it++) {
		(*it)->draw();
	}
	
	// Moving actors: Victims & Player
	for (VictimList::iterator it = victims->begin(); it != victims->end(); it++) {
		(*it)->draw();
	}
	player->draw();
}

void Level::spawnFood()
{
	foods->push_back(new Food(randomLevelCoords()));
}

PixelCoords Level::randomLevelCoords()
{
	PixelCoords c;
	c.x = rand() % pixelWidth;
	c.y = rand() % pixelHeight;
	return c;
}
