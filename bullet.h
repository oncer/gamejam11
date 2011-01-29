#ifndef _BULLET_H_
#define _BULLET_H_

#include "coords.h"

class Bullet
{

public:

Bullet(PixelCoords pos);

void nextAnimFrame();
void draw();

bool canMove();
void doMove();

float dx, dy;
bool isDead; /* indicates that this object can be removed */

static const float BASE_SPEED = 5.0;

PixelCoords position;

private:

int maxSteps;
int steps;

bool collideWithVictim(Victim *v);

};

#endif
