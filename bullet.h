#ifndef _BULLET_H_
#define _BULLET_H_

#include "coords.h"
#include "projectile.h"
#include "animation.h"

class Bullet : public Projectile
{

public:

Bullet(PixelCoords pos);
virtual ~Bullet();

virtual void draw();
virtual void nextAnimFrame();
virtual float getBaseSpeed();

static const float BASE_SPEED = 5.0;

private:

Animation bulletAnim;

};

#endif
