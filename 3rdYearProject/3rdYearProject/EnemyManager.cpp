#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
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
	for(int i = 0; i < m_p_Enemies.size(); i++)
	{
		m_p_Enemies[i]->Update(timeElapsed, turn);
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
	m_p_Enemies.erase(m_p_Enemies.begin() + i);
}

void EnemyManager::FillAP()
{
	for(int i = 0; i < m_p_Enemies.size(); i++)
	{
		m_p_Enemies[i]->FillAP();
	}
}