#include <cmath>
#include "player.h"
#include "audio.h"
#include "flame.h"
#include "bullet.h"

Player::Player(PixelCoords pos)
{
	position = pos;
	keyBits = 0;
	ix = iy = ifire = 0;
	vx = vy = 0;
	hunger = 0;
	isDead = false;
	fireTicks = 0;
	changeWeapon(WEAPON_GUN);
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
	if (stickyDiagonal) stickyDiagonal--;
	if (!ifire && (ix != 0 || iy != 0)) {
		if (stickyDiagonal && vx && vy) {
			// assume the keys are e.g. left-down,up-down,up-up,left-up
			// we want to keep shooting up/left, not straight left
		}
		else {
			vx = ix;
			vy = iy;
			if (vx && vy) {
				stickyDiagonal = 10;
			}
		}
	}

	if (ifire && fireTicks == 0 && (ix != 0 || iy != 0)) {
		PixelCoords p = position;

		float dx = ix;
		float dy = iy;
		float v = 1.0;
		
		Bullet *bullet = NULL; // only for WEAPON_GUN
		Flame *flame = NULL; // only for WEAPON_FLAMETHROWER
		
		switch (weaponType) {
			
		case WEAPON_GUN:;
			bullet = new Bullet(p);
			dx += (rand()%100 - 50) / 700.0;
			dy += (rand()%100 - 50) / 700.0;
			v = sqrt(dx * dx + dy * dy);
			dx = dx / v;
			dy = dy / v;
			bullet->dx = dx * bullet->getBaseSpeed();
			bullet->dy = dy * bullet->getBaseSpeed();
			fireTicks = fireRate;
			Game::globalGame->currentLevel->projectiles->push_back(bullet);
			Audio::playSFX(Audio::SFX_SHOT);
			break;
			
		case WEAPON_FLAMETHROWER:
			flame = new Flame(p);
			dx += (rand()%400 - 200) / 700.0;
			dy += (rand()%400 - 200) / 700.0;
			v = sqrt(dx * dx + dy * dy);
			dx = dx / v;
			dy = dy / v;
			flame->dx = dx * flame->getBaseSpeed();
			flame->dy = dy * flame->getBaseSpeed();
			fireTicks = fireRate;
			Game::globalGame->currentLevel->projectiles->push_back(flame);
			break;
			
		case WEAPON_LASER:
			break;
			
		}

	}
	
	if (fireTicks > 0)
		fireTicks--;
}

void Player::getSpeed(float *dx, float *dy) {
	*dx = ix;
	*dy = iy;
	float d = std::sqrt(*dx * *dx + *dy * *dy);
	*dx *= BASE_SPEED / d;
	*dy *= BASE_SPEED / d;
}

bool Player::canMove()
{
	Level *level = Game::globalGame->currentLevel;
	if (position.x > level->pixelWidth) {
		return false;
	}
	if (position.y > level->pixelHeight) {
		return false;
	}
	if (position.x < 0) {
		return false;
	}
	if (position.y < 0) {
		return false;
	}
	CollisionChecker *c = Game::globalGame->collisionChecker;
	return c->playerCanMoveTo(position);
}

void Player::doMove()
{
	if (!isDead && !ifire && (ix || iy)) {
		float dx, dy;
		getSpeed(&dx, &dy);
		
		position.x += dx;
		if (!canMove()) {
			position.x -= dx;
		}
		
		position.y += dy;
		if (!canMove()) {
			position.y -= dy;
		}
	}
}

void Player::changeWeapon(WeaponType type)
{
	fireTicks = 0;
	weaponType = type;
	
	switch(weaponType) {
		
	case WEAPON_GUN:
		fireRate = FIRE_RATE_BULLET;
		break;
		
	case WEAPON_FLAMETHROWER:
		fireRate = FIRE_RATE_FLAME;
		break;
		
	case WEAPON_LASER:
		fireRate = 1; // TODO: laser not implemented yet
		break;
		
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
				keyBits &= ~16;
				break;
		}
	}
}
