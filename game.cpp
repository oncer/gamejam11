#include "game.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

void Game::init ()
{
	al_init();
	display = al_create_display(640, 480);
	
	al_install_mouse(); // TODO: maybe not needed
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon(); // TODO: maybe not needed
	
	resources = Resources::instance();
	resources->loadEverything();
	
	currentLevel = new Level();
	hud = new Hud();
	
	timer = al_create_timer(1.0 / FPS);
	
	queue  = al_create_event_queue();
	al_register_event_source(queue, (ALLEGRO_EVENT_SOURCE*)al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));

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
		
		/* let the player handle whatever events he wants */
		currentLevel->player->handleEvent(&event);
		
		if (event.type == ALLEGRO_EVENT_TIMER) {
			update();
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
	delete currentLevel;
	delete hud;
}

	
