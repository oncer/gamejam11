#include "coords.h"

class Bullet
{

public:

Bullet(PixelCoords pos);

void nextAnimFrame();
void draw();

bool canMove();
void doMove();

PixelCoords position;
float dx, dy;
bool dead; /* indicates that this object can be removed */

private:

static const float BASE_SPEED = 1.0;

int maxSteps;
int steps;


};
