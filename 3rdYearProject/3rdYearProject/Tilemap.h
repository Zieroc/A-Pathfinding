#ifndef TILEMAP_H
#define TILEMAP_H
#include "Debug.h"
#include "Tile.h"
#include "Camera.h"
#include "CC_Texture.h"
#include "TileDAO.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>

using std::string;

class TileMap
{
public:
	//MAP CONSTANTS
	static const int TILE_WIDTH = 32;
	static const int TILE_HEIGHT = 32;
	static const int ROOM_WIDTH = 9;
	static const int ROOM_HEIGHT = 9;
	static const int NUM_ROOMS_ROW = 3;
	static const int NUM_ROOMS_COL = 3;
	static const int NUM_ROOMS = NUM_ROOMS_COL * NUM_ROOMS_ROW;
	static const int MAP_WIDTH = ROOM_WIDTH * NUM_ROOMS_COL;
	static const int MAP_HEIGHT = ROOM_HEIGHT * NUM_ROOMS_ROW;
	static const int DEFAULT_TILE = 2;
	static const int NUMBER_OF_TILES = 3;

	TileMap(CC_Texture* tileSheet);
	~TileMap();
	int GetCellByPointX(int x); //Get x map cell for this pixel point
	int GetCellByPointY(int y); //Get y map cell for this pixel point
	bool IsCellPassable(int x, int y);
	bool IsCellPassableByPoint(int x, int y);
	Tile* GetTileAtCell(int x, int y);
	Tile* GetTileAtPoint(int x, int y);
	void SetTileAtCell(int x, int y, int index, bool passable, int code);
	void Draw(SDL_Renderer* renderer, Camera* camera);
	void LoadMap(const char* fileName);
	void LoadRoom(const char* fileName, int xOffset, int yOffset);
	void ClearMap();
private:
	Tile* m_p_MapCells[MAP_WIDTH][MAP_HEIGHT];
	CC_Texture* m_p_TileSheet;
	int TilesPerRow();
	SDL_Rect TileSourceRectangle(int index);
};

#endif

