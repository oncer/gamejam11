#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>
#include <time.h>
#include "resources.h"
#include "game.h"

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
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon(); // TODO: maybe not needed
    al_init_acodec_addon();
    al_install_audio();
    voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
    mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF2);
    al_attach_mixer_to_voice(mixer, voice);
	srand(time(0));
	
	resources = Resources::instance();
	resources->loadEverything();
	
	al_set_window_title(display, "Super Extinction");
	al_set_display_icon(display, resources->imgVictim[0]);

	hud = new Hud();
	
	timer = al_create_timer(1.0 / FPS);
	
	currentLevel = NULL;
	ai = NULL;
	
	queue = al_create_event_queue();
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
		
		if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
	
				break;
			}
			else {
				if (state == GS_Title) {
					restart();
					continue;
				}
				else if (state == GS_GameOver) {
					state = GS_Title;
					continue;
				}
			}
			
			if (event.keyboard.keycode == ALLEGRO_KEY_F1) {
				state = GS_GameOver;
			}
		}
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		if (state == GS_Playing) {
			/* let the player handle whatever events he wants */
			currentLevel->player->handleEvent(&event);
		}
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
	if (state == GS_Playing) {
		ai->planEverything();
		currentLevel->update();
		collisionChecker->playerPickupFood();
		collisionChecker->victimPickupFood();
		collisionChecker->victimVsBullet();
		collisionChecker->playerVsVictim();
		hud->setHunger(currentLevel->player->hunger);
		hud->setMaxHunger(Player::HUNGER_LIMIT);
		
		if (currentLevel->player->isDead) {
			state = GS_GameOver;
		}
	}
}

void Game::draw()
{
	Resources* resources = Resources::instance();
	if (state == GS_Title) {
		al_draw_bitmap(resources->imgTitle, 0, 0, 0);
	}
	else if (state == GS_Playing) {
		currentLevel->draw();
		hud->draw();
	}
	else if (state == GS_GameOver) {
		currentLevel->draw();
		hud->draw();
		
		al_draw_textf(resources->fontBig, al_map_rgb(255, 255, 255),
			320, 200, ALLEGRO_ALIGN_CENTRE, "Game Over"); 
	}
}

void Game::restart() {
	currentLevel = new Level();
	collisionChecker = new CollisionChecker(currentLevel);
	ai = new AI(currentLevel);
	state = GS_Playing;
}

void Game::shutdown ()
{
	Resources::destroyInstance();
	delete collisionChecker;
	delete ai;
	delete currentLevel;
	delete hud;
}
