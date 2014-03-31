#include "LevelManager.h"

LevelManager::LevelManager()
{
}

LevelManager::~LevelManager()
{
	delete(m_p_Map);
	delete(m_p_PlayerManager);
	delete(m_p_EnemyManager);
	delete(m_p_EnemyFactory);
	delete(m_p_PlayerFactory);
}

void LevelManager::Initialize(CC_Texture* enemySprites[], CC_Texture* playerSprites[], CC_Texture* tiles, Camera* camera, SoundManager* soundMan)
{
	m_p_Map = new LevelMap(tiles);
	m_p_PlayerManager = new PlayerManager();
	m_p_EnemyManager = new EnemyManager();
	m_p_EnemyFactory = new EnemyFactory(m_p_PlayerManager, enemySprites, m_p_Map->GetMap(), soundMan);
	m_p_PlayerFactory = new PlayerFactory(playerSprites, m_p_Map->GetMap(), soundMan);

	m_p_Camera = camera;
}

Character* LevelManager::GenerateLevel()
{
	m_p_Map->GenerateMap();

	for(int i = 0; i < TileMap::MAP_WIDTH; i++)
	{
		for(int j = 0; j < TileMap::MAP_HEIGHT; j++)
		{
			int code = m_p_Map->GetMap()->GetTileAtCell(i, j)->GetCode();
			if(code == 1)
			{
				m_p_EnemyManager->AddEnemy(m_p_EnemyFactory->CreateEnemy(Vector2(i * TileMap::TILE_WIDTH, j * TileMap::TILE_HEIGHT), 128));
			}
			else if(code == 2)
			{
				m_p_PlayerManager->AddPlayer(m_p_PlayerFactory->CreatePlayer(Vector2(i * TileMap::TILE_WIDTH, j * TileMap::TILE_HEIGHT), 128));
			}
		}
	}

	if(!m_p_PlayerManager->GetPlayers().empty())
	{
		return m_p_PlayerManager->GetPlayer(0);
	}

	return NULL;
}

void LevelManager::Update(Uint32 timeElapsed, int turn)
{
	m_p_PlayerManager->Update(timeElapsed, turn);
	m_p_EnemyManager->Update(timeElapsed, turn);
}

void LevelManager::Draw(SDL_Renderer* renderer)
{
	m_p_Map->Draw(renderer, m_p_Camera);
	m_p_PlayerManager->Draw(renderer, m_p_Camera);
	m_p_EnemyManager->Draw(renderer, m_p_Camera);
}

Character* LevelManager::HandleInput(InputHandler* input, Character* selectedPlayer)
{
	if(input->MousePressed(input->RightButton))
	{
		if(!m_Clicked)
		{
			Vector2 mousePos = Vector2(input->GetMouseX(), input->GetMouseY());
			selectedPlayer->SetTarget(m_p_Camera->ScreenToLocation(mousePos));
			m_Clicked = true;
		}
	}
	else
	{
		m_Clicked = false;
	}

	return m_p_PlayerManager->HandleInput(input, m_p_Camera);
}

void LevelManager::FillAP(int i)
{
	if(i == 1)
	{
		m_p_EnemyManager->FillAP();
	}
	else
	{
		m_p_PlayerManager->FillAP();
	}
}

PlayerManager* LevelManager::GetPlayerManager()
{
	return m_p_PlayerManager;
}

EnemyManager* LevelManager::GetEnemyManager()
{
	return m_p_EnemyManager;
}