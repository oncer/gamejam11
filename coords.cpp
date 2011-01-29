#include "coords.h"

bool PixelCoords::operator==(const PixelCoords& rhs)
{
	return (x == rhs.x) && (y == rhs.y);
}
