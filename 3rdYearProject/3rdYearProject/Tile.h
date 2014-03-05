#ifndef TILE_H
#define TILE_H
#include "Debug.h"
#include <SDL.h>
#include "PathNode.h"

class Tile
{
public:
	
	Tile();
	Tile(int index, bool passable, int xCell, int yCell, int code);
	~Tile();
	int GetIndex();
	bool GetPassable();
	void SetIndex(int i);
	void SetPassable(bool passable);
	int GetXCell();
	int GetYCell();
	PathNode* GetNode();
	int GetCode();
	void SetCode(int code);
private:
	int m_XCell;
	int m_YCell;
	int m_Index;
	bool m_Passable;
	PathNode* m_p_Node;
	int m_Code; //0 - Nothing, 1 - Player Spawn Points, 2 - Enemy Spawn Point
};

#endif

