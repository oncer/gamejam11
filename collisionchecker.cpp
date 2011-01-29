#include "collisionchecker.h"
#include "level.h"

bool boxCollision (PixelCoords p1, PixelCoords p2, int w1, int h1, int w2, int h2)
{
	if ((p1.x - w1/2 < p2.x + w2/2) && (p2.x - w2/2 < p1.x + w1/2) && 
	    (p1.y - h1/2 < p2.y + h2/2) && (p2.y - h2/2 < p1.y + h1/2)) {
		return true;
	}
	else {
		return false;
	}
}

CollisionChecker::CollisionChecker(Level* lvl)
{
	level = lvl;
}

bool CollisionChecker::playerCanMoveTo(PixelCoords position)
{
	/* TODO: level objects not implemented yet
	for (LevelObjectList::iterator it = level->levelObjects->begin(); it != level->levelObjects->end(); it++) {
		if (boxCollision()) {
			return false;
		}
	}*/
	return true;
}

bool CollisionChecker::victimCanMoveTo(PixelCoords position)
{
	/* TODO: level objects not implemented yet
	for (LevelObjectList::iterator it = level->levelObjects->begin(); it != level->levelObjects->end(); it++) {
		if (boxCollision()) {
			return false;
		}
	}*/
	return true;
}

void CollisionChecker::playerPickupFood()
{
	for (FoodList::iterator it = level->foods->begin(); it != level->foods->end(); it++) {
		Food* food = *it;
		if (food->isConsumed || food->isDead) {
			continue;
		}
		if (boxCollision(level->player->position, food->position, PLAYER_WIDTH, PLAYER_HEIGHT, FOOD_WIDTH, FOOD_HEIGHT)) {
			if (food->isPlayerEdible) {
				level->player->feed(food->value);
			}
			food->isConsumed = true;
		}
	}
}

void CollisionChecker::victimPickupFood()
{
	for (VictimList::iterator it = level->victims->begin(); it != level->victims->end(); it++) {
		Victim* victim = *it;
		if (victim->isDying || victim->isDead) {
			continue;
		}
		for (FoodList::iterator it = level->foods->begin(); it != level->foods->end(); it++) {
			Food* food = *it;
			if (food->isConsumed || food->isDead) {
				continue;
			}
			if (boxCollision(victim->position, food->position, VICTIM_WIDTH, VICTIM_HEIGHT, FOOD_WIDTH, FOOD_HEIGHT)) {
				victim->feed(food->value);
				food->isConsumed = true;
			}
		}
	}
}

void CollisionChecker::playerVsVictim()
{
	for (VictimList::iterator it = level->victims->begin(); it != level->victims->end(); it++) {
		Victim* victim = *it;
		if (victim->isDying || victim->isDead) {
			continue;
		}
		if (boxCollision(level->player->position, victim->position, PLAYER_WIDTH, PLAYER_HEIGHT, VICTIM_WIDTH, VICTIM_HEIGHT)) {
			victim->isDying = true;
		}
	}
}

void CollisionChecker::victimVsBullet()
{
	for (VictimList::iterator it = level->victims->begin(); it != level->victims->end(); it++) {
		Victim* victim = *it;
		if (victim->isDying || victim->isDead) {
			continue;
		}
		
		for (BulletList::iterator it = level->bullets->begin(); it != level->bullets->end(); it++) {
			Bullet* bullet = *it;
			if (bullet->dead) {
				continue;
			}
			
			if (boxCollision(victim->position, bullet->position, VICTIM_WIDTH, VICTIM_HEIGHT, BULLET_WIDTH, BULLET_HEIGHT)) {
				victim->isDying = true;
				bullet->dead = true;
			}
		}
	}
}
