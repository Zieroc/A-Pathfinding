#include "Tile.h"
#include <iostream>


Tile::Tile()
{
	m_Index = 0;
	m_Passable = true;
}

Tile::Tile(int index, bool passable)
{
	m_Index = index;
	m_Passable = passable;
}

Tile::~Tile()
{
}

int Tile::GetIndex()
{
	return m_Index;
}

bool Tile::GetPassable()
{
	return m_Passable;
}

void Tile::SetIndex(int i)
{
	m_Index = i;
}

void Tile::SetPassable(bool passable)
{
	m_Passable = passable;
}