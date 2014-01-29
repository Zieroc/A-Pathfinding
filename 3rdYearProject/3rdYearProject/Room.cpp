#include "Room.h"

Room::Room(int x, int y)
{
	m_X = x;
	m_Y = y;
	m_CanSpawnEnemies = false;
	m_MinEnemy = 0;
	m_MaxEnemy = 0;
}

Room::~Room()
{
}