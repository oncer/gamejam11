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
	
	resources = new Resources();
	resources->loadEverything();
	
	queue  = al_create_event_queue();
	al_register_event_source(queue, (ALLEGRO_EVENT_SOURCE*)al_get_keyboard_event_source());

}

void Game::mainLoop ()
{	
	ALLEGRO_EVENT event;
	while(1) {
		/* DEMO CODE - draw some stuff */
		al_clear_to_color(al_map_rgb_f(0, 0, 0));
		al_draw_filled_rectangle(0, 0, 160, 120, al_map_rgb_f(200, 127, 20)); // broken ?!
		
		/* blue vertical line */
		al_draw_line(0.5, 0, 0.5, 6, al_map_rgb_f(0, 0, 255), 1);
		/* red horizontal line */
		al_draw_line(2, 1, 6, 1, al_map_rgb_f(255, 0, 0), 2);
		al_draw_filled_circle(100, 100, 50, al_map_rgb_f(255, 0, 0));
		
		
		
		al_draw_bitmap(resources->imgBullet, 200, 50, 0);

		/* </DEMO CODE> */
		
		
		
		al_flip_display();
		al_wait_for_event(queue, &event);
		if(event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
			break;
		}
	}
}

void Game::shutdown ()
{
	delete resources;
}

	