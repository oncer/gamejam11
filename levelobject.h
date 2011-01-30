#ifndef _LEVELOBJECT_H_
#define _LEVELOBJECT_H_

#include "coords.h"

class LevelObject
{

public:
	PixelCoords position;
	int variation;
	int w, h;

	LevelObject(PixelCoords pos, int variation);

	void draw();
};

#endif
