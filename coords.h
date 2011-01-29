#ifndef _COORDS_H_
#define _COORDS_H_

struct PixelCoords
{
	float x;
	float y;
	
	bool operator==(const PixelCoords& rhs);
};

#endif
