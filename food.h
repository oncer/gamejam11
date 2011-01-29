#ifndef _FOOD_H_
#define _FOOD_H_

#include "coords.h"

// Food may be fruit (consumable by player) or bits of bad guys
// (player wants to collect those before other bad guys do)
class Food
{

public:

Food(PixelCoords pos);

PixelCoords position;

void nextAnimFrame();
void draw();

private:

};

#endif
