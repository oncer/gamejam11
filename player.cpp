#include <cmath>
#include "player.h"

Player::Player(PixelCoords pos)
{
	position = pos;
	fireRate = 10;
	fireTicks = 0;
	keyBits = 0;
	ix = iy = ifire = 0;
	vx = vy = 0;
	hunger = 0;
	isDead = false;
}

void Player::nextAnimFrame()
{
}

void Player::draw()
{
	Resources* resources = Resources::instance();
	int currentFrame = 0;
	ALLEGRO_BITMAP* img = resources->imgPlayer[currentFrame];
	PixelCoords imgPos = antiCenter(position, al_get_bitmap_width(img), al_get_bitmap_height(img));
	al_draw_bitmap(img, imgPos.x, imgPos.y, 0);
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

void Player::update()
{
	if (ix != 0 || iy != 0) {
		vx = ix;
		vy = iy;
	}

	if (ifire && fireTicks == 0) {
		PixelCoords p = position;
		Bullet *bullet = new Bullet(p);
		bullet->dx = vx * Bullet::BASE_SPEED;
		bullet->dy = vy * Bullet::BASE_SPEED;
		fireTicks = fireRate;
		Game::globalGame->currentLevel->bullets->push_back(bullet);
	}
	
	if (fireTicks > 0)
		fireTicks--;
}

bool Player::canMove()
{
	// TODO: collision check (use CollisionChecker or something as parameter)
	return true;
}

void Player::doMove()
{
	if (!isDead && (ix || iy)) {
		float dx = ix;
		float dy = iy;
		float d = std::sqrt(dx * dx + dy * dy);
		dx *= BASE_SPEED / d;
		dy *= BASE_SPEED / d;
		position.x += dx;
		position.y += dy;
	}
}
	
bool Player::handleEvent(ALLEGRO_EVENT *event) {
	if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (event->keyboard.keycode) {
			case ALLEGRO_KEY_LEFT:
				ix = -1;
				keyBits |= 1;
				break;
			case ALLEGRO_KEY_RIGHT:
				ix = 1;
				keyBits |= 2;
				break;
			case ALLEGRO_KEY_UP:
				iy = -1;
				keyBits |= 4;
				break;
			case ALLEGRO_KEY_DOWN:
				iy = 1;
				keyBits |= 8;
				break;
			case ALLEGRO_KEY_SPACE:
			case ALLEGRO_KEY_LSHIFT:
				ifire = 1;
				keyBits |= 16;
				break;
		}
	}
	if (event->type == ALLEGRO_EVENT_KEY_UP) {
		switch (event->keyboard.keycode) {
			case ALLEGRO_KEY_LEFT:
				keyBits &= ~1;
				if ((keyBits & 3) == 0) ix = 0;
				break;
			case ALLEGRO_KEY_RIGHT:
				keyBits &= ~2;
				if ((keyBits & 3) == 0) ix = 0;
				break;
			case ALLEGRO_KEY_UP:
				keyBits &= ~4;
				if ((keyBits & 12) == 0) iy = 0;
				break;
			case ALLEGRO_KEY_DOWN:
				keyBits &= ~8;
				if ((keyBits & 12) == 0) iy = 0;
				break;
			case ALLEGRO_KEY_SPACE:
			case ALLEGRO_KEY_LSHIFT:
				ifire = 0;
				break;
		}
	}
}
