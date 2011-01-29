#ifndef _VICTIM_H_
#define _VICTIM_H_

#include "coords.h"

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

PixelCoords position;
bool isDying;
bool isDead;
Plan plan;
PixelCoords target; // This is where we want to go

private:

static const float BASE_SPEED = 1.0;

float speed;

};

#endif
