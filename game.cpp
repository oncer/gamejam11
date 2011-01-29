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
	
	queue  = al_create_event_queue();
	al_register_event_source(queue, (ALLEGRO_EVENT_SOURCE*)al_get_keyboard_event_source());
}

void Game::mainLoop ()
{	
	ALLEGRO_EVENT event;
	while(1) {
		
		update();
		draw();
		
		al_flip_display();
		al_wait_for_event(queue, &event);
		
		if(event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
			break;
		}
		
		currentLevel->player->handleEvent(&event);
	}
}

void Game::update()
{
	currentLevel->update();
}

void Game::draw()
{
	currentLevel->draw();
}

void Game::shutdown ()
{
	Resources::destroyInstance();
	delete currentLevel;
}

	
