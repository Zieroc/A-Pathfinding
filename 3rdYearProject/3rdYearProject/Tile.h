#ifndef TILE_H
#define TILE_H
#include "Debug.h"
#include <SDL.h>

class Tile
{
public:
	Tile();
	Tile(int index, bool passable, int xCell, int yCell);
	~Tile();
	int GetIndex();
	bool GetPassable();
	void SetIndex(int i);
	void SetPassable(bool passable);
	int GetF();
	void SetF(int h);
	Tile* GetParent();
	void SetParent(Tile* tile);
	int GetXCell();
	int GetYCell();
private:
	int m_XCell;
	int m_YCell;
	int m_Index;
	int m_G;
	int m_F; //Used for pathfinding
	Tile* m_p_Parent; //Used for pathfinding
	bool m_Passable;
};

#endif

