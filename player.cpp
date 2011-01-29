#include "player.h"

void Player::nextAnimFrame()
{
}

void Player::draw()
{
	Resources* resources = Resources::instance();
	int currentFrame = 0;
	ALLEGRO_BITMAP* currentFrameImg = resources->imgPlayer[currentFrame];
	al_draw_bitmap(currentFrameImg, position.x, position.y, 0);
}

void Player::feed(int foodValue)
{
	hunger -= foodValue;
	if (hunger < 0) hunger = 0;
}

void Player::increaseHunger()
{
	hunger++;
	if (hunger >= HUNGER_LIMIT) {
		isDead = true;
	}
}

bool Player::canMove()
{
	// TODO: collision check (use CollisionChecker or something as parameter)
	return true;
}

void Player::doMove()
{
	position.x += ix;
	position.y += iy;
}
	
bool Player::handleEvent(ALLEGRO_EVENT *event) {
	if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (event->keyboard.keycode) {
			case ALLEGRO_KEY_LEFT:
				ix = -1;
				break;
			case ALLEGRO_KEY_RIGHT:
				ix = 1;
				break;
			case ALLEGRO_KEY_UP:
				iy = -1;
				break;
			case ALLEGRO_KEY_DOWN:
				iy = 1;
				break;
		}
	}
	if (event->type == ALLEGRO_EVENT_KEY_UP) {
		switch (event->keyboard.keycode) {
			case ALLEGRO_KEY_LEFT:
				ix = 0;
				break;
			case ALLEGRO_KEY_RIGHT:
				ix = 0;
				break;
			case ALLEGRO_KEY_UP:
				iy = 0;
				break;
			case ALLEGRO_KEY_DOWN:
				iy = 0;
				break;
		}
	}
}
