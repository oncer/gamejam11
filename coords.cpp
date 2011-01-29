#include "coords.h"

bool PixelCoords::operator==(const PixelCoords& rhs)
{
	return (x == rhs.x) && (y == rhs.y);
}

PixelCoords antiCenter(PixelCoords coords, int width, int height)
{
	return (PixelCoords) { coords.x - width/2, coords.y - height/2 };
}
