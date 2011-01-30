#ifndef _LASER_H_
#define _LASER_H_

#include "coords.h"

class Laser
{
	
public:

static const float LASER_LENGTH = 2000; // enough to always cover the whole level
static const float LASER_START_OFFSET = 10; // get away from center pos. of shooting player

void set(PixelCoords position, float dx, float dy);
void activate();
void deactivate();

PixelCoords from;
PixelCoords to;
bool active;

};

#endif
