#include "ai.h"
#include "level.h"

AI::AI(Level* lvl)
{
	level = lvl;
}

void AI::planEverything()
{
	for (VictimList::iterator it = level->victims->begin(); it != level->victims->end(); it++) {
		Victim* victim = *it;
		if (victim->isDying || victim->isDead || (victim->plan != Victim::PLAN_NOTHING)) {
			continue;
		}
		
		// this victim needs a plan - try smelling for food
		for (FoodList::iterator it = level->foods->begin(); it != level->foods->end(); it++) {
			Food* food = *it;
			if (food->isConsumed || food->isDead) {
				continue;
			}
			if (distance(food->position, victim->position) <= SMELL_DISTANCE) {
				victim->plan = Victim::PLAN_CHASE_FOOD;
				victim->target = food->position;
				break;
			}
		}
		
		// still no plan? Wander around a bit
		if (victim->plan == Victim::PLAN_NOTHING) {
			victim->plan = Victim::PLAN_WANDER;
			float wanderDistanceX = WANDER_DISTANCE_MIN + (WANDER_DISTANCE_MAX - WANDER_DISTANCE_MIN) * rand() / RAND_MAX;
			float wanderDistanceY = WANDER_DISTANCE_MIN + (WANDER_DISTANCE_MAX - WANDER_DISTANCE_MIN) * rand() / RAND_MAX;
			if (rand() % 2) wanderDistanceX *= -1;
			if (rand() % 2) wanderDistanceY *= -1;
			victim->target.x = victim->position.x + wanderDistanceX;
			victim->target.y = victim->position.y + wanderDistanceY;
		}
		
		fixTarget(victim);
	}
}

void AI::fixTarget(Victim* victim)
{
	if (victim->target.x < Level::BORDER_ZONE) victim->target.x = Level::BORDER_ZONE;
	if (victim->target.y < Level::BORDER_ZONE) victim->target.y = Level::BORDER_ZONE;
	if (victim->target.x > level->pixelWidth - Level::BORDER_ZONE) victim->target.x = level->pixelWidth - Level::BORDER_ZONE;
	if (victim->target.y > level->pixelWidth - Level::BORDER_ZONE) victim->target.y = level->pixelWidth - Level::BORDER_ZONE;
}
