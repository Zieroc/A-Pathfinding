#include "Tile.h"
#include <iostream>

Tile::Tile(int index, bool passable, int xCell, int yCell, int code)
{
	m_Index = index;
	m_Passable = passable;
	m_XCell = xCell;
	m_YCell = yCell;
	m_p_Node = new PathNode(this);
	m_Code = code;
}

Tile::Tile()
{
	m_Index = 0;
	m_Passable = true;
	m_XCell = 0;
	m_YCell = 0;
	m_p_Node = new PathNode(this);
}

Tile::~Tile()
{
	delete(m_p_Node);
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

int Tile::GetXCell()
{
	return m_XCell;
}

int Tile::GetYCell()
{
	return m_YCell;
}

PathNode* Tile::GetNode()
{
	return m_p_Node;
}

int Tile::GetCode()
{
	return m_Code;
}

void Tile::SetCode(int code)
{
	m_Code = code;
}