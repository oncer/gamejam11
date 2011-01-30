#include <allegro5/allegro5.h>
#include <math.h>
#include <cstdlib>
#include "level.h"
#include "victim.h"
#include "resources.h"
#include "audio.h"

Victim::Victim(PixelCoords pos)
    :walkAnim(6, 1, true),
     deathAnim(3, Resources::EXPLOSION_FRAMES, false)
{
	position = pos;
	target = position;
	plan = PLAN_WANDER;
	speed = BASE_SPEED;
	isDying = false;
	isDead = false;
	splitCountdown = FOOD_TO_SPLIT;
	splitAgain = 0;
}

void Victim::nextAnimFrame()
{
    if (isDying) {
        deathAnim.update();
        if (deathAnim.isDone()) {
            isDead = true;
        }
    }
}

void Victim::draw()
{
	Resources* resources = Resources::instance();
    ALLEGRO_BITMAP* img;
    if (isDying) {
        int currentFrame = deathAnim.getCurrentFrame();
        img = resources->imgExplosion[currentFrame];
    } else {
        int currentFrame = 0;
        img = resources->imgVictim[currentFrame];
    }
	PixelCoords imgPos = antiCenter(position, al_get_bitmap_width(img), al_get_bitmap_height(img));
	al_draw_bitmap(img, imgPos.x, imgPos.y, 0);
}

void Victim::feed(int foodValue)
{
	splitCountdown--;
}

bool Victim::canMove()
{
	if (isDead || isDying) return false;
	// TODO: collision check (use CollisionChecker or something as parameter)
	return true;
}

void Victim::doMove()
{
	float dir_x = target.x - position.x;
	float dir_y = target.y - position.y;
	float dir_w = sqrt(dir_x * dir_x + dir_y * dir_y) / speed;
	
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
	isDying = true;
	
	int n = 8;
	for (int i = 0; i < n; i++) {
		float a = 2 * 3.14 * (i + (std::rand() % 64) / 64.0) / n;
		float x = cos(a);
		float y = sin(a);
		float r = 40 + std::rand() % 40; 

		FoodList *foods = Game::globalGame->currentLevel->foods;
		PixelCoords p = position;
		p.x += x * r;
		p.y += y * r;
		Food *f = new Food(0, p, 1000, false);
		f->dx = x * r / 10;
		f->dy = y * r / 10;
		foods->push_back(f);
	}

	// shake screen
	Game::globalGame->currentLevel->shake();
}

Victim Victim::split()
{
	splitAgain = SPLIT_AGAIN_TICKS;
	splitCountdown += FOOD_TO_SPLIT; // reset countdown
	speed += INCREASE_SPEED;
	if (speed > MAX_SPEED) speed = MAX_SPEED;
	Victim v = Victim(position);
	v.splitAgain = SPLIT_AGAIN_TICKS;
	return v;
}
