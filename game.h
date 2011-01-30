#ifndef _GAME_H_
#define _GAME_H_

#include <allegro5/allegro5.h>
#include "resources.h"
#include "level.h"
#include "hud.h"
#include "collisionchecker.h"
#include "ai.h"

enum GameState {
	GS_Title,
	GS_Playing,
	GS_GameOver,
	GS_LevelWon,
	GS_GameWon
};

/* This class contains the main loop and owns game resources */
class Game
{

public:

static Game *globalGame;
Level* currentLevel;
GameState state;
CollisionChecker* collisionChecker;

void init ();
void mainLoop ();
void shutdown ();
void restart ();

void changeMusic(const char* path);

private:

void update();
void draw();

static const int FPS = 60;
ALLEGRO_DISPLAY * display; // TODO: move to somewhere else
ALLEGRO_TIMER *timer;
ALLEGRO_MIXER *mixer;
ALLEGRO_VOICE *voice;
Resources* resources; // Game assets from files (images, sounds, ...)

Hud* hud;
AI* ai;

ALLEGRO_EVENT_QUEUE *queue;

};

#endif
