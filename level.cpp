#include "level.h"

Level::Level()
{
	player = new Player();
	victims = new VictimList();
	levelObjects = new LevelObjectList();
}

Level::~Level()
{
	delete player;
	delete victims;
	delete levelObjects;
}

