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

static const int SCORE_KILL = 10; // only by shooting, not direct contact
static const int SCORE_FOOD = 50;
static const int SCORE_LEVEL = 500;
static const int WIDTH = 800;
static const int HEIGHT = 600;

static Game *globalGame;
Level* currentLevel;
GameState state;
CollisionChecker* collisionChecker;
int levelCounter;
int score;

int ignoreKeyboardTicks; // ignore keyboard for a number of ticks

void init ();
void mainLoop ();
void shutdown ();
void restart ();

void changeMusic(const char* path);

private:

void update();
void draw();
void drawLevelAndHud();

static const int FPS = 60;
ALLEGRO_DISPLAY * display; // TODO: move to somewhere else
ALLEGRO_TIMER *timer;
Resources* resources; // Game assets from files (images, sounds, ...)
ALLEGRO_BITMAP* drawingTarget; // in level: for alpha blending enabled draw operations

Hud* hud;
AI* ai;

ALLEGRO_EVENT_QUEUE *queue;

};

#endif
