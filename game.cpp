#include "game.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

Game *Game::globalGame;

void Game::init ()
{
	globalGame = this;
	al_init();
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	display = al_create_display(640, 480);
	
	al_install_mouse(); // TODO: maybe not needed
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon(); // TODO: maybe not needed
	
	resources = Resources::instance();
	resources->loadEverything();
	
	currentLevel = new Level();
	hud = new Hud();
	collisionChecker = new CollisionChecker(currentLevel);
	
	timer = al_create_timer(1.0 / FPS);
	
	queue  = al_create_event_queue();
	al_register_event_source(queue, (ALLEGRO_EVENT_SOURCE*)al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_display_event_source(display));
}

void Game::mainLoop ()
{	
	ALLEGRO_EVENT event;
	
	al_start_timer(timer);
	
	bool redraw = false;
	
	while(1) {

		al_wait_for_event(queue, &event);
		
		if(event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
			break;
		}
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		
		/* let the player handle whatever events he wants */
		currentLevel->player->handleEvent(&event);
		
		if (event.type == ALLEGRO_EVENT_TIMER) {
			update();
			redraw = true;
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
			int w = event.display.width;
			int h = event.display.height;
			al_acknowledge_resize(display);
			ALLEGRO_TRANSFORM transform;
			float s = h / 480.0;
			int x = (w - 640 * s) / 2;
			int y = (h - 480 * s) / 2;

			al_build_transform(&transform, x, y, s, s, 0);
			al_use_transform(&transform);
			redraw = true;
		}
		
		if(redraw && al_is_event_queue_empty(queue)) {
         redraw = false;
         draw();
         al_flip_display();
      }
	}
}

void Game::update()
{
	currentLevel->update();
	collisionChecker->playerPickupFood();
	collisionChecker->victimPickupFood();
	collisionChecker->victimVsBullet();
	collisionChecker->playerVsVictim();
	hud->setHunger(currentLevel->player->hunger);
	hud->setMaxHunger(Player::HUNGER_LIMIT);
}

void Game::draw()
{
	currentLevel->draw();
	hud->draw();
}

void Game::shutdown ()
{
	Resources::destroyInstance();
	delete collisionChecker;
	delete currentLevel;
	delete hud;
}

	
