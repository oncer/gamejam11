#include <math.h>
#include "coords.h"

bool PixelCoords::operator==(const PixelCoords& rhs)
{
	return (x == rhs.x) && (y == rhs.y);
}

PixelCoords antiCenter(PixelCoords coords, int width, int height)
{
	return (PixelCoords) { coords.x - width/2, coords.y - height/2 };
}

float distance(PixelCoords a, PixelCoords b)
{
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
