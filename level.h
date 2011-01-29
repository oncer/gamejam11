#ifndef _LEVEL_H_
#define _LEVEL_H_

class Level;

#include <vector>
#include <list>
#include "player.h"
#include "victim.h"
#include "levelobject.h"
#include "bullet.h"

typedef std::list<Victim*> VictimList;
typedef std::vector<LevelObject*> LevelObjectList;
typedef std::vector<Bullet*> BulletList;

/* Contains runtime level info */
class Level
{
public:

	Level();
	~Level();

	void update();
	void draw();

	Player* player;
	VictimList* victims;
	LevelObjectList* levelObjects;
	BulletList* bullets;

};

#endif
