#include "Pathfinder.h"
#include <algorithm>

Pathfinder::Pathfinder(TileMap* map)
{
	m_p_Map = map;
}

Pathfinder::Pathfinder()
{
}

Pathfinder::~Pathfinder()
{
}

int Pathfinder::CalculateH(Tile* current, Tile* target)
{
	int h = 0;
	int xDiff = std::abs(current->GetXCell() - target->GetXCell());
	int yDiff = std::abs(current->GetYCell() - target->GetYCell());

	h = xDiff + yDiff;
	h *= 10;

	return h;
}

bool Pathfinder::FindPath(Tile* start, Tile* end)
{
	m_p_SelectedSquare = start;
	openList.clear();
	closedList.clear();
	openList.push_back(start);
	bool foundPath = false;
	PathNode* selectedNode = m_p_SelectedSquare->GetNode();
	PathNode* node;
	selectedNode->SetG(0);
	selectedNode->SetParent(NULL);
	Tile* tile;
	bool occupiedEnd = false;

	if(end->GetOccupied())
	{
		occupiedEnd = true;
		end->SetOccupied(false);
	}

	if(!m_p_SelectedSquare->GetPassable())
	{
		ClearNodes();
		return false;
	}

	while(!foundPath)
	{
		selectedNode = m_p_SelectedSquare->GetNode();

		if(m_p_SelectedSquare->GetXCell() > 0)
		{
			tile = m_p_Map->GetTileAtCell(m_p_SelectedSquare->GetXCell() - 1, m_p_SelectedSquare->GetYCell());
			node = tile->GetNode();
			if(tile->GetPassable() && !tile->GetOccupied() && std::find(closedList.begin(), closedList.end(), tile) == closedList.end())
			{
				node->SetParent(selectedNode);
				int g = 10 + node->GetParent()->GetG();
				node->SetG(g);
				node->SetF(CalculateH(tile, end));
				if(std::find(openList.begin(), openList.end(), tile) == openList.end())
				{
					openList.push_back(tile);
				}
			}
		}
		if(m_p_SelectedSquare->GetXCell() < TileMap::MAP_WIDTH - 1)
		{
			tile = m_p_Map->GetTileAtCell(m_p_SelectedSquare->GetXCell() + 1, m_p_SelectedSquare->GetYCell());
			node = tile->GetNode();
			if(tile->GetPassable() && !tile->GetOccupied() && std::find(closedList.begin(), closedList.end(), tile) == closedList.end())
			{
				node->SetParent(selectedNode);
				int g = 10 + node->GetParent()->GetG();
				node->SetG(g);
				node->SetF(CalculateH(tile, end));
				if(std::find(openList.begin(), openList.end(), tile) == openList.end())
				{
					openList.push_back(tile);
				}
			}
		}
		if(m_p_SelectedSquare->GetYCell() > 0)
		{
			tile = m_p_Map->GetTileAtCell(m_p_SelectedSquare->GetXCell(), m_p_SelectedSquare->GetYCell() - 1);
			node = tile->GetNode();
			if(tile->GetPassable() && !tile->GetOccupied() && std::find(closedList.begin(), closedList.end(), tile) == closedList.end())
			{
				node->SetParent(selectedNode);
				int g = 10 + node->GetParent()->GetG();
				node->SetG(g);
				node->SetF(CalculateH(tile, end));
				if(std::find(openList.begin(), openList.end(), tile) == openList.end())
				{
					openList.push_back(tile);
				}
			}
		}
		if(m_p_SelectedSquare->GetYCell() < TileMap::MAP_HEIGHT - 1)
		{
			tile = m_p_Map->GetTileAtCell(m_p_SelectedSquare->GetXCell(), m_p_SelectedSquare->GetYCell() + 1);
			node = tile->GetNode();
			if(tile->GetPassable() && !tile->GetOccupied() && std::find(closedList.begin(), closedList.end(), tile) == closedList.end())
			{
				node->SetParent(selectedNode);
				int g = 10 + node->GetParent()->GetG();
				node->SetG(g);
				node->SetF(CalculateH(tile, end));
				if(std::find(openList.begin(), openList.end(), tile) == openList.end())
				{
					openList.push_back(tile);
				}
			}
		}

		closedList.push_back(m_p_SelectedSquare);

		if(std::find(closedList.begin(), closedList.end(), end) != closedList.end())
		{
			foundPath = true;
			if(occupiedEnd)
			{
				end->SetOccupied(true);
				closedList.erase(std::find(closedList.begin(), closedList.end(), end));
				end = end->GetNode()->GetParent()->GetTile();
			}
		}
		else
		{
			openList.erase(std::find(openList.begin(), openList.end(), m_p_SelectedSquare));

			if(openList.empty())
			{
				ClearNodes();
				return false;
			}

			std::sort(openList.begin(), openList.end(), [](Tile* a, Tile* b){return a->GetNode()->GetF() < b->GetNode()->GetF();});
			//std::reverse(openList.begin(), openList.end()); 

			m_p_SelectedSquare = openList[0];
		}
	}

	m_p_SelectedSquare = end;

	while(m_p_SelectedSquare->GetNode()->GetParent() != NULL)
	{
		m_Path.push_front(Vector2(m_p_SelectedSquare->GetXCell() * TileMap::TILE_WIDTH, m_p_SelectedSquare->GetYCell() * TileMap::TILE_HEIGHT));
		m_p_SelectedSquare = m_p_SelectedSquare->GetNode()->GetParent()->GetTile();
	}

	ClearNodes();
	return true;
}

Vector2 Pathfinder::GetNextNode()
{
	Vector2 node(-10, -10);
	if(!m_Path.empty())
	{
		node = m_Path.front();
		m_Path.pop_front();
	}

	return node;
}

void Pathfinder::ClearNodes()
{
	for(int i = 0; i < TileMap::MAP_WIDTH; i++)
	{
		for(int j = 0; j < TileMap::MAP_HEIGHT; j++)
		{
			m_p_Map->GetTileAtCell(i, j)->GetNode()->SetParent(NULL);
			m_p_Map->GetTileAtCell(i, j)->GetNode()->SetG(10);
		}
	}
}