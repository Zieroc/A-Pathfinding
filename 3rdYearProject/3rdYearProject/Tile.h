#ifndef TILE_H
#define TILE_H
#include "Debug.h"
#include <SDL.h>

class Tile
{
public:
	Tile();
	Tile(int index, bool passable);
	~Tile();
	int GetIndex();
	bool GetPassable();
	void SetIndex(int i);
	void SetPassable(bool passable);
private:
	int m_Index;
	bool m_Passable;
};

#endif

