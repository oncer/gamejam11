#ifndef _FLAME_H_
#define _FLAME_H_

#include "coords.h"
#include "projectile.h"
#include "animation.h"

// This class works like bullet, except it's a flame from the
// flame thrower and it has a fade anim
class Flame : public Projectile
{

public:

Flame(PixelCoords pos);
virtual ~Flame();

virtual void draw();
virtual void nextAnimFrame();
virtual float getBaseSpeed();
virtual void onHitVictim();

static const float BASE_SPEED = 4.0;

private:

Animation flameAnim;

};

#endif
