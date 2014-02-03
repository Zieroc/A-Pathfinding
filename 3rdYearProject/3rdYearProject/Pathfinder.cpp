#include "Pathfinder.h"
#include <algorithm>

Pathfinder::Pathfinder(TileMap* map)
{
	m_p_Map = map;
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
	m_SelectedSquare = start;
	openList.push_back(start);
	bool foundPath = false;
	m_SelectedSquare->SetParent(NULL);
	Tile* tile;

	while(!foundPath)
	{
		if(m_SelectedSquare->GetXCell() > 0)
		{
			tile = m_p_Map->GetTileAtCell(m_SelectedSquare->GetXCell() - 1, m_SelectedSquare->GetYCell());
			if(tile->GetPassable() && std::find(closedList.begin(), closedList.end(), tile) == closedList.end())
			{
				tile->SetF(CalculateH(tile, end));
				tile->SetParent(m_SelectedSquare);
				openList.push_back(tile);
			}
		}
		if(m_SelectedSquare->GetXCell() < TileMap::MAP_WIDTH - 1)
		{
			tile = m_p_Map->GetTileAtCell(m_SelectedSquare->GetXCell() + 1, m_SelectedSquare->GetYCell());
			if(tile->GetPassable() && std::find(closedList.begin(), closedList.end(), tile) == closedList.end())
			{
				tile->SetF(CalculateH(tile, end));
				tile->SetParent(m_SelectedSquare);
				openList.push_back(tile);
			}
		}
		if(m_SelectedSquare->GetYCell() > 0)
		{
			tile = m_p_Map->GetTileAtCell(m_SelectedSquare->GetXCell(), m_SelectedSquare->GetYCell() - 1);
			if(tile->GetPassable() && std::find(closedList.begin(), closedList.end(), tile) == closedList.end())
			{
				tile->SetF(CalculateH(tile, end));
				tile->SetParent(m_SelectedSquare);
				openList.push_back(tile);
			}
		}
		if(m_SelectedSquare->GetYCell() < TileMap::MAP_HEIGHT - 1)
		{
			tile = m_p_Map->GetTileAtCell(m_SelectedSquare->GetXCell(), m_SelectedSquare->GetYCell() + 1);
			if(tile->GetPassable() && std::find(closedList.begin(), closedList.end(), tile) == closedList.end())
			{
				tile->SetF(CalculateH(tile, end));
				tile->SetParent(m_SelectedSquare);
				openList.push_back(tile);
			}
		}

		closedList.push_back(m_SelectedSquare);

		if(std::find(closedList.begin(), closedList.end(), end) != closedList.end())
		{
			foundPath = true;
		}
		else
		{
			openList.erase(std::find(openList.begin(), openList.end(), m_SelectedSquare));
			openList.shrink_to_fit();

			std::sort(openList.begin(), openList.end(), [](Tile* a, Tile* b){return a->GetF() < b->GetF();});
			//std::reverse(openList.begin(), openList.end()); 

			m_SelectedSquare = openList[0];
		}
	}

	m_SelectedSquare = end;

	while(m_SelectedSquare != NULL)
	{
		m_Path.push_front(Vector2(m_SelectedSquare->GetXCell() * TileMap::TILE_WIDTH, m_SelectedSquare->GetYCell() * TileMap::TILE_HEIGHT));
		m_SelectedSquare = m_SelectedSquare->GetParent();
	}

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