#include "player.h"


void Player::draw()
{
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

void Player::tick() {
	position.x += ix;
	position.y += iy;
}
