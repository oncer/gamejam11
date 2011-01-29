#ifndef _GAME_H_
#define _GAME_H_

#include <allegro5/allegro5.h>
#include "resources.h"
#include "level.h"
#include "hud.h"
#include "collisionchecker.h"

/* This class contains the main loop and owns game resources */
class Game
{

public:

static Game *globalGame;
Level* currentLevel;

void init ();
void mainLoop ();
void shutdown ();

private:

void update();
void draw();

static const int FPS = 60;
ALLEGRO_DISPLAY * display; // TODO: move to somewhere else
ALLEGRO_TIMER *timer;
Resources* resources; // Game assets from files (images, sounds, ...)

Hud* hud;
CollisionChecker* collisionChecker;

ALLEGRO_EVENT_QUEUE *queue;

};

#endif
