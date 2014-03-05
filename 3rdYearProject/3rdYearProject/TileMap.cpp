#include "Tilemap.h"
#include <vector>

TileMap::TileMap(CC_Texture* tileSheet)
{
	for(int i = 0; i < MAP_WIDTH; i++)
	{
		for(int j = 0; j < MAP_HEIGHT; j++)
		{
			m_p_MapCells[i][j] = new Tile(DEFAULT_TILE, true, i, j, 0);
		}
	}

	m_p_TileSheet = tileSheet;
}


TileMap::~TileMap()
{
	for(int i = 0; i < MAP_WIDTH; i++)
	{
		for(int j = 0; j < MAP_HEIGHT; j++)
		{
			delete(m_p_MapCells[i][j]);
		}
	}
}

int TileMap::GetCellByPointX(int x)
{
	int result = x / TILE_WIDTH;
	if(result < 0)
	{
		return 0;
	}
	if(result >= MAP_WIDTH)
	{
		return MAP_WIDTH - 1;
	}
	return result;
}

int TileMap::GetCellByPointY(int y)
{
	int result = y / TILE_HEIGHT;
	if(result < 0)
	{
		return 0;
	}
	if(result >= MAP_HEIGHT)
	{
		return MAP_HEIGHT - 1;
	}
	return y / TILE_HEIGHT;
}

bool TileMap::IsCellPassable(int x, int y)
{
	return GetTileAtCell(x, y)->GetPassable();
}

bool TileMap::IsCellPassableByPoint(int x, int y)
{
	return GetTileAtPoint(x, y)->GetPassable();
}

Tile* TileMap::GetTileAtCell(int x, int y)
{
	return m_p_MapCells[x][y];
}

Tile* TileMap::GetTileAtPoint(int x, int y)
{
	return m_p_MapCells[GetCellByPointX(x)][GetCellByPointY(y)];
}

void TileMap::SetTileAtCell(int x, int y, int index, bool passable, int code)
{
	GetTileAtCell(x, y)->SetIndex(index);
	GetTileAtCell(x, y)->SetPassable(passable);
	GetTileAtCell(x, y)->SetCode(code);
}

void TileMap::Draw(SDL_Renderer* renderer, Camera* camera)
{
	//Get the start and end map cell numbers that can be seen on screen
	int startX = GetCellByPointX((int)camera->GetPosition().x);
	int endX = GetCellByPointX((int)camera->GetPosition().x + camera->GetViewPortSize().x);

	int startY = GetCellByPointY((int)camera->GetPosition().y);
	int endY = GetCellByPointY((int)camera->GetPosition().y + camera->GetViewPortSize().y);

	for (int x = startX; x <= endX; x++)
	{
		for (int y = startY; y <= endY; y++)
		{
			if ((x >= 0) && (y >= 0) && (x < MAP_WIDTH) && (y < MAP_HEIGHT))
			{
				SDL_Rect sourceRect = TileSourceRectangle(m_p_MapCells[x][y]->GetIndex());
				SDL_Rect destRect;

				destRect.x = x * TILE_WIDTH;
				destRect.y = y * TILE_HEIGHT;
				destRect.w = TILE_WIDTH;
				destRect.h = TILE_HEIGHT;
				destRect = camera->LocationToScreen(destRect);
				SDL_RenderCopy(renderer, m_p_TileSheet->GetTexture(), &sourceRect, &destRect);
			}
		}
	}
}

void TileMap::LoadMap(const char* fileName)
{
	TileDAO tileDAO;
	std::vector<Tile*> tiles = tileDAO.Read(fileName);
	int tile = 0;

	for(int i = 0; i <  MAP_WIDTH; i++)
	{
		for(int j = 0; j < MAP_HEIGHT; j++)
		{
			if(tile < tiles.size())
			{
				m_p_MapCells[i][j]->SetIndex(tiles[tile]->GetIndex());
				m_p_MapCells[i][j]->SetPassable(tiles[tile]->GetPassable());
				m_p_MapCells[i][j]->SetCode(tiles[tile]->GetCode());
				tile++;
			}
		}
	}

	for(std::vector<Tile*>::const_iterator iter = tiles.begin(); iter != tiles.end(); ++iter)
	{
		delete *iter;
	}
	tiles.clear();
}

void TileMap::LoadRoom(const char* fileName, int xOffset, int yOffset)
{
	TileDAO tileDAO;
	std::vector<Tile*> tiles = tileDAO.Read(fileName);
	int tile = 0;

	for(int i = 0; i <  ROOM_WIDTH; i++)
	{
		for(int j = 0; j < ROOM_HEIGHT; j++)
		{
			if(tile < tiles.size())
			{
				m_p_MapCells[i + xOffset][j + yOffset]->SetIndex(tiles[tile]->GetIndex());
				m_p_MapCells[i + xOffset][j + yOffset]->SetPassable(tiles[tile]->GetPassable());
				m_p_MapCells[i + xOffset][j + yOffset]->SetCode(tiles[tile]->GetCode());
				tile++;
			}
		}
	}

	for(std::vector<Tile*>::const_iterator iter = tiles.begin(); iter != tiles.end(); ++iter)
	{
		delete *iter;
	}
	tiles.clear();
}

void TileMap::ClearMap()
{
	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			m_p_MapCells[x][y]->SetIndex(DEFAULT_TILE);
			m_p_MapCells[x][y]->SetPassable(true);
		}
	}
}

int TileMap::TilesPerRow()
{
	return m_p_TileSheet->GetWidth() / MAP_WIDTH;
}

SDL_Rect TileMap::TileSourceRectangle(int index)
{
	SDL_Rect source;
	source.x = (index % TilesPerRow()) * TILE_WIDTH;
	source.y = (index / TilesPerRow()) * TILE_HEIGHT;
	source.w = TILE_WIDTH;
	source. h = TILE_HEIGHT;
	return source;
}