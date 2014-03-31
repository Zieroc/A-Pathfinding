#include "EnemyManager.h"

EnemyManager::EnemyManager() : m_EnemyIndex(-1)
{
	m_p_EnemyToUpdate = NULL;
}

EnemyManager::~EnemyManager()
{
	for(std::vector<Enemy*>::const_iterator iter = m_p_Enemies.begin(); iter != m_p_Enemies.end(); ++iter)
	{
		delete(*iter);
	}
}

void EnemyManager::Update(Uint32 timeElapsed, int turn)
{
	for(int i = m_p_Enemies.size() - 1; i >= 0; i--)
	{
		if(m_p_Enemies[i]->GetCurrentHealth() <= 0)
		{
			m_p_Enemies[i]->UnoccupyMap();
			RemoveEnemy(i);
		}
	}


	if(turn == 2)
	{
		for(int i = 0; i < m_p_Enemies.size(); i++)
		{
			if(i != m_EnemyIndex) //The selected enemy is update seperately so do not update him here
			{
				m_p_Enemies[i]->Update(timeElapsed, 1); // Update all enemies as if it isn't their turn to handle animation updates
			}
		}
	
		if(m_p_EnemyToUpdate != NULL)
		{
			m_p_EnemyToUpdate->Update(timeElapsed, 2); //Update the selected enemy as appropriate so enemies will carry out actions one after the other
		}

		GetEnemyToUpdate();
	}
	else
	{
		for(int i = 0; i < m_p_Enemies.size(); i++)
		{
			m_p_Enemies[i]->Update(timeElapsed, 1);
		}
	}
}

void EnemyManager::Draw(SDL_Renderer* renderer, Camera* camera)
{
	for(int i = 0; i < m_p_Enemies.size(); i++)
	{
		m_p_Enemies[i]->Draw(renderer, camera);
	}
}

void EnemyManager::AddEnemy(Enemy* enemy)
{
	m_p_Enemies.push_back(enemy);
}

Enemy* EnemyManager::GetEnemy(int i)
{
	return m_p_Enemies.at(i);
}

void EnemyManager::RemoveEnemy(int i)
{
	delete(m_p_Enemies[i]);
	m_p_Enemies.erase(m_p_Enemies.begin() + i);
	m_p_EnemyToUpdate = NULL;
}

void EnemyManager::FillAP()
{
	for(int i = 0; i < m_p_Enemies.size(); i++)
	{
		m_p_Enemies[i]->FillAP();
	}
}

void EnemyManager::GetEnemyToUpdate()
{

	if(m_p_EnemyToUpdate != NULL)
	{
		if(m_p_EnemyToUpdate->GetCurrentAP() <= 0)
		{
			if(m_EnemyIndex < m_p_Enemies.size() - 1)
			{
				m_EnemyIndex++;
			}
			else
			{
				m_EnemyIndex = 0;
			}
		}
		m_p_EnemyToUpdate = m_p_Enemies[m_EnemyIndex];
	}
	else if(!m_p_Enemies.empty())
	{
		m_p_EnemyToUpdate = m_p_Enemies[0];
		m_EnemyIndex = 0;
	}
}

std::vector<Enemy*> EnemyManager::GetEnemies()
{
	return m_p_Enemies;
}

bool EnemyManager::TurnComplete()
{
	for(int i = 0; i < m_p_Enemies.size(); i++)
	{
		if(m_p_Enemies[i]->GetCurrentAP() > 0)
		{
			return false;
		}
	}

	return true;
}