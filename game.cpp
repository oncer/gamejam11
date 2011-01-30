#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <time.h>
#include "resources.h"
#include "game.h"
#include "audio.h"

Game *Game::globalGame;

void Game::init ()
{
	globalGame = this;
	al_init();
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	display = al_create_display(WIDTH, HEIGHT);
	
	al_install_mouse(); // TODO: maybe not needed
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon(); // TODO: maybe not needed
	Audio::init();
	srand(time(0));
	
	resources = Resources::instance();
	resources->loadEverything();
	
	al_set_window_title(display, "Super Extinction");
	al_set_display_icon(display, resources->imgVictim[0]);

	hud = new Hud();
	
	timer = al_create_timer(1.0 / FPS);
	
	levelCounter = 1;
	currentLevel = NULL;
	ai = NULL;
	score = 0;
	
	queue = al_create_event_queue();
	al_register_event_source(queue, (ALLEGRO_EVENT_SOURCE*)al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_display_event_source(display));
	
	drawingTarget = al_clone_bitmap(al_get_backbuffer(display));

	state = GS_Title;
	Audio::playMusic(Audio::MUSIC_TITLE);
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
			else if (ignoreKeyboardTicks == 0) {
				if (state == GS_Title) {
					score = 0;
					restart();
					continue;
				}
				else if (state == GS_GameOver) {
					state = GS_Title;
					Audio::playMusic(Audio::MUSIC_TITLE);
					continue;
				}
				else if (state == GS_LevelWon) {
					restart();
					state = GS_Playing;
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
			float s = h / (double)HEIGHT;
			int x = (w - WIDTH * s) / 2;
			int y = (h - HEIGHT * s) / 2;

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
	if (ignoreKeyboardTicks) ignoreKeyboardTicks--;
	
	if (state == GS_Playing) {
		ai->planEverything();
		currentLevel->update();
		collisionChecker->playerPickupWeapon();
		collisionChecker->playerPickupFood();
		collisionChecker->victimPickupFood();
		collisionChecker->victimVsLaser();
		collisionChecker->victimVsProjectile();
		collisionChecker->playerVsVictim();
		hud->setHunger(currentLevel->player->hunger);
		hud->setMaxHunger(Player::HUNGER_LIMIT);
		
		if (currentLevel->player->isDead) {
			state = GS_GameOver;
			Audio::stopMusic();
			ignoreKeyboardTicks = 20;
		}
		
		if (currentLevel->victims->size() == 0) {
			levelCounter++;
			state = GS_LevelWon;
			score += SCORE_LEVEL;
			ignoreKeyboardTicks = 20;
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
		drawLevelAndHud();
	}
	else if (state == GS_GameOver) {
		drawLevelAndHud();		
		al_draw_textf(resources->fontBig, al_map_rgb(255, 255, 255),
			Game::WIDTH/2, Game::HEIGHT/2 - 32, ALLEGRO_ALIGN_CENTRE, "Game Over"); 
	}
	else if (state == GS_LevelWon) {
		drawLevelAndHud();
		for (int i = 0; i < 5; i++) {
			int ox = (int[]){-1, 1, -1, 1, 0}[i];
			int oy = (int[]){1, 1, -1, -1, 0}[i];
			ALLEGRO_COLOR c;
			c = i == 4 ? al_map_rgb(255, 255, 255) : al_map_rgb(0, 0, 0);
			al_draw_textf(resources->fontBig, c,
				Game::WIDTH/2 + ox, Game::HEIGHT/2 - 60 + oy, ALLEGRO_ALIGN_CENTRE, "Extinction!");
			al_draw_textf(resources->fontNormal, c,
				Game::WIDTH/2 + ox, Game::HEIGHT/2 + 20 + oy, ALLEGRO_ALIGN_CENTRE, "Get ready for level %d!", levelCounter);
		}
	}
}

void Game::drawLevelAndHud()
{
	ALLEGRO_BITMAP* targetBackup = al_get_target_bitmap();
	al_set_target_bitmap(drawingTarget);
	currentLevel->draw();
	al_set_target_bitmap(targetBackup);
	al_draw_bitmap(drawingTarget, 0, 0, 0);
	hud->draw();
}

void Game::restart() {
	if (ai != NULL) delete ai;
	if (collisionChecker != NULL) delete collisionChecker;
	if (currentLevel != NULL) delete currentLevel;
	currentLevel = new Level();
	collisionChecker = new CollisionChecker(currentLevel);
	ai = new AI(currentLevel);
	currentLevel->create(levelCounter);
	state = GS_Playing;
	Audio::playMusic(Audio::MUSIC_BATTLE);
}

void Game::shutdown ()
{
	Audio::quit();
	Resources::destroyInstance();
	delete collisionChecker;
	delete ai;
	delete currentLevel;
	delete hud;
	al_destroy_bitmap(drawingTarget);
}
