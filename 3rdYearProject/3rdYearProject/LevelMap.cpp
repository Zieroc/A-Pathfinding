#include "LevelMap.h"
#include <algorithm>
#include <sstream>

using std::find;

LevelMap::LevelMap(CC_Texture* tileSheet)
{
	m_p_Map = new TileMap(tileSheet);
}

LevelMap::~LevelMap()
{
	delete(m_p_Map);

	for(int i = 0; i < NUM_ROOMS; i++)
	{
		if(m_Rooms[i] != NULL)
		{
			delete(m_Rooms[i]);
		}
	}
}

void LevelMap::GenerateMap()
{
	m_p_Map->ClearMap();
	vector<int> openRooms;
	vector<int> closedRooms;
	int connections[NUM_ROOMS];
	for(int i = 0; i < NUM_ROOMS; i++)
	{
		connections[i] = 0;
	}

	int activeRoom = 1;
	bool finished = false;
	for(int i = 0; i < NUM_ROOMS; i++)
	{
		closedRooms.push_back(i + 1);
	}

	for(int v = 0; v < NUM_ROOMS; v++)
	{
		DEBUG_MSG(activeRoom);
		openRooms.push_back(activeRoom);
		if(find(closedRooms.begin(), closedRooms.end(), activeRoom) != closedRooms.end())
		{
			closedRooms.erase(find(closedRooms.begin(), closedRooms.end(), activeRoom));
			closedRooms.shrink_to_fit();
			int room = activeRoom;
			vector<int> possibleRooms = GetClosedConnections(activeRoom, closedRooms);

			if(!possibleRooms.empty())
			{
				//List isn't empty pick a new room from the list
				int num = rand() % possibleRooms.size();
				room = possibleRooms[num];

				connections[activeRoom - 1] = room;
				activeRoom = room;
			}
			else
			{
				v = NUM_ROOMS;
			}
				
		}
		else
		{
			v = NUM_ROOMS;
		}
	}

	//Generate level files
	while(!openRooms.empty())
	{
		int room = openRooms.front();
		openRooms.erase(openRooms.begin());
		openRooms.shrink_to_fit();
		int col = (room % NUM_ROOMS_COL) - 1;
		int row = ((room - 1) / 3);
		if(col < 0)
		{
			col = NUM_ROOMS_COL - 1;
		}
		int lvl = rand() % 3 + 1;
		std::ostringstream ss;
		ss << "data/Files/Room" << lvl << ".lvl";
		m_p_Map->LoadRoom(ss.str().c_str(), 0 + (col * ROOM_WIDTH), 0 + (row * ROOM_HEIGHT));	
	}

	for(int i = 0; i < NUM_ROOMS; i++)
	{
		if(connections[i] > 0)
		{
			OpenConnection(i + 1, connections[i]);
		}
	}
}

void LevelMap::Draw(SDL_Renderer* renderer, Camera* camera)
{
	m_p_Map->Draw(renderer, camera);
}

void LevelMap::OpenConnection(int room1, int room2)
{
	int col1 = (room1 % NUM_ROOMS_COL) - 1;
	int row1 = ((room1 - 1) / 3);
	if(col1 < 0)
	{
		col1 = NUM_ROOMS_COL - 1;
	}

	int col2 = (room2 % NUM_ROOMS_COL) - 1;
	int row2 = ((room2 - 1) / 3);
	if(col2 < 0)
	{
		col2 = NUM_ROOMS_COL - 1;
	}

	int dir1 = 0;
	int dir2 = 0;

	if(col1 == col2)
	{
		//Same column => difference is in rows So must be up or down
		if(row1 < row2)
		{
			dir1 = 3;
			dir2 = 1;
		}
		else if(row1 > row2)
		{
			dir1 = 1;
			dir2 = 3;
		}
	}
	else if(row1 == row2)
	{
		//Same row => difference is in columns So must be right or left
		if(col1 < col2)
		{
			dir1 = 2;
			dir2 = 4;
		}
		else if(col1 > col2)
		{
			dir1 = 4;
			dir2 = 2;
		}
	}

	OpenDoor(dir1, col1, row1);
	OpenDoor(dir2, col2, row2);
}

void LevelMap::OpenDoor(int dir, int col, int row)
{
	switch(dir)
	{
	case 1:
		m_p_Map->SetTileAtCell(3 + (col * ROOM_WIDTH), 0 + (row * ROOM_HEIGHT), 1, true);
		m_p_Map->SetTileAtCell(4 + (col * ROOM_WIDTH), 0 + (row * ROOM_HEIGHT), 1, true);
		m_p_Map->SetTileAtCell(5 + (col * ROOM_WIDTH), 0 + (row * ROOM_HEIGHT), 1, true);
		break;
	case 2:
		m_p_Map->SetTileAtCell(ROOM_WIDTH - 1 + (col * ROOM_WIDTH), 3 + (row * ROOM_HEIGHT), 1, true);
		m_p_Map->SetTileAtCell(ROOM_WIDTH - 1 + (col * ROOM_WIDTH), 4 + (row * ROOM_HEIGHT), 1, true);
		m_p_Map->SetTileAtCell(ROOM_WIDTH - 1 + (col * ROOM_WIDTH), 5 + (row * ROOM_HEIGHT), 1, true);
		break;
	case 3:
		m_p_Map->SetTileAtCell(3 + (col * ROOM_WIDTH), ROOM_HEIGHT - 1 + (row * ROOM_HEIGHT), 1, true);
		m_p_Map->SetTileAtCell(4 + (col * ROOM_WIDTH), ROOM_HEIGHT - 1 + (row * ROOM_HEIGHT), 1, true);
		m_p_Map->SetTileAtCell(5 + (col * ROOM_WIDTH), ROOM_HEIGHT - 1 + (row * ROOM_HEIGHT), 1, true);
		break;
	case 4:
		m_p_Map->SetTileAtCell(0 + (col * ROOM_WIDTH), 3 + (row * ROOM_HEIGHT), 1, true);
		m_p_Map->SetTileAtCell(0 + (col * ROOM_WIDTH), 4 + (row * ROOM_HEIGHT), 1, true);
		m_p_Map->SetTileAtCell(0 + (col * ROOM_WIDTH), 5 + (row * ROOM_HEIGHT), 1, true);
		break;
	default:
		break;
	}
}


vector<int> LevelMap::GetClosedConnections(int room, vector<int> closedRooms)
{
	vector<int> closedConnections;
	int col = (room % NUM_ROOMS_COL) - 1;
	int row = ((room - 1) / 3);
	if(col < 0)
	{
		col = NUM_ROOMS_COL - 1;
	}

	bool connection = false;
	vector<int> connections;

	if(col == 0)
	{
		connections.push_back(room + 1);

		if(row == 0)
		{
			connections.push_back(room + NUM_ROOMS_COL);
		}
		else if(row == NUM_ROOMS_ROW - 1)
		{
			connections.push_back(room - NUM_ROOMS_COL);
		}
		else
		{
			connections.push_back(room + NUM_ROOMS_COL);
			connections.push_back(room - NUM_ROOMS_COL);
		}
	}
	else if(col == NUM_ROOMS_COL - 1)
	{
		connections.push_back(room - 1);
		if(row == 0)
		{
			connections.push_back(room + NUM_ROOMS_COL);
		}
		else if(row == NUM_ROOMS_ROW - 1)
		{
			connections.push_back(room - NUM_ROOMS_COL);
		}
		else
		{
			connections.push_back(room + NUM_ROOMS_COL);
			connections.push_back(room - NUM_ROOMS_COL);
		}
	}
	else
	{
		connections.push_back(room - 1);
		connections.push_back(room + 1);
		if(row == 0)
		{
			connections.push_back(room + NUM_ROOMS_COL);
		}
		else if(row == NUM_ROOMS_ROW)
		{
			connections.push_back(room - NUM_ROOMS_COL);
		}
		else
		{
			connections.push_back(room + NUM_ROOMS_COL);
			connections.push_back(room - NUM_ROOMS_COL);
		}
	}

	for(int i = 0; i < connections.size(); i++)
	{
		if(find(closedRooms.begin(), closedRooms.end(), connections[i]) != closedRooms.end())
		{
			closedConnections.push_back(connections[i]);
		}
	}

	return closedConnections;
}