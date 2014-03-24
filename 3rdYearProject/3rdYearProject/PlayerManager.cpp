#include "PlayerManager.h"

PlayerManager::PlayerManager()
{
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

void PlayerManager::AddPlayer(Character* player)
{
	m_p_Players.push_back(player);
}

Character* PlayerManager::GetPlayer(int i)
{
	return m_p_Players.at(i);
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