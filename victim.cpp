#include <allegro5/allegro5.h>
#include <math.h>
#include "level.h"
#include "victim.h"
#include "resources.h"

Victim::Victim(PixelCoords pos)
{
	position = pos;
	target = position;
	plan = PLAN_WANDER;
	speed = BASE_SPEED;
	isDying = false;
	isDead = false;
}

void Victim::nextAnimFrame()
{
	if (isDying) isDead = true; // TODO: die animation
}

void Victim::draw()
{
	Resources* resources = Resources::instance();
	int currentFrame = 0;
	ALLEGRO_BITMAP* img = resources->imgVictim[currentFrame];
	PixelCoords imgPos = antiCenter(position, al_get_bitmap_width(img), al_get_bitmap_height(img));
	al_draw_bitmap(img, imgPos.x, imgPos.y, 0);
}

void Victim::feed(int foodValue)
{
	// TODO: after a certain amount of food, the victim splits
}

bool Victim::canMove()
{
	if (isDead) return false;
	// TODO: collision check (use CollisionChecker or something as parameter)
	return true;
}

void Victim::doMove()
{
	float dir_x = target.x - position.x;
	float dir_y = target.y - position.y;
	float dir_w = sqrt(dir_x * dir_x + dir_y * dir_y);
	
	if (dir_w > 1) {
		position.x += dir_x / dir_w;
		position.y += dir_y / dir_w;
	}
	else {
		position = target;
	}

	if (position == target) {
		plan = PLAN_NOTHING; // wait until AI gives us a new plan
	}
}

void Victim::explode() {
	int n = 8;
	float r = 50;
	for (int i = 0; i < n; i++) {
		float a = 2 * 3.14 * i / n;
		float x = cos(a);
		float y = sin(a);
		FoodList *foods = Game::globalGame->currentLevel->foods;
		PixelCoords p = position;
		p.x += x * r;
		p.y += y * r;
		Food *f = new Food(0, p, 1000, false);
		foods->push_back(f);
	}
}
