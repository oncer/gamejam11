#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "coords.h"
#include "animation.h"

class Projectile
{

public:

Projectile(PixelCoords pos);
virtual ~Projectile();

virtual void draw() = 0;

virtual bool canMove();
virtual void doMove();
virtual void nextAnimFrame() = 0;
virtual float getBaseSpeed() = 0;

PixelCoords position;
float dx, dy;
bool isDead; /* indicates that this object can be removed */

protected:

int maxSteps;
int steps;

};

#endif
