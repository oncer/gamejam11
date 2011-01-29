#ifndef _BULLET_H_
#define _BULLET_H_

#include "coords.h"
#include "animation.h"

class Bullet
{

public:

Bullet(PixelCoords pos);

void draw();

bool canMove();
void doMove();
void nextAnimFrame();

PixelCoords position;
float dx, dy;
bool isDead; /* indicates that this object can be removed */

static const float BASE_SPEED = 5.0;

private:

int maxSteps;
int steps;
Animation bulletAnim;

};

#endif
