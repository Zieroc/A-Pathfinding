#ifndef TILEDAO_H
#define TILEDAO_H

#include <vector>
#include "tinyxml2.h"
#include "Tile.h"

class TileDAO
{
public:
	TileDAO();
	~TileDAO();
	std::vector<Tile*> Read(const char* file);
};

#endif