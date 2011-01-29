#include "coords.h"

class Victim
{

public:

Victim(PixelCoords pos);

void nextAnimFrame();
void draw();

bool canMove();
void doMove();

private:

static const float BASE_SPEED = 1.0;
enum Plan { PLAN_WANDER, PLAN_CHASE_FOOD }; // Current plan of action (AI)

PixelCoords position;
float speed;

Plan plan;
PixelCoords target; // This is where we want to go

};
