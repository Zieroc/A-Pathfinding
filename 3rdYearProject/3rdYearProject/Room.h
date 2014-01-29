#ifndef ROOM_H
#define ROOM_H

class Room
{
public:
	Room(int x, int y);
	~Room();
	int m_X;
	int m_Y;
	bool m_CanSpawnEnemies;
	int m_MinEnemy;
	int m_MaxEnemy;
};

#endif