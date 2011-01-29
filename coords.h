#ifndef _COORDS_H_
#define _COORDS_H_

struct PixelCoords
{
	float x;
	float y;
	
	bool operator==(const PixelCoords& rhs);
};

// given coords at the center of the box of given size, 
// this function returns coords at the top left of the box
PixelCoords antiCenter(PixelCoords coords, int width, int height);

float distance(PixelCoords a, PixelCoords b);

#endif
