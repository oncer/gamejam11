#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player;

#include "game.h"
#include "coords.h"
#include "weapontype.h"

class Player
{

public:

Player(PixelCoords pos);

static const int HUNGER_LIMIT = 2000;
static const float BASE_SPEED = 2.0;
static const int FIRE_RATE_BULLET = 10;
static const int FIRE_RATE_FLAME = 3;

int ix, iy; /* input direction */
int ifire; /* fire button input */
int vx, vy; /* view direction */
PixelCoords position;
int fireRate; /* how many ticks for next projectile */
int fireTicks;
int hunger; // if this reaches HUNGER_LIMIT, player dies
bool isDead; // set after death animation concludes. => Game Over
int keyBits;
int stickyDiagonal; // make it not almost impossible to have a diagonal
					// shoot direction while standing still
WeaponType weaponType;

void nextAnimFrame();
void draw();

bool handleEvent(ALLEGRO_EVENT *event);
void increaseHunger();
void feed(int foodValue);
void changeWeapon(WeaponType type);

void update();
bool canMove();
void doMove();

private:
	void getSpeed(float *dx, float *dy);
};

#endif
