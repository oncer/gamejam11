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
}
