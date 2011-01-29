#ifndef _LEVELOBJECT_H_
#define _LEVELOBJECT_H_

#include "coords.h"

class LevelObject
{

public:
	PixelCoords position;

	LevelObject(PixelCoords pos);
	
	void draw();
};

#endif
