#include "PathNode.h"
#include "Tile.h"

PathNode::PathNode(Tile* tile)
{
	m_G = 10;
	m_p_Tile = tile;
}

PathNode::~PathNode()
{
}

PathNode* PathNode::GetParent()
{
	return m_p_Parent;
}

void PathNode::SetParent(PathNode* parent)
{
	m_p_Parent = parent;
}

int PathNode::GetF()
{
	return m_F;
}

void PathNode::SetF(int h)
{
	m_F = m_G + h;
}

Tile* PathNode::GetTile()
{
	return m_p_Tile;
}

int PathNode::GetG()
{
	return m_G;
}

void PathNode::SetG(int g)
{
	m_G = g;
}