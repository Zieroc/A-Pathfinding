#ifndef TILEMAP_H
#define TILEMAP_H
#include "Debug.h"
#include "Tile.h"
#include "Camera.h"
#include "CC_Texture.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>

using std::string;

#define TILE_WIDTH 32
#define TILE_HEIGHT 32
#define ROOM_WIDTH 9
#define ROOM_HEIGHT 9
#define NUM_ROOMS_ROW 3
#define NUM_ROOMS_COL 3
#define NUM_ROOMS NUM_ROOMS_COL * NUM_ROOMS_ROW
#define MAP_WIDTH ROOM_WIDTH * NUM_ROOMS_ROW
#define MAP_HEIGHT ROOM_HEIGHT * NUM_ROOMS_COL
#define DEFAULT_TILE 2
#define NUMBER_OF_TILES 3

class TileMap
{
public:
	TileMap(CC_Texture* tileSheet);
	~TileMap();
	int GetCellByPointX(int x); //Get x map cell for this pixel point
	int GetCellByPointY(int y); //Get y map cell for this pixel point
	bool IsCellPassable(int x, int y);
	bool IsCellPassableByPoint(int x, int y);
	Tile* GetTileAtCell(int x, int y);
	Tile* GetTileAtPoint(int x, int y);
	void SetTileAtCell(int x, int y, int index, bool passable);
	void Draw(SDL_Renderer* renderer, Camera* camera);
	void LoadMap(string fileName);
	void LoadRoom(string fileName, int xOffset, int yOffset);
	void ClearMap();
private:
	Tile* m_p_MapCells[MAP_WIDTH][MAP_HEIGHT];
	int m_TileCollideInfo[NUMBER_OF_TILES];
	CC_Texture* m_p_TileSheet;
	int TilesPerRow();
	SDL_Rect TileSourceRectangle(int index);
	void SetTileCollideInformation();
};

#endif

