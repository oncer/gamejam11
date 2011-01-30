#include <iostream>
#include "collisionchecker.h"
#include "level.h"
#include "audio.h"

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
	explodeAudioDelay = 0;
}

bool CollisionChecker::canMoveTo(PixelCoords position, int w, int h) {
	for (LevelObjectList::iterator it = level->levelObjects->begin(); it != level->levelObjects->end(); it++) {
		LevelObject *lob = *it;
		if (boxCollision(lob->position, position, lob->w, lob->h,
			w, h)) {
			return false;
		}
	}
	return true;
}

bool CollisionChecker::playerCanMoveTo(PixelCoords position)
{
	return canMoveTo(position, PLAYER_WIDTH, PLAYER_HEIGHT);
}

bool CollisionChecker::foodCanMoveTo(PixelCoords position)
{
	return canMoveTo(position, FOOD_WIDTH, FOOD_HEIGHT);
}

bool CollisionChecker::projectileCanMoveTo(PixelCoords position)
{
	return canMoveTo(position, PROJECTILE_WIDTH, PROJECTILE_HEIGHT);
}

bool CollisionChecker::victimCanMoveTo(PixelCoords position)
{
	return canMoveTo(position, VICTIM_WIDTH, VICTIM_HEIGHT);
}

void CollisionChecker::playerPickupWeapon()
{
	for (WeaponList::iterator it = level->weapons->begin(); it != level->weapons->end(); it++) {
		Weapon* weapon = *it;
		if (weapon->isConsumed || weapon->isDead) {
			continue;
		}
		if (boxCollision(level->player->position, weapon->position, PLAYER_WIDTH, PLAYER_HEIGHT, WEAPON_WIDTH, WEAPON_HEIGHT)) {
			level->player->changeWeapon(weapon->weaponType);
			weapon->getPickedUp();
		}
	}
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
				Game::globalGame->score += Game::SCORE_FOOD;
			}
			food->getEaten();
		}
	}
}

void CollisionChecker::victimPickupFood()
{
	size_t operations = 0;
	
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
				food->getEaten();
			}
			if (operations++ >= OPERATIONS_CAP) {
				return; // ignore remaining checks
			}
		}
	}
}

void CollisionChecker::playerVsVictim()
{
	explodeAudioDelay--;
	for (VictimList::iterator it = level->victims->begin(); it != level->victims->end(); it++) {
		Victim* victim = *it;
		if (victim->isDying || victim->isDead) {
			continue;
		}
		if (boxCollision(level->player->position, victim->position, PLAYER_WIDTH, PLAYER_HEIGHT, VICTIM_WIDTH, VICTIM_HEIGHT)) {
			victim->explode();
			if (explodeAudioDelay <= 0) {
				Audio::playSFX(Audio::SFX_DEATH);
				explodeAudioDelay = 5;
			}
		}
	}
}

void CollisionChecker::victimVsLaser()
{
	Laser* laser = level->laser;
	if (!laser->active) {
		return;
	}
	
	for (VictimList::iterator it = level->victims->begin(); it != level->victims->end(); it++) {
		Victim* victim = *it;
		if (victim->isDying || victim->isDead) {
			continue;
		}
		
		PixelCoords partitionPos = laser->from;
		float dx = ((float) laser->to.x - laser->from.x) / LASER_PARTITIONS;
		float dy = ((float) laser->to.y - laser->from.y) / LASER_PARTITIONS;
			
		for (int i = 0; i < LASER_PARTITIONS; i++) {
			if (boxCollision(victim->position, partitionPos, VICTIM_WIDTH, VICTIM_HEIGHT, LASER_FIELD_SIZE, LASER_FIELD_SIZE)) {
				victim->explode();
				if (explodeAudioDelay <= 0) {
					Audio::playSFX(Audio::SFX_DEATH);
					explodeAudioDelay = 5;
				}
				Game::globalGame->score += Game::SCORE_KILL;
				break; // try next victim
			}
			
			partitionPos.x += dx;
			partitionPos.y += dy;
		}
	}
}

void CollisionChecker::victimVsProjectile()
{
	size_t operations = 0;
	
	for (VictimList::iterator it = level->victims->begin(); it != level->victims->end(); it++) {
		Victim* victim = *it;
		if (victim->isDying || victim->isDead) {
			continue;
		}
		
		for (ProjectileList::iterator it = level->projectiles->begin(); it != level->projectiles->end(); it++) {
			Projectile* projectile = *it;
			if (projectile->isDead) {
				continue;
			}
			
			if (boxCollision(victim->position, projectile->position, VICTIM_WIDTH, VICTIM_HEIGHT, PROJECTILE_WIDTH, PROJECTILE_HEIGHT)) {
				projectile->isDead = true;
				victim->explode();
				if (explodeAudioDelay <= 0) {
					Audio::playSFX(Audio::SFX_DEATH);
					explodeAudioDelay = 5;
				}
				Game::globalGame->score += Game::SCORE_KILL;
			}
			
			if (operations++ >= OPERATIONS_CAP) {
				return; // ignore remaining checks
			}
		}
	}
}

