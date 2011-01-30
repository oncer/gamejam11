#ifndef _VICTIM_H_
#define _VICTIM_H_

#include "coords.h"
#include "animation.h"

class Victim
{

public:

enum Plan { PLAN_NOTHING, PLAN_WANDER, PLAN_CHASE_FOOD }; // Current plan of action (AI)

Victim(PixelCoords pos);

void nextAnimFrame();
void draw();

void feed(int foodValue);
bool canMove();
void doMove();
void explode();
Victim split();

PixelCoords position;
bool isDying;
bool isDead;
Plan plan;
PixelCoords target; // This is where we want to go
int splitCountdown; // How many food items we need to consume until split
int walkSteps; // How many steps are we walking to this target

private:

static const float BASE_SPEED = 1.0;
static const float INCREASE_SPEED = 0.1;
static const int FOOD_TO_SPLIT = 3;

float speed;
Animation walkAnim;
Animation deathAnim;

};

#endif
