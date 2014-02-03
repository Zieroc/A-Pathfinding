#include "Tile.h"
#include <iostream>


Tile::Tile()
{
	m_Index = 0;
	m_Passable = true;
	m_G = 10;
}

Tile::Tile(int index, bool passable, int xCell, int yCell)
{
	m_Index = index;
	m_Passable = passable;
	m_G = 10;
	m_XCell = xCell;
	m_YCell = yCell;
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

int Tile::GetF()
{
	return m_F;
}

void Tile::SetF(int h)
{
	m_F = m_G + h;
}

Tile* Tile::GetParent()
{
	return m_p_Parent;
}

void Tile::SetParent(Tile* parent)
{
	m_p_Parent = parent;
}

int Tile::GetXCell()
{
	return m_XCell;
}

int Tile::GetYCell()
{
	return m_YCell;
}