#include <allegro5/allegro5.h>
#include <cstdlib>
#include <math.h>
#include <iostream>
#include "level.h"

#include <stdio.h>

Level::Level()
{
	player = new Player((PixelCoords) {225, 40});
	victims = new VictimList();
	levelObjects = new LevelObjectList();
	projectiles = new ProjectileList();
	foods = new FoodList();
	weapons = new WeaponList();

	levelNumber = 0;
	ticks = 0;
	pixelWidth = 640;  // TODO: dynamic
	pixelHeight = 480; // TODO: dynamic
	foodInterval = BASE_FOOD_INTERVAL;
	foodTimer = foodInterval;

}

void Level::create(int num) {
	levelNumber = num;
	levelBackground = num % 2;
	
	/* DEMO CODE */
	/*
	Resources* resources = Resources::instance();
	victims->push_back(new Victim((PixelCoords) {50, 50}));
	victims->push_back(new Victim((PixelCoords) {500, 30}));
	background = 0;
	pixelWidth = al_get_bitmap_width(resources->imgLevelBackground[background]);
	pixelHeight = al_get_bitmap_height(resources->imgLevelBackground[background]);
	*/
	if (num == 1) {
		victims->push_back(new Victim((PixelCoords) {50, 50}));
		victims->push_back(new Victim((PixelCoords) {500, 30}));
		
		levelObjects->push_back(new LevelObject((PixelCoords) {100, 200}, 1));
		
		for (int i = 0; i < 4; i++)
			levelObjects->push_back(new LevelObject((PixelCoords) {200, 200 + i * 32}, 1));
	}
	else {
		for (int i = 0; i < 3 + num; i++) {
			victims->push_back(new Victim((PixelCoords) {
				40 + std::rand() % 580, 40 + std::rand() % 400}));
				
			LevelObject *lob = new LevelObject((PixelCoords) {
				40 + std::rand() % 580, 40 + std::rand() % 400}, std::rand() % 3);
			levelObjects->push_back(lob);
		}
	}
	
	// make sure player is not stuck
	while (1) {
		CollisionChecker *c = Game::globalGame->collisionChecker;
		if (c->playerCanMoveTo(player->position)) break;
		player->position.x = 40 + std::rand() % 580;
		player->position.y = 40 + std::rand() % 400;
	}
}

Level::~Level()
{
	delete player;
	delete victims;
	delete levelObjects;
	delete foods;
	delete weapons;
}

void Level::update()
{
	ticks++;
	
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
	
	player->doMove();
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
			if (victim->splitAgain)
				victim->splitAgain--;
			else {
				victims->push_back(new Victim(victim->split()));
			}
		}
		victim->nextAnimFrame();
	}

	for (ProjectileList::iterator it = projectiles->begin(); it != projectiles->end(); it++) {
		Projectile* projectile = *it;
		if (projectile->canMove()) {
			projectile->doMove();
		}
		projectile->nextAnimFrame();
	}

	for (ProjectileList::iterator it = projectiles->begin(); it != projectiles->end();) {
		Projectile* projectile = *it;
		if (projectile->isDead) {
			it = projectiles->erase(it);
			delete projectile;
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
	
	// spawn weapons?
	if ((levelNumber >= FLAMETHROWER_FIRST_LEVEL) && (ticks == FLAMETHROWER_SPAWN_TIME)) {
		weapons->push_back(new Weapon(WEAPON_FLAMETHROWER, randomLevelCoords()));
	}
	if ((levelNumber >= LASER_FIRST_LEVEL) && (ticks == LASER_SPAWN_TIME)) {
		// TODO: spawn WEAPON_LASER when implemented
		weapons->push_back(new Weapon(WEAPON_FLAMETHROWER, randomLevelCoords())); 
	}
	
	// player hunger increases
	player->increaseHunger();
	
	// level shake
	shakeAngle += shakeRotation;
	shakeIntensity *= 0.9;
	shakeRotation *= 0.9;
}

void Level::draw()
{
	ALLEGRO_BITMAP* targetBackup = al_get_target_bitmap();
	int width = al_get_bitmap_width(targetBackup);
	int height = al_get_bitmap_height(targetBackup);
	
	// shake
	float offsetX = ((ticks % 2)*2-1) * cos(shakeAngle) * shakeIntensity;
	float offsetY = ((ticks % 2)*2-1) * sin(shakeAngle) * shakeIntensity;
	
	ALLEGRO_BITMAP *drawingTarget = al_create_sub_bitmap(targetBackup,
		offsetX, offsetY, width + offsetX, height + offsetY);
	al_set_target_bitmap(drawingTarget);
	
	Resources* resources = Resources::instance();
	
	// Background
	ALLEGRO_BITMAP* img = resources->imgBackground[levelBackground];
	float sw = al_get_bitmap_width(img);
	float sh = al_get_bitmap_height(img);
	al_draw_scaled_bitmap(img, 0, 0, sw, sh, 0, 0, pixelWidth, pixelHeight, 0);
	
	// Level objects (walls)
	for (LevelObjectList::iterator it = levelObjects->begin(); it != levelObjects->end(); it++) {
		(*it)->draw();
	}
	
	// Food objects
	for (FoodList::iterator it = foods->begin(); it != foods->end(); it++) {
		(*it)->draw();
	}
	
	// Weapon objects
	for (WeaponList::iterator it = weapons->begin(); it != weapons->end(); it++) {
		(*it)->draw();
	}
	
	// Moving actors: Victims & Player
	for (VictimList::iterator it = victims->begin(); it != victims->end(); it++) {
		(*it)->draw();
	}
	player->draw();
	
	for (ProjectileList::iterator it = projectiles->begin(); it != projectiles->end(); it++) {
		(*it)->draw();
	}

	al_set_target_bitmap(targetBackup);
	al_destroy_bitmap(drawingTarget);
}

void Level::shake()
{
	shakeIntensity += SHAKE_INTENSITY_GAIN * rand() / RAND_MAX;
	if (shakeIntensity > SHAKE_INTENSITY_MAX) shakeIntensity = SHAKE_INTENSITY_MAX;
	shakeRotation += ((2.0 * SHAKE_ROTATION_GAIN) - SHAKE_ROTATION_GAIN) * rand() / RAND_MAX;
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
