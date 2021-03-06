#ifndef LEVELMAP_H
#define LEVELMAP_H

#include "TileMap.h"
#include "Room.h"
#include "CC_Texture.h"
#include <vector>

using std::vector;

class LevelMap
{
public:
	LevelMap(CC_Texture* tileSheet);
	~LevelMap();
	void GenerateMap();
	void Draw(SDL_Renderer* renderer, Camera* camera);
	void OpenConnection(int room1, int room2);
	void OpenDoor(int dir, int col, int row);
	vector<int> GetClosedConnections(int room, vector<int> closedRooms);
	TileMap* GetMap();
private:
	//Room* m_Rooms[TileMap::NUM_ROOMS]; Room class no longer used
	TileMap* m_p_Map;
};

#endif