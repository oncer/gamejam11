#include <vector>
#include "player.h"
#include "victim.h"
#include "levelobject.h"

typedef std::vector<Victim> VictimList;
typedef std::vector<LevelObject> LevelObjectList;

/* Contains runtime level info */
class Level
{

public:

	Level();
	~Level();

	Player* player;
	VictimList* victims;
	LevelObjectList* levelObjects;

};
