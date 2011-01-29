#include <allegro5/allegro5.h>
#include <math.h>
#include "level.h"

Level::Level()
{
	player = new Player();
	victims = new VictimList();
	levelObjects = new LevelObjectList();
	foods = new FoodList();
	
	pixelWidth = 640;  // TODO: dynamic
	pixelHeight = 480; // TODO: dynamic
	foodInterval = BASE_FOOD_INTERVAL;
	foodTimer = foodInterval;
	
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
	// move and animate everything, remove dead weight where necessary
	for (FoodList::iterator it = foods->begin(); it != foods->end(); it++) {
		Food* food = *it;
		while (food->isDead) {
			it = foods->erase(it);
			if (it == foods->end()) break;
			food = *it;
		}
		if (it == foods->end()) break;
		food->nextAnimFrame();
	}
	
	if (player->canMove()) {
		player->doMove();
	}
	player->nextAnimFrame();
	
	for (VictimList::iterator it = victims->begin(); it != victims->end(); it++) {
		Victim* victim = *it;
		while (victim->isDead) {
			it = victims->erase(it);
			if (it == victims->end()) break;
			victim = *it;
		}
		if (it == victims->end()) break;
		if (victim->canMove()) {
			victim->doMove();
		}
		victim->nextAnimFrame();
	}
	
	// spawn food?
	foodTimer--;
	if (foodTimer <= 0) {
		spawnFood();
		foodTimer = foodInterval;
	}
	
	// player hunger increases
	player->increaseHunger();
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
	foods->push_back(new Food(randomLevelCoords(), 1000));
}

PixelCoords Level::randomLevelCoords()
{
	PixelCoords c;
	c.x = rand() % pixelWidth;
	c.y = rand() % pixelHeight;
	return c;
}
