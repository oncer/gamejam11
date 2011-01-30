#include "laser.h"

void Laser::set(PixelCoords position, float dx, float dy)
{
	from.x = position.x + dx * LASER_START_OFFSET;
	from.y = position.y + dy * LASER_START_OFFSET; 
	to.x = position.x + dx * LASER_LENGTH;
	to.y = position.y + dy * LASER_LENGTH; 
}

void Laser::activate()
{
	active = true;
}

void Laser::deactivate()
{
	active = false;
}
