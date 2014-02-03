#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "TileMap.h"
#include <vector>
#include <forward_list>
#include "Vector2.h"

using std::vector;
using std::forward_list;

class Pathfinder
{
public:
	Pathfinder(TileMap* map);
	~Pathfinder();
	int CalculateH(Tile* current, Tile* target);
	bool FindPath(Tile* start, Tile* end);
	Vector2 GetNextNode();
private:
	vector<Tile*> openList;
	vector<Tile*> closedList;
	forward_list<Vector2> m_Path;
	TileMap* m_p_Map;
	Tile* m_SelectedSquare;
};

#endif