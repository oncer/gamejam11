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

Level* level;

void fixTarget(Victim* victim); // fix conditions like target out of level

};

#endif
