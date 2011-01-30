#ifndef _AI_H_
#define _AI_H_

class Level;
class Victim;

// controls the victims movements
class AI
{

public:

AI(Level* lvl);
void planEverything(); // set actions for all the victims

private:

static const float SMELL_DISTANCE = 200; // Victims will smell food this far
static const float WANDER_DISTANCE_MIN = 70;
static const float WANDER_DISTANCE_MAX = 100;
static const float BACKOFF_CHANCE_PERCENT = 20;
static const int MIN_FOOD_STEPS = 60;

Level* level;

void fixTarget(Victim* victim); // fix conditions like target out of level

};

#endif
