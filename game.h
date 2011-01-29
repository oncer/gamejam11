#include <allegro5/allegro5.h>
#include "resources.h"

/* This class contains the main loop and owns game resources */
class Game
{

public:
	
void init ();
void mainLoop ();
void shutdown ();

private:

ALLEGRO_DISPLAY * display; // TODO: move to somewhere else
ALLEGRO_BITMAP* bmp; // TODO: sample code; remove this
Resources* resources; // Game assets from files (images, sounds, ...)

ALLEGRO_EVENT_QUEUE *queue;

};
