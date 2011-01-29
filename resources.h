#include <allegro5/allegro5.h>

/* Contains game assets from files (images, sounds, ...) */
class Resources
{
	
public:

Resources();
~Resources();
void loadEverything();

static const int PLAYER_FRAMES = 1;
static const int VICTIM_FRAMES = 1;
static const int BIT_VARIATIONS = 1; // how many different kinds of bits there are

enum Frame { FRAME_FRONT }; // anim frame indices

ALLEGRO_BITMAP* imgPlayer[PLAYER_FRAMES];
ALLEGRO_BITMAP* imgVictim[VICTIM_FRAMES];
ALLEGRO_BITMAP* imgBullet;
ALLEGRO_BITMAP* imgBit[BIT_VARIATIONS];

};