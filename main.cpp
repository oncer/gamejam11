#include "game.h"

int main()
{
	Game* game = new Game();
	
	game->init();
	game->mainLoop();
	game->shutdown();
	
	delete game;
	return 0;
}

/*
// Allegro 5 example	

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

int main(int argc, char** argv)
{
		if (!al_init()) {
			printf("Failed to initialize Allegro library.\n"); return 1;}
        
		ALLEGRO_DISPLAY * display = al_create_display(640, 480);
	if(!display) {
		printf("Error creating display.\n");
		return 1;
	}
	
	if(!al_install_keyboard()) {
		printf("Error installing keyboard.\n");
		return 1;
	}
	
    al_install_mouse();
    al_install_keyboard();
	al_init_image_addon();
	
	ALLEGRO_BITMAP* bmp = al_load_bitmap("./gfx/player.png");
	if (!bmp) {
		printf("Error loading bmp.\n");
		return 1;
	}
	
	
		ALLEGRO_EVENT_QUEUE *queue  = al_create_event_queue();
	al_register_event_source(queue, 
				 (ALLEGRO_EVENT_SOURCE*)al_get_keyboard_event_source());
				 
		
ALLEGRO_EVENT event;
	while(1) {
		al_set_target_backbuffer(display);
      al_clear_to_color(al_map_rgb_f(255, 255, 255));
		al_draw_bitmap(bmp, 0, 0, 0);
		al_flip_display();
		al_wait_for_event(queue, &event);
		if(event.type == ALLEGRO_EVENT_KEY_DOWN 
		&& event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) 
			break;
	}
	
	return 0;
}
*/
