#include <vector>
#include <list>
#include "player.h"
#include "victim.h"
#include "levelobject.h"

typedef std::list<Victim*> VictimList;
typedef std::vector<LevelObject*> LevelObjectList;

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

};
