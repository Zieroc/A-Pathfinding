#include "PlayerManager.h"

PlayerManager::PlayerManager()
{
	m_Clicked = false;
}

PlayerManager::~PlayerManager()
{
	for(std::vector<Character*>::const_iterator iter = m_p_Players.begin(); iter != m_p_Players.end(); ++iter)
	{
		delete(*iter);
	}
}

void PlayerManager::Update(Uint32 timeElapsed, int turn)
{
	for(int i = m_p_Players.size() - 1; i >= 0; i--)
	{
		if(m_p_Players[i]->GetCurrentHealth() <= 0)
		{
			m_p_Players[i]->UnoccupyMap();
			RemovePlayer(i);
		}
	}

	for(int i = 0; i < m_p_Players.size(); i++)
	{
		m_p_Players[i]->Update(timeElapsed, turn);
	}
}

void PlayerManager::Draw(SDL_Renderer* renderer, Camera* camera)
{
	for(int i = 0; i < m_p_Players.size(); i++)
	{
		m_p_Players[i]->Draw(renderer, camera);
	}
}

Character* PlayerManager::HandleInput(InputHandler* input, Camera* camera)
{
	if(input->MousePressed(input->LeftButton))
	{
		if(!m_Clicked)
		{
			
			SDL_Rect mouse;
			Vector2 pos = camera->ScreenToLocation(Vector2(input->GetMouseX(), input->GetMouseY()));
			mouse.x = pos.x;
			mouse.y = pos.y;
			mouse.w = 8;
			mouse.h = 8;
			
			m_Clicked = true;

			for(int i = 0; i < m_p_Players.size(); i++)
			{
				if(SDL_HasIntersection(&mouse, &m_p_Players[i]->GetBounds()))
				{
					return m_p_Players[i];
				}
			}
		}
	}
	else
	{
		m_Clicked = false;
	}

	return NULL;

};

void PlayerManager::AddPlayer(Character* player)
{
	m_p_Players.push_back(player);
}

Character* PlayerManager::GetPlayer(int i)
{
	if(m_p_Players.size() > i && i > -1)
	{
		return m_p_Players.at(i);
	}

	return NULL;
}

void PlayerManager::RemovePlayer(int i)
{
	delete(m_p_Players[i]);
	m_p_Players.erase(m_p_Players.begin() + i);
}

void PlayerManager::FillAP()
{
	for(int i = 0; i < m_p_Players.size(); i++)
	{
		m_p_Players[i]->FillAP();
	}
}

std::vector<Character*> PlayerManager::GetPlayers()
{
	return m_p_Players;
}