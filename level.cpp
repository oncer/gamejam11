#include <allegro5/allegro5.h>
#include <math.h>
#include "level.h"

#include <stdio.h>

Level::Level()
{
	player = new Player((PixelCoords) {225, 40});
	victims = new VictimList();
	levelObjects = new LevelObjectList();

	bullets = new BulletList();

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
			delete food;
			it = foods->erase(it);
			if (it == foods->end()) break;
			food = *it;
		}
		if (it == foods->end()) break;
		food->doMove();
		food->nextAnimFrame();
	}
	
	if (player->canMove()) {
		player->doMove();
	}
	player->update();
	player->nextAnimFrame();
	
	for (VictimList::iterator it = victims->begin(); it != victims->end(); it++) {
		Victim* victim = *it;
		while (victim->isDead) {
			delete victim;
			it = victims->erase(it);
			if (it == victims->end()) break;
			victim = *it;
		}
		if (it == victims->end()) break;
		if (victim->canMove()) {
			victim->doMove();
		}
		if (victim->splitCountdown <= 0) {
			victims->push_back(new Victim(victim->split()));
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
		if (bullet->isDead) {
			it = bullets->erase(it);
			delete bullet;
		}
		else
			it++;
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
	
	for (BulletList::iterator it = bullets->begin(); it != bullets->end(); it++) {
		(*it)->draw();
	}
}

bool Level::isInLevelBoundaries(PixelCoords coords)
{
	if (coords.x < BORDER_ZONE) return false;
	if (coords.y < BORDER_ZONE) return false;
	if (coords.x > pixelWidth - BORDER_ZONE) return false;
	if (coords.y > pixelWidth - BORDER_ZONE) return false;
	
	return true;
}

void Level::spawnFood()
{
	int variation = rand() % Resources::FOOD_VARIATIONS;
	PixelCoords position = randomLevelCoords();
	foods->push_back(new Food(variation, position, 1000));
}

PixelCoords Level::randomLevelCoords()
{
	PixelCoords c;
	c.x = rand() % pixelWidth;
	c.y = rand() % pixelHeight;
	return c;
}
